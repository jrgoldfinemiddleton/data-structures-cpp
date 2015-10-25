/*********************************************************************
 ** Program Filename: Stack.h
 ** Author: Jason Goldfine-Middleton
 ** Date: 10/24/15
 ** Description: Header for a simple templated class implementing a
 **              stack.  As  Requires C++11 for compilation.
 *********************************************************************/

#ifndef STACK_H
#define STACK_H


template <class T>
class Stack
{
    private:
        // array to hold Stack elements
        T **stk;

        // current position of top of Stack
        int cur_pos;

        // number of positions in stack that must be filled
        // before the Stack will be resized
        int size;

        // resizes the Stack to make room for more elements
        bool grow();

        // copies elements to new array
        bool copy(T **new_stk);

    public:
        // starting size of Stack
        static const int MIN_SIZE = 10;

        // default constructor
        Stack() : cur_pos(0), size(MIN_SIZE) { this->stk = new T*[size]; }
        
        // destructor
        ~Stack();

        // returns top element of Stack
        T* top();

        // removes top element of Stack and returns it
        T* pop();

        // adds a new element to top of Stack
        void push(T &t);

        // accessor functions
        int get_size() { return this->size; }
        int get_cur_pos() { return this->cur_pos; }
};


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

template <class T> bool Stack<T>::grow()
{
    // create new array twice as big as stk
    const int GROW_FACTOR = 2;
    T **new_stk = new T*[this->size * GROW_FACTOR];

    // try to copy all the elements
    if (copy(new_stk))
    {
        // deallocate current array memory
        delete [] this->stk;

        // point stk to new array
        this->stk = new_stk;

        // update size
        this->size *= GROW_FACTOR;

        return true;
    }

    // elements couldn't be copied to nullptr
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
 ** Post-Conditions: new_stk contains the elements that are in stk
 *********************************************************************/

template <class T> bool Stack<T>::copy(T **new_stk)
{
    // if new_stk is a real array
    if (new_stk != nullptr)
    {
        // copy elements in stk to new_stk
        for (int index = 0; index < this->size; ++index)
            new_stk[index] = stk[index];
        
        return true;
    }

    // new_stk was nullptr
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

template <class T> Stack<T>::~Stack()
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

template <class T> T* Stack<T>::top()
{
    // stack empty
    if (this->cur_pos == 0)
        return nullptr;
    
    // return last item in stack
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

template <class T> T* Stack<T>::pop()
{
    // stack empty
    if (this->cur_pos == 0)
        return nullptr;

    // store last item
    T *old_top = this->stk[this->cur_pos];

    // adjust current position of top element
    --(this->cur_pos);

    // return former last item
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

template <class T> void Stack<T>::push(T &t)
{
    // no room to add new item, expand the stack
    if (this->size == this->cur_pos)
        this->grow();

    // adjust the current position of top element
    ++(this->cur_pos);

    // store address of t in stack
    this->stk[this->cur_pos] = &t;
}


#endif
