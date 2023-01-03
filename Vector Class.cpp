#include <iostream>

template <typename Object>

class Vector
{
private:
    int m_size;
    int m_capacity;
    Object* m_ptr;
public:
    explicit Vector(int size = 0) : m_size{ size }, m_capacity{size+5}
    {
        m_ptr = new Object[m_capacity];
    }

    ~Vector() { delete[] m_ptr; }

    //Copy constructor with deep copying
    Vector(const Vector<Object>& a)
    {
        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = new Object[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            m_ptr[i] = a.m_ptr[i];
        }

    }

    //Copy assignemnt with deep copying
    Vector& operator = (const Vector<Object>& a)
    {
        if (&a == this)
            return *this;

        //delete existing pointer and deep copy from Vector 'a'
        delete[] m_ptr;

        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = new Object[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            m_ptr[i] = a.m_ptr[i];
        }
        
        return *this;
    }

    //In case there is no need to COPY, it is more efficient to utilize MOVE SEMANTICS! 

    //1.Move copy c-r
    Vector(Vector<Object>&& a) noexcept
    {
        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = a.m_ptr;

        a.m_ptr = nullptr;
        a.m_size = 0;
        a.m_capacity = 0;
    }

    //2.Move assignment
    Vector& operator= (Vector<Object>&& a) noexcept
    {
        if (&a == this)
            return *this;

        delete[] m_ptr;

        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_ptr = a.m_ptr;

        a.m_ptr = nullptr;
        a.m_size = 0;
        a.m_capacity = 0;

        return *this;
    }



    void reserve(int newCapacity)
    {
        if (newCapacity < m_size)
            return;

        Object* newObject = new Object[newCapacity];
        
        for (int i = 0; i < m_size; ++i)
        {
            newObject[i] = m_ptr[i];
            
        }

        delete[] m_ptr;           
        m_capacity = newCapacity;
        m_ptr = new Object[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            m_ptr[i] = newObject[i];
        }

        delete[] newObject;


    }

    void resize(int newSize)
    {
        if (newSize > m_capacity)
            reserve(newSize * 2);

        m_size = newSize;

    }

    void push_back(const Object& obj)
    {
        if (m_size == m_capacity)
            reserve(2 * m_capacity + 1);

        m_ptr[m_size++] = obj;
    }

    void pop_back()
    {
        --m_size;
    }

    Object& operator[] (int index)
    {
        return m_ptr[index];
    }

    const Object& operator[] (int index) const
    {
        return m_ptr[index];
    }

    int size() const
    {
        return m_size;
    }

    int capacity() const
    {
        return m_capacity;
    }
};

int main()
{
    Vector<int> vec{};
    vec.push_back(5);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(0);
    
    Vector<int> copy{ std::move(vec) };
    //vec.pop_back();
    std::cout << "vec size:" << vec.size() << "  vec capacity:" << vec.capacity() << '\n';

    for (int i = 0; i < copy.size(); ++i)
    {
        std::cout << copy[i] << ' ';
    }
    return 0;
}


