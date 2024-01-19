#include <iostream>
#include <string>

#define ALPHA_NUM 26

using namespace std;

struct Node {
    bool isLeaf;
    Node* characters[ALPHA_NUM];
};

Node* create() {
    Node* node = new Node;
    node->isLeaf = false;

    for (int i = 0; i < ALPHA_NUM; i++) {
        node->characters[i] = nullptr;
    }

    return node;
}

void insert(Node* head, string text) {
    Node* current = head;
    for (char Ch : text) {
        if (current->characters[Ch - 'a'] == nullptr)
            current->characters[Ch - 'a'] = create();
        current = current->characters[Ch - 'a'];
    }

    current->isLeaf = true;
}

bool search(Node* head, string text) {
    if (!head) return false;

    Node* current = head;
    for (char Ch : text) {
        if (current->characters[Ch - 'a'] == nullptr) {
            return false;
        }
        current = current->characters[Ch - 'a'];
    }

    return current->isLeaf;
}

void remove(Node* head, string text) {
    if (!head) return ;

    Node* current = head;
    for (char Ch : text) {
        if (current->characters[Ch - 'a'] == nullptr) {
            return ;
        }
        current = current->characters[Ch - 'a'];
    }

    current->isLeaf = false;
}

int main() {

    Node* head = create();


    insert(head, "apple");
    insert(head, "banana");


    cout << (search(head, "apple") ? "apple in trie" : "apple not in trie") << endl;   
    cout << (search(head, "banana") ? "banana in trie" : "banana not in trie") << endl;  
    cout << (search(head, "orange") ? "orange in trie" : "orange not in trie") << endl;  
    
    remove(head , "apple");
    cout << "remove apple...\n" ;
    cout << (search(head, "apple") ? "apple in trie" : "apple not in trie") << endl;   

    return 0;
}