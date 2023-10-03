#include <iostream>
#include <cassert>

template <typename Object>
class Vector {
private:
    int m_size;
    int m_capacity;
    Object* m_ptr;

public:
    explicit Vector(int size = 0) : m_size{ size }, m_capacity{ size == 0 ? 1 : size * 2 } {
        m_ptr = new Object[m_capacity];
    }

    ~Vector() {
        if(m_ptr != nullptr)
            delete[] m_ptr;
    }

    // Copy constructor with deep copying
    Vector(const Vector<Object>& a) : m_size{ a.m_size }, m_capacity{ a.m_capacity }, m_ptr{ new Object[a.m_capacity] } {
        for (int i = 0; i < m_size; ++i) {
            m_ptr[i] = a.m_ptr[i];
        }
    }

    // Copy assignment with deep copying
    Vector& operator=(const Vector<Object>& a) {
        if (&a == this) return *this;

        delete[] m_ptr;

        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = new Object[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_ptr[i] = a.m_ptr[i];
        }
        return *this;
    }

    // Move copy constructor
    Vector(Vector<Object>&& a) noexcept : m_size{ a.m_size }, m_capacity{ a.m_capacity }, m_ptr{ a.m_ptr } {
        a.m_ptr = nullptr;
        a.m_size = 0;
        a.m_capacity = 0;
    }

    // Move assignment
    Vector& operator=(Vector<Object>&& a) noexcept {
        if (&a == this) return *this;

        delete[] m_ptr;

        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = a.m_ptr;

        a.m_ptr = nullptr;
        a.m_size = 0;
        a.m_capacity = 0;

        return *this;
    }

    void reserve(int newCapacity) {
        if (newCapacity <= m_size) return;

        Object* newObject = new Object[newCapacity];
        for (int i = 0; i < m_size; ++i) {
            newObject[i] = std::move(m_ptr[i]);
        }

        m_capacity = newCapacity;
        std::swap(m_ptr, newObject);
        delete[] newObject;
    }

    void resize(int newSize) {
        if (newSize > m_capacity)
            reserve(newSize * 2);
        m_size = newSize;
    }

    void push_back(const Object& obj) {
        if (m_size == m_capacity)
            reserve(2 * m_capacity);
        m_ptr[m_size++] = obj;
    }

    void pop_back() {
        assert(m_size > 0);  // Check if vector is not empty
        --m_size;
    }

    Object& operator[](int index) {
        assert(index >= 0 && index < m_size); // Range check
        return m_ptr[index];
    }

    const Object& operator[](int index) const {
        assert(index >= 0 && index < m_size); // Range check
        return m_ptr[index];
    }

    int size() const {
        return m_size;
    }

    int capacity() const {
        return m_capacity;
    }

    bool empty() const {
        return m_size == 0;
    }
};
