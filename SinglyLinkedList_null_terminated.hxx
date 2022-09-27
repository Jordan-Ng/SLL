// #pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <utility>
#include "SinglyLinkedList.hpp"

// (4) implementation
namespace DS::SeqCont
{
    template <typename T>
    struct SinglyLinkedList<T>::Node
    {
        T _data = T{};
        Node *next = nullptr;

        Node() = default;
        Node(T value) : _data{std::move(value)} {}
    };

    template <typename T>
    struct SinglyLinkedList<T>::PrivateMembers
    {
        Node *_head = nullptr;
        Node *_tail = nullptr;
        std::size_t _size = 0;
    };

    // std::unique_ptr<typename SinglyLinkedList<T>::Node> SinglyLinkedList<T>::before_begin() { return nullptr; };
    template <typename T>
    auto SinglyLinkedList<T>::before_begin() { return nullptr; };

    template <typename T>
    auto SinglyLinkedList<T>::end() { return nullptr; };

    template <typename T>
    auto SinglyLinkedList<T>::insert_after(Node *position, T &data)
    {
        // aliases
        auto &head = self->_head;
        auto &tail = self->_tail;
        auto &size = self->_size;

        Node *newNode = new Node(data);
        Node *currentNode = position;

        if (isEmpty())
        {
            head = tail = newNode;
        }

        // insert at beginning
        if (currentNode == nullptr)
        {
            newNode->next = head;
            head = newNode;
        }
        // insert at end
        else if (currentNode == tail)
        {
            tail->next = newNode;
            tail = newNode;
        }
        // insert somewhere in list
        else
        {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }

        size += 1;
        return newNode;
    };

    template <typename T>
    void SinglyLinkedList<T>::erase_after(Node *position)
    {
        // aliases
        auto &head = self->_head;
        auto &tail = self->_tail;
        auto &size = self->_size;

        Node *toBeRemoved = nullptr;
        // if before_begin is passed in (trying to erase head)
        // what if before_begin is passed in and the list is empty?
        if (isEmpty())
        {
            throw std::length_error("attempting to remove from an empty list");
        }

        // what if tail is passed in? before_begin and tail are nullptrs, how do we ensure correct behavior?
        if (position == tail)
        {
            return;
        }
 
        if (position == before_begin())
        {
            toBeRemoved = head;
            head = head->next;
        }

        // if erase somewhere in list
        else
        {
            /*
                Notice that we are not handling the situation where the position passed in is the
                second to last node.
                If we needed to address that special case, the implementation would differ a little.
                we would need to have additional validation (because position-> next -> next in
                this scenario would throw an error: dereferencing a nullptr):

                toBeRemoved = position -> next;
                if(toBeRemoved == tail){
                    position->next = nullptr;
                    tail = position
                }

                why is it not implemented then? that's because the interface abstracts the
                creation of nodes from the client. this means that the client will not have access to these Node pointers
                and will only be able to invoke the erase_after function for limited iterators (begin, end, before_begin)
                as defined in our interface. Also, there are no member functions (only pop_front in interface) that will need 
                to support this special case.

                well, what if we had a member function that gets the Node at a certain position and then executes
                erase_after at the returned address? say:

                Node * get(int position){
                    int traverseCount = position;
                    Node* currentNode = self->head;

                    if (isEmpty || position > size() - 1){throw std::out_of_range("out of range")}
                    while(traverseCount != 0){
                        currentNode = currentNode -> next;
                        traverseCount -= 1;
                    }

                    return currentNode;
                }

                mySll.erase_after(mySll.get(2))

                **Notice that the get(int position) member function is an O(n) operation. so mybe not a good idea..
            */

            toBeRemoved = position->next;
            position->next = position->next->next;
        }

        size -= 1;
        delete toBeRemoved;
    }
}