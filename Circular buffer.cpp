template <typename Object>
class RingBuffer {
private:
    int m_capacity;
    int m_size;
    Object* m_data;
    int m_head;
    int m_tail;

public:
    RingBuffer(int capacity = 0) : m_capacity{ capacity }, m_size{0}, m_head{0}, m_tail{0} {
        if (m_capacity == 0) {
            m_data = nullptr;
        } else {
            m_data = new Object[m_capacity];
        }
    }

    ~RingBuffer() { delete[] m_data; }

    bool isFull() const {
        return m_size == m_capacity;
    }

    bool isEmpty() const {
        return m_size == 0;
    }

    void insert(const Object& obj) {
        assert(m_data != nullptr);

        if (isFull()) {
       
            m_head = (m_head + 1) % m_capacity;
        }

        m_data[m_tail] = obj;
        m_tail = (m_tail + 1) % m_capacity;
        m_size++;
    }

    void pop() {
        assert(!isEmpty());

        m_head = (m_head + 1) % m_capacity;
        m_size--;
    }

    void printData() {
        assert(m_data != nullptr);

        for (int i = 0; i < m_capacity; ++i) {
            std::cout << m_data[i] << ' ';
        }
        std::cout << "\nHEAD:" << m_data[m_head] << ", TAIL:" << (m_tail == 0 ? m_data[m_capacity - 1] : m_data[m_tail - 1]) << '\n';
    }

    int size() const {
        return m_size;
    }
};
