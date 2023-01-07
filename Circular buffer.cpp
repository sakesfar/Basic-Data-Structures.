#include <iostream>
#include <cassert>

template <typename Object>

class RingBuffer
{
private:
    int m_size;
    Object* m_data;
    int m_head;
    int m_tail;
public:
    RingBuffer(int size = 0) : m_size{ size }
    {
        if (m_size == 0)
            m_data = nullptr;
        else
        {
            m_data = new Object[m_size];
            m_head = -1;
            m_tail = -1;
        }
    }

    ~RingBuffer() { delete[] m_data; }

    void insert(const Object& obj)
    {
        assert(m_data != nullptr);

        if (m_tail == -1 && m_head == -1)
        {
            ++m_tail;
            ++m_head;
            m_data[m_tail] = obj;
        }

        else if (m_tail >= 0 && m_tail < m_size - 1)
        {
            ++m_tail;
            m_data[m_tail] = obj;
            
            
        }

        else if (m_tail >= m_size - 1)
        {
            m_tail = 0;
            m_data[m_tail] = obj;
            ++m_tail;
        }


    }

    void pop()
    {
        assert(m_head != -1 || m_tail != -1);

        if (m_head >= 0 && m_head<m_tail)
        {
            m_data[m_head] = 0;
            ++m_head;
        }

        if (m_head == m_tail)
        {
            m_data[m_head] = 0;
            m_head = m_tail = -1;
        }

    }

    void printData()
    {
        assert(m_head != -1 && m_tail != -1 || m_data!=nullptr);
        for (int i = 0; i < m_size; ++i)
        {
            std::cout << m_data[i] << '\n';
        }
        std::cout << "HEAD:" << m_data[m_head] << ", TAIL:" << m_data[m_tail] << '\n';
    }

    int size()
    {
        return m_size;
    }

};

int main()
{
    RingBuffer<int> list{8};
    for (int i = 0; i < list.size(); ++i)
    {
        list.insert(i);
    }

    for (int i = 0; i < list.size() - 4; ++i)
    {
        list.pop();
    }
    list.printData();
    list.insert(8);
    std::cout << "INSERTION AFTER POPPING\n";
    list.printData();


    return 0;
}

