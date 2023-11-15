#include <iostream>

using namespace std;

struct Node {
    int value;
};

struct Queue {
    Node* nodes;
    int size; // total size of queue
    int len; // Reserved positions in the queue
    Node* front;
    Node* rear;
};

void add(Queue* q, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    q->nodes[q->len] = *newNode;
    q->len++;
    q->rear = &q->nodes[q->len - 1];
}

Node peek(Queue* q) {
    return *q->front;
}

Node poll(Queue* q) {
    //q->nodes[q->len - 1] = NULL;
    q->len--;
    q->rear = &q->nodes[q->len - 1];
}

Node* rear(Queue* q) {
    return &q->nodes[q->len - 1];
}

Queue* createQ(int size) {
    Queue* q = new Queue;
    q->len = 0;
    q->size = size;
    Node* nodeArray = new Node[size];
    q->nodes = nodeArray;
    q->front = nullptr;

    return q;
}

int main() {

    return 0;
}