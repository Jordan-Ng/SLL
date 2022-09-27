#pragma once
#include <initializer_list>
#include <memory>
#include <cstddef>
#include <utility>

// (2) declaring the interface
namespace DS::SeqCont
{
    template <typename T>
    class SinglyLinkedList
    {
    private:
        struct Node;
        struct PrivateMembers;
        std::unique_ptr<PrivateMembers> self = nullptr;

    public:
        // -- initialization support for SLL --
        SinglyLinkedList();                                   // default constructor
        SinglyLinkedList(std::initializer_list<T> init_list); // initialized list constructor
        // SinglyLinkedList(SinglyLinkedList const &other);          // copy constructor
        // SinglyLinkedList(SinglyLinkedList const &&other);         // move constructor
        // SinglyLinkedList &operator=(SinglyLinkedList const &rhs); // copy assignment operator
        // SinglyLinkedList &&operator=(SinglyLinkedList &&rhs);     // move assignment operator
        ~SinglyLinkedList(); // destructor

        //  -- iterators --
        auto before_begin();
        auto begin();
        auto end();

        //  -- accessors --
        T &front();
        T &back();

        // -- queries --
        bool isEmpty();
        std::size_t size();

        // -- modifiers --
        void push_back(T &value);
        void push_front(T &value);
        void pop_front();
        void clear();
        void pop_back() = delete;
        /* not supporting pop back!
            - O(n) operation, (we need to traverse all the way to end of list to delete)
            - even if we regulate tail, we would still need to traverse to the second to last node,
              which will be a O(n-1) operation, which will essentially still be O(n)
        */

        // -- extra operations --
        auto insert_after(Node *position, T &data);
        void erase_after(Node *position);
        void forward_print();
        void forward_print_recursive();
        void backward_print();
        void reverse();

    private:
        void forward_print_recursive(Node *);
        void backward_print(Node *);
        void reverse(Node *);
    };
}

// (4) implementation
/* why are the implementations split between .hpp and .hxx files? Notice from the notes, there are some
   similarities between null_terminated and circular SLL. So, we can define member functions that are 
   "shared" here, and implement specific member functions individually in their respective .hxx
   files. 

   to separate interface from implementation further, these "shared" member functions can be moved to its
   own .hpp file
*/
namespace DS::SeqCont
{
    // -- RAII --
    template <typename T>
    SinglyLinkedList<T>::SinglyLinkedList() : self(std::make_unique<PrivateMembers>()) {}

    template <typename T>
    SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> init_list)
        : SinglyLinkedList()
    {
        for (T item : init_list)
            push_back(item);
    }

    template <typename T>
    SinglyLinkedList<T>::~SinglyLinkedList()
    {
        clear();
    }

    // -- iterators -- (see specific implementation in respective SLL implementation)
    template <typename T>
    auto SinglyLinkedList<T>::begin() { return self->_head; }

    // -- accessors --
    template <typename T>
    T &SinglyLinkedList<T>::front()
    {
        return self->_head->_data;
    };

    template <typename T>
    T &SinglyLinkedList<T>::back()
    {
        return self->_tail->_data;
    };

    // -- queries --
    template <typename T>
    bool SinglyLinkedList<T>::isEmpty() { return size() == 0; }

    template <typename T>
    std::size_t SinglyLinkedList<T>::size()
    {
        return self->_size;
    }

    // -- modifiers --
    template <typename T>
    void SinglyLinkedList<T>::push_back(T &data)
    {
        insert_after(self->_tail, data);
    }

    template <typename T>
    void SinglyLinkedList<T>::push_front(T &data)
    {
        insert_after(before_begin(), data);
    }

    template <typename T>
    void SinglyLinkedList<T>::pop_front()
    {
        erase_after(before_begin());
    }

    template <typename T>
    void SinglyLinkedList<T>::clear()
    {
        while (begin()->next != end())
            pop_front();
    }

    // -- extra operations --
    template <typename T>
    void SinglyLinkedList<T>::forward_print()
    {
        Node *currentNode = self->_head;
        while (currentNode->next != end())
        {
            std::cout << currentNode->_data << " -> ";
            currentNode = currentNode->next;
        }
        std::cout << currentNode->_data << std::endl;
    }

    // public implementation (client facing)
    template <typename T>
    void SinglyLinkedList<T>::forward_print_recursive()
    {
        forward_print_recursive(self->_head);
    }

    template <typename T>
    void SinglyLinkedList<T>::backward_print()
    {
        backward_print(self->_head);
    }

    template <typename T>
    void SinglyLinkedList<T>::reverse()
    {
        auto &head = self->_head;
        auto &tail = self->_tail;
        auto tempHead = self->_head;
        reverse(head);
        // swapping head and tail
        head = tail;
        tail = tempHead;
        tempHead = nullptr;
    }

    // private helper function
    template <typename T>
    void SinglyLinkedList<T>::forward_print_recursive(Node *current)
    {
        // pre order traversal (visit -> recurse)
        // base case
        if (current == end())
            return;

        // visit
        std::cout << current->_data;
        if (current->next != end())
        {
            std::cout << " -> ";
        }
        else
        {
            std::cout << "\n";
        }
        // recurse
        forward_print_recursive(current->next);
    }

    // item4 <- item3 <- item2 <- item1
    template <typename T>
    void SinglyLinkedList<T>::backward_print(Node *current)
    {
        // post order traversal (recurse -> visit)
        // base case
        if (current == end())
            return;
        // recurse
        backward_print(current->next);
        // visit
        std::cout << current->_data;
        if (current != begin())
        {
            std::cout << " <- ";
        }
        else
        {
            std::cout << "\n";
        }
    }

    template <typename T>
    void SinglyLinkedList<T>::reverse(Node *current)
    {
        // base case
        if (current == end() || current->next == end())
        {
            return;
        }
        // recursive
        reverse(current->next);

        // visit
        Node *currentNode = current;
        Node *nextNode = current->next;

        nextNode->next = currentNode;
        currentNode->next = end();
    }
}

// #include "SinglyLinkedList_null_terminated.hxx"
#include "SinglyLinkedList_circular.hxx"
