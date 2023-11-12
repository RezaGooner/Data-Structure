#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

struct Stack {
    int top; // index of top of stack
    int elements[MAX_SIZE]; 
};

bool isEmpty(Stack& stack) {
    if (stack.top == -1) {
        return true;
    }
    return false;
}

bool isFull(Stack& stack) {
    if (stack.top == MAX_SIZE - 1) {
        return true;
    }
    return false;
}

void push(Stack& stack, int value) {
    if (isFull(stack)) {
        cout << "Stack overflow!" << endl;
        return;
    }
    stack.elements[++stack.top] = value;
}

void pop(Stack& stack) {
    if (isEmpty(stack)) {
        cout << "Stack underflow!" << endl;
        return;
    }
    stack.elements[stack.top--] = 0;
}

int top(Stack& stack) {
    if (isEmpty(stack)) {
        // cout << "Stack is empty!" << endl;
        return 0;
    }
    return stack.elements[stack.top];
}

int main() {
    Stack stack;
    stack.top = -1; 

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/08/22 ~ 2023/11/13
*/
