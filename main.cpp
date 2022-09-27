#include <iostream>
#include <string>
#include "SinglyLinkedList.hpp"

// (1) pseudocode -> (2) interface -> (3) main -> (4) implementation
int main()
{
    // (1) Pseudocode - what do we want from the interface?
    //  we want to keep track of head, tail, and size of SLL

    // initialization suppot for SLL (rule of five)
        // default constructor -- (done, done)
        // initialized list constructor -- (done, done)
        // copy constructor
        // move constructor
        // copy assignment operator
        // move assignment operator
        // destructor -- (done, done)

    // compare
        // == operator overloading

    // iterators
        // before_begin -- (done, done)
        // begin -- (done, done)
        // end -- (done, done)

    // accessors (read and write)
        // front -- (done, done)
        // back -- (done, done)

    // queries
        // isEmpty -- (done, done)
        // size -- (done, done)

    // modifiers
        // push front -- (done, done)
        // push back -- (done, done)
        // pop front -- (done, done)
        // pop back (**delete**)
        // clear -- (done, done)

    // other operations to interact with the SLL:
        // forward print -- (done, done)
        // recursive forward print -- (done, done)
        // backward print -- (done, done)
        // insert_after -- (done, done)
        // remove_after -- (done, done)
        /*(notice that we cannot do insert/remove before, because it is a forward list,
        so we cannot traverse backwards)*/

    // ---------------------------------------------------------------

    // (3) writing main driver code

    // ---- default constructor ----
    DS::SeqCont::SinglyLinkedList<std::string> mySll;
    std::cout << std::boolalpha << mySll.isEmpty() << std::endl;
    std::cout << mySll.size() << std::endl;

    std::string item1 = "item1";
    std::string item2 = "item2";
    mySll.push_back(item1);
    mySll.push_back(item2);
    mySll.forward_print();

    // ---- initializer list constructor ----
    std::initializer_list<std::string> init_list{"item1", "item2"};
    DS::SeqCont::SinglyLinkedList<std::string> initSLL(init_list);
    initSLL.forward_print();

    // --- testing ---
    std::initializer_list<std::string> init_list2{"item1", "item2", "item3", "item4"};
    DS::SeqCont::SinglyLinkedList<std::string> mySll2(init_list2);
    std::cout << "-- initial list -- \n";
    mySll2.forward_print();
    mySll2.pop_front();
    mySll2.pop_front();
    std::cout << "-- forward print using recursive method after 2x pop_front operation -- \n";
    mySll2.forward_print_recursive();
    std::cout << "-- backward print --" << std::endl;
    mySll2.backward_print();
    mySll2.reverse();
    std::cout << "-- forward print after reverse operation -- \n";
    mySll2.forward_print();
}