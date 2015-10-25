/*********************************************************************
 ** Program Filename: main.cpp
 ** Author: Jason Goldfine-Middleton
 ** Date: 10/24/15
 ** Description: Tests the templated Stack class with ints and
 **              std::strings.  Demos the top(), pop(), push(),
 **              get_size(), and get_cur_pos() member functions of the
 **              Stack class.
 ** Input: int, std::string
 ** Output: std::cout, information about operations and state of Stacks
 *********************************************************************/

#include "Stack.h"

#include <iostream>
#include <string>


template <class T>
void print_size_pos(Stack<T> &stack);

template <class T>
void top(Stack<T> &stack);

template <class T>
void pop(Stack<T> &stack);

template <class T>
void push(Stack<T> &stack, T &t);


int main()
{
    // create stack of ints
    Stack<int> stack;

    // print the stacks size and current position of top element
    print_size_pos(stack);


    int arr[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    // test the three main functions that define a stack
    push(stack, arr[1]);
    top(stack);
    pop(stack);


    push(stack, arr[1]);
    push(stack, arr[2]);
    top(stack);
    push(stack, arr[3]);
    pop(stack);
    pop(stack);
    pop(stack);
    
    // stack should now be empty
    print_size_pos(stack);

    // should print that stack is empty
    pop(stack);
    print_size_pos(stack);

    // add 12 elements to verify that stack grows
    for (int i = 0; i < 12; ++i)
    {
        std::cout << (i + 1) << '\t';
        push(stack, arr[i]);
    }

    pop(stack);
    top(stack);

    // create stack of strings
    Stack<std::string> stk_str;
    std::string str_arr[] { "hi", "this", "is", "bob" };

    pop(stk_str);
    top(stk_str);
    top(stk_str);
    print_size_pos(stack);

    for (int i = 3; i >= 0; --i)
    {
        std::cout << (4 - i) << '\t';
        push(stk_str, str_arr[i]);
    }

    return 0;
}


/*********************************************************************
 ** Function: print_size_pos()
 ** Description: Prints the size of the Stack and the current position
 **              of the top element to the console.
 ** Parameters: stack   a reference to the Stack
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/

template <class T>
void print_size_pos(Stack<T> &stack)
{
    std::cout << "The stack's size:      " << stack.get_size() <<
                 "\nThe stack's position:  " << stack.get_cur_pos() <<
                 "\n\n";
}


/*********************************************************************
 ** Function: top()
 ** Description: Prints information about the top element of stack
 **              or states that stack is empty.
 ** Parameters: stack   a reference to the Stack
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/

template <class T>
void top(Stack<T> &stack)
{
    std::cout << "Attempting to get the top element.\n";
    T *top = stack.top();

    if (top != nullptr)
        std::cout << "The top of the stack is \"" << *top << "\".\n\n";
    else
        std::cerr << "The stack is empty!\n\n";
}


/*********************************************************************
 ** Function: pop()
 ** Description: Removes the top element from stack if there is one
 **              and prints information about it, otherwise states
 **              that stack is empty.
 ** Parameters: stack   a reference to the Stack
 ** Pre-Conditions: none
 ** Post-Conditions: if stack was not empty, the top element of the
 **                  stack is removed and the current position of the
 **                  top element is updated
 *********************************************************************/

template <class T>
void pop(Stack<T> &stack)
{
    std::cout << "Attempting to pop the top element.\n";
    T *pop = stack.pop();

    if (pop != nullptr)
        std::cout << "The top of the stack is \"" << *pop << "\".\n\n";
    else
        std::cerr << "The stack is empty!\n\n";
}


/*********************************************************************
 ** Function: push()
 ** Description: Adds element t to the top of stack and prints
 **              the size of stack and the current position of the new
 **              top element.
 ** Parameters: stack   a reference to the Stack
 **             t       a reference to the element to add
 ** Pre-Conditions: none
 ** Post-Conditions: t is added to the top of stack and the current
 **                  position of the top element is updated
 *********************************************************************/

template <class T>
void push(Stack<T> &stack, T &t)
{
    std::cout << "Attempting to push \"" << t << "\" to stack.\n";
    stack.push(t);

    // print the size of stack and the position number of top element
    print_size_pos(stack);
}

