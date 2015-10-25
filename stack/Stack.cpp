/*********************************************************************
 ** Program Filename: Stack.cpp
 ** Author: Jason Goldfine-Middleton
 ** Date: 10/24/15
 ** Description: Member function implementation file for the Stack
 **              class.  Requires C++11 for compilation.
 *********************************************************************/

#include "Stack.h"


/*********************************************************************
 ** Function: Stack<T>::grow()
 ** Description: Resizes the Stack by doubling the number of positions
 **              available to store elements.  This is an internal
 **              helper for the Stack<T>::push() function.  Returns
 **              true if the elements were copied to a new array and
 **              false otherwise.
 ** Parameters: none
 ** Pre-Conditions: the memory that stk points to has not been deleted
 ** Post-Conditions: stk points to a new address, memory at old address
 **                  is deallocated
 *********************************************************************/

template <class T>
bool Stack<T>::grow()
{
    const int GROW_FACTOR = 2;
    T **new_stk = new T*[this->size * GROW_FACTOR];

    if (copy(new_stk))
    {
        delete [] this->stk;
        this->stk = new_stk;
        this->size *= GROW_FACTOR;
        return true;
    }

    return false;
}


/*********************************************************************
 ** Function: Stack<T>::copy()
 ** Description: Copies the elements of stk to new_stk and copies the
 **              address to which new_stk points to stk.  Returns true
 **              if the elements were copied successfully and false
 **              otherwise.
 ** Parameters: new_stk     the address of the array which will store
 **                         the Stack
 ** Pre-Conditions: for the copy to succeed, new_stk must be at least
 **                 as big as stk
 ** Post-Conditions: stk points to a new address, memory at old address
 **                  is deallocated
 *********************************************************************/

template <class T>
bool Stack<T>::copy(T **new_stk)
{
    if (new_stk != nullptr)
    {
        for (int index = 0; index < this->size; ++index)
            new_stk[index] = stk[index];
        
        return true;
    }

    return false;
}


/*********************************************************************
 ** Function: Stack<T>::~Stack()
 ** Description: Destructs the Stack, deallocating all heap memory.
 ** Parameters: none
 ** Pre-Conditions: the memory that stk points to has not been
 **                 deallocated
 ** Post-Conditions: the memory that stk points to is deallocated
 *********************************************************************/

template <class T>
Stack<T>::~Stack()
{
    delete [] this->stk;
    this->stk = nullptr;
}


/*********************************************************************
 ** Function: Stack<T>::top()
 ** Description: Returns the last (top) element of the Stack.
 ** Parameters: none
 ** Pre-Conditions: cur_pos is nonnegative, the memory that stk points
 **                 to has not been deallocated
 ** Post-Conditions: if the stack is empty, returns nullptr, otherwise
 **                  returns the last element
 *********************************************************************/

template <class T>
T* Stack<T>::top()
{
    if (this->cur_pos == 0)
        return nullptr;
    
    return this->stk[this->cur_pos];
}


/*********************************************************************
 ** Function: Stack<T>::pop()
 ** Description: Removes the last (top) element from the Stack and
 **              returns it.
 ** Parameters: none
 ** Pre-Conditions: cur_pos is nonnegative, the memory that stk points
 **                 to has not been deallocated
 ** Post-Conditions: if the Stack is empty, returns nullptr, otherwise
 **                  returns the last element and decrements cur_pos
 *********************************************************************/

template <class T>
T* Stack<T>::pop()
{
    if (this->cur_pos == 0)
        return nullptr;

    T *old_top = this->stk[this->cur_pos];
    --(this->cur_pos);

    return old_top;
}


/*********************************************************************
 ** Function: Stack<T>::push()
 ** Description: Adds an element to the end (top) of the Stack.  If
 **              there is no room in the stack for more elements, it
 **              resizes the Stack to make room.
 ** Parameters: t   a reference to the element to be added
 ** Pre-Conditions: size > 0 and cur_pos > 0, the memory that stk points
 **                 to has not been deallocated
 ** Post-Conditions: a pointer to t is added to the Stack and cur_pos
 **                  is incremented
 *********************************************************************/

template <class T>
void Stack<T>::push(T &t)
{
    if (this->size == this->cur_pos)
        this->grow();

    ++(this->cur_pos);
    this->stk[this->cur_pos] = &t;
}
