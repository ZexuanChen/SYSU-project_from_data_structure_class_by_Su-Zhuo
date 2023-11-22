#ifndef Stack_h
#define Stack_h
#define MaxNumber 500 //capacity of stack
#include <vector>
using namespace std;

template<typename ElemType>
class Stack {
public:
    Stack();                    //default constructor
    Stack(Stack&);              //copy constructor
    ~Stack() {}                 //destructor
    void clear();               //clear stack elements
    int size();                 //the size of stack
    bool isEmpty();             //judge whether is a empty stack
    bool push(ElemType val);    //push into stack
    bool pop();                 //pop from stack
    ElemType get_top();         //the top element of stack
private:
    ElemType data[MaxNumber];
    int top; //position of stack top, begin with -1
};

template<typename ElemType>
void Stack<ElemType>::clear() {
    top = -1;
    return;
}

template<typename ElemType>
Stack<ElemType>::Stack() {
    clear();
}

template<typename ElemType>
Stack<ElemType>::Stack(Stack& stack) {
    vector<ElemType> v(stack.size());
    int i = 0;
    while (!stack.isEmpty()) {
        stack.pop(v[i]);
    }

    //clear the stack, then copied from another one
    clear();
    for (int i = v.size()-1; i >= 0; i--) {
        push(v[i]);
    }
}

template<typename ElemType>
int Stack<ElemType>::size() {
    //the first element begins with 0
    return top+1;
}

template<typename ElemType>
bool Stack<ElemType>::isEmpty() {
    if (top == -1) return true;
    return false;
}

template<typename ElemType>
bool Stack<ElemType>::push(ElemType val) {
    //If exceeding max capacity, then return false
    if (top == MaxNumber) return false;
    data[++top] = val;
    return true;
}

template<typename ElemType>
bool Stack<ElemType>::pop() {
    //If no elements in stack, then return false
    if (top == -1) return false;
    top--;
    return true;
}

template<typename ElemType>
ElemType Stack<ElemType>::get_top() {
    return data[top];
}

#endif