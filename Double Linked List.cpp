#include <iostream>
#include <cassert>

template <typename Object>

class List
{
private:
    struct Node
    {
        Object data;
        Node* next;
        Node* previous;

        Node(const Object& obj = Object{}, Node* n = nullptr, Node* p = nullptr) : data{ obj },next{n}, previous{p} {}
        
    };

    Node* m_head;
    //Node* m_tail;
    int m_size;

public:
    List(): m_size{0}
    {      
        m_head = nullptr;
        //m_tail = nullptr;
    }

    ~List()
    {
        delete m_head;
        
    }

    void push_front(const Object& data)
    {
        ++m_size;

        //create new Node and store data
        Node* newNode = new Node;
        newNode->data = data;

        if (m_head == nullptr)
        {
            
            m_head = newNode;
            
            return;
        }

        //newNode is head now
        newNode->previous = nullptr;
        newNode->next = m_head;

        //prev of the original head is newNode
        m_head->previous = newNode;

        //m_head now should point to the very 1st element
        m_head = newNode;
                
    }

    void push_back(const Object& data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        Node* begin = m_head;

        //traverse till last node
        while (m_head->next != nullptr)
        {
            m_head = m_head->next;
        }

        
        newNode->previous = m_head;
        m_head->next = newNode;

        m_head = begin;
        begin = nullptr;
        ++m_size;
    }

    //insert Object before Node
    void insert(Node* nextNode, const Object& data)
    {
        assert(nextNode != nullptr);

        Node* newNode = new Node;
        newNode->data = data;
        
        newNode->next = nextNode;
        newNode->previous = nextNode->previous;

        nextNode->previous = newNode;
        newNode->previous->next = newNode;

        ++m_size;
    }

    void pop_front()
    {
        //we need to delete the original m_head;
        Node* deleteHead = m_head;
        m_head = m_head->next;
        m_head->previous = nullptr;
        
        delete deleteHead;
        --m_size;
    }

    void pop_back()
    {
        Node* copyHead = m_head;

        for (int i = 1; i < m_size; ++i)
        {
            m_head = m_head->next;
        }
        m_head->previous->next = nullptr;
        delete m_head;
        m_head = copyHead;

        copyHead = nullptr;                    
        
        --m_size;
        
    }

    Node* getNodeAt(unsigned int index)
    {
        assert(index <= m_size);

        Node* begin = m_head;
        Node* node = nullptr;
        int count{};
        static bool check = true;

        while (check)
        {
            //node = m_head->next->previous;
            node = m_head;
            m_head = m_head->next;
            ++count;

            if (count == index)
                check = false;
        }

        //reset m_head to the beginning
        m_head = begin;
        begin = nullptr;
        return node;
    }

     const Node* begin()
    {
        return m_head;
    }

    void printData()
    {
        Node* last = m_head;
        Node* copyHead = m_head;

        while (last->next != nullptr)
        {
            std::cout << m_head->data << '\n';
            last = m_head;
            m_head = m_head->next;
            
        }

        //reset head to the beginning of the list
        m_head = copyHead;
        copyHead = nullptr;
    }

    int size()
    {
        return m_size;
    }

};


int main()
{
    List<int> list;
    list.push_front(5);
    list.push_front(4);
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.printData();
    std::cout << "\nAfer front_popping\n";
    list.pop_front();
    list.printData();
    std::cout << "\nAfter inserting\n";
    list.insert(list.getNodeAt(3), 10);
    list.printData();
    std::cout << "\nAfer back_popping\n";
    list.pop_back();
    std::cout << "SIZE:" << list.size() << '\n';    
    list.printData();




    

    return 0;
}

