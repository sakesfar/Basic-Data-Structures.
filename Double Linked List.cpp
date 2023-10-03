#include <iostream>
#include <cassert>

template <typename Object>
class List {
private:
    struct Node {
        Object data;
        Node* next;
        Node* previous;

        Node(const Object& obj = Object{}, Node* n = nullptr, Node* p = nullptr)
            : data{obj}, next{n}, previous{p} {}
    };

    Node* m_head;
    int m_size;

public:
    List() : m_size{0}, m_head{nullptr} {}

    ~List() {
        Node* current = m_head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void push_front(const Object& data) {
        Node* newNode = new Node(data, m_head);
        if (m_head) {
            m_head->previous = newNode;
        }
        m_head = newNode;
        ++m_size;
    }

    void push_back(const Object& data) {
        Node* newNode = new Node(data);
        if (!m_head) {
            m_head = newNode;
        } else {
            Node* temp = m_head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->previous = temp;
        }
        ++m_size;
    }

    void insert(Node* nextNode, const Object& data) {
        assert(nextNode != nullptr);
        Node* newNode = new Node(data, nextNode, nextNode->previous);
        if (nextNode->previous) {
            nextNode->previous->next = newNode;
        }
        nextNode->previous = newNode;

        ++m_size;
    }

    void pop_front() {
        assert(m_head != nullptr);  // List should not be empty

        Node* deleteHead = m_head;
        m_head = m_head->next;
        if (m_head) {
            m_head->previous = nullptr;
        }
        delete deleteHead;

        --m_size;
    }

    void pop_back() {
        assert(m_head != nullptr);  // List should not be empty

        Node* temp = m_head;
        while (temp->next) {
            temp = temp->next;
        }
        if (temp->previous) {
            temp->previous->next = nullptr;
        } else {
            m_head = nullptr;
        }
        delete temp;

        --m_size;
    }

    
    void printData() const {
        Node* temp = m_head;
        while (temp) {
            std::cout << temp->data << '\n';
            temp = temp->next;
        }
    }

    int size() const {
        return m_size;
    }

public:

class iterator;


 iterator begin() {
        return iterator(m_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    class iterator {
        Node* current;

    public:
        iterator(Node* ptr = nullptr) : current{ptr} {}

Object& operator*() {
    assert(current != nullptr);
    return current->data;
}

// Overload for the -> dereference operator
Object* operator->() {
    assert(current != nullptr);
    return &current->data;
}

        

        // Prefix ++
        iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Postfix ++
        iterator operator++(int) {
            iterator old = *this;
            current = current->next;
            return old;
        }

        // Prefix --
        iterator& operator--() {
            current = current->previous;
            return *this;
        }

        // Postfix --
        iterator operator--(int) {
            iterator old = *this;
            current = current->previous;
            return old;
        }

        // Equality check
        bool operator==(const iterator& rhs) const {
            return current == rhs.current;
        }

        // Inequality check
        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        }
    };



};
