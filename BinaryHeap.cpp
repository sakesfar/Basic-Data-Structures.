#include <iostream>
#include <vector>

template <typename Object>
class BinaryHeap
{
private:
    std::vector<Object> m_data;
    unsigned int m_currentSize;
public:
    BinaryHeap(unsigned int size) :m_currentSize{ 0 }
    {
        m_data.resize(size+1);         
        //std::cout << "CUR SIZE" << m_currentSize << " vec size:" << m_data.size() << "\n";
    }

    void insert(const Object& item)
    {
        if (m_currentSize==m_data.size()-1)
            m_data.resize(m_data.size() * 2);
        
        Object temp = item;
        m_data[0] = std::move(temp);

        int hole = ++m_currentSize;

        for (; item < m_data[hole / 2]; hole /= 2)
            m_data[hole] = std::move(m_data[hole/2]);

        m_data[hole] = std::move(m_data[0]);

    }

    void deleteMin()
    {
        m_data[1] = std::move(m_data[m_currentSize--]);
        percolateDown(1);
    }
    
    void percolateDown(int hole)
    {
        int maxHoles = m_currentSize / 2;
        Object copy = m_data[1];
        while (hole <= maxHoles)
        {
            if (hole*2 == m_currentSize)
            {
                if (m_data[hole] <= m_data[2 * hole])
                    break;
                else
                {
                    m_data[hole] = std::move(m_data[hole * 2]);
                    m_data[hole * 2] = std::move(copy);
                    break;
                }
            }

            else if (m_data[hole] <= m_data[2 * hole] && m_data[hole] <= m_data[hole * 2 + 1])
            {
                break;
            }
            else
            {
                if (m_data[hole * 2] < m_data[hole * 2 + 1])
                {
                    m_data[hole] = std::move(m_data[hole * 2]);
                    m_data[hole * 2] = std::move(copy);
                    hole *= 2;
                }
                else
                {
                    m_data[hole] = std::move(m_data[hole * 2 + 1]);
                    m_data[hole * 2 + 1] = std::move(copy);
                    hole=hole*2+1;
                }
                    
            }
                        
        }

        
    }
    

    void display()
    {
        for (int i = 1; i <=m_currentSize; ++i)
            std::cout << m_data[i] << " ";
            
    }

    int size()
    {
        return m_currentSize;
    }

};


int main()
{
    BinaryHeap<int> data{ 10 };
    data.insert(4);
    data.insert(9);
    data.insert(8);
    data.insert(7);
    data.insert(6);
    data.insert(13);
    data.insert(3);
    data.deleteMin();
    data.deleteMin();    

    data.display();
    std::cout << "\n" << data.size();

    return 0;
}


