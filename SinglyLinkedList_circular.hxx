#include "SinglyLinkedList.hpp"

namespace DS::SeqCont
{
    template <typename T>
    struct SinglyLinkedList<T>::Node
    {
        T _data = T{};
        Node *next = this;

        Node() = default;
        Node(T value) : _data{std::move(value)} {}
    };

    template <typename T>
    struct SinglyLinkedList<T>::PrivateMembers
    {
        Node sentinel;
        Node *&_head = sentinel.next;
        Node *_tail = &sentinel;
        std::size_t _size = 0;
    };

    template <typename T>
    auto SinglyLinkedList<T>::before_begin() { return &self->sentinel; }

    template <typename T>
    auto SinglyLinkedList<T>::end() { return &self->sentinel; }

    template <typename T>
    auto SinglyLinkedList<T>::insert_after(Node *position, T &data)
    {
        auto &tail = self->_tail;
        auto &size = self->_size;

        Node *newNode = new Node(data);
        Node *currentNode = position;

        newNode->next = currentNode->next;
        currentNode->next = newNode;

        if (newNode->next == end())
            tail = newNode;
        size += 1;
        return newNode;
    }

    template <typename T>
    void SinglyLinkedList<T>::erase_after(Node *position)
    {
        auto &tail = self->_tail;
        auto &size = self->_size;

        if (isEmpty())
        {
            throw std::length_error("removing from empty list");
        }
        if (position == tail)
        {
            return;
        }

        Node *toBeRemoved = position->next;
        position->next = position->next->next;

        size -= 1;

        if (toBeRemoved == tail)
            tail = position;
        delete toBeRemoved;
    }
}