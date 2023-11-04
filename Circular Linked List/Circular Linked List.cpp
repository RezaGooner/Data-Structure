#include <iostream>
#include <cassert>
using namespace std ;

struct Node {
    int data;
    Node* next;
};

void add(Node*& head, int Data) {
    Node* newNode = new Node;
    newNode->next = NULL;
    newNode->data = Data;
    if (head == NULL) {
        head = newNode;
        head->next =NULL;
    } else {
        Node* current = head;
        while (current->next != NULL && current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }
}

void insert(Node*& head, int index, int element) {
	assert(index >= 0);
	
    Node* current = head;
	Node* newNode = new Node;
    newNode->data = element;
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        for (int i = 0; i < index - 1; i++) {
            if (current == NULL) {
                return;
            }
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int length(Node*& head){
	Node* current = head ;
	int counter = 0 ;
	while (current != NULL){
		counter ++ ;
	 	if (current -> next == head) {
	 		break ;
		}
		current = current -> next ;
	}
	return counter ;
}

bool isEmpty(Node*& head){
	if (length(head) == 0){
		return true ;
	} else {
		return false ;
	}
}

int get(Node*& head, int index) {
	assert(head != NULL);
    Node* current = head;
    for (int i = 0; i < index; i++) {
		assert(current != NULL);
        current = current->next;
    }

    return current->data;
}

int indexOf(Node* head, int element) {
    Node* current = head;
    if (current == NULL){
    	return -1 ;
	}
   	if (current -> next == NULL){
		if (current -> data != element){
			return -1 ;
		}
	}
    int counter = 0;
    while (current != NULL) {
        if (current->data == element) {
            return counter;
        }
        current = current->next;
        counter++;
    }
    return -1;
}

void display(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
        if (current == head) {
            break;
        }
    }
    cout << endl;
}


void remove(Node*& head, int element) {
	assert(head != NULL);

    Node* current = head;
    Node* prev = NULL;
    
    if (head -> data == element){
    	int len = length(head);
    	for ( int i = 1 ; i < len ; i++){
    		current = current -> next ;
		}
		current -> next = head -> next ;
		Node* temp = head ;
		head = head -> next ;
		delete temp ;
		return ;
	}

    while (current != NULL && current->data != element) {
        prev = current;
        current = current->next;
    }

	assert(current != NULL);

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}

void removeByIndex(Node*& head, int index) {
    assert (head != NULL) ;

    Node* current = head;
    Node* prev = NULL;

    for (int i = 0; i < index; i++) {
        assert (current != NULL);
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}


int count(Node*& head , int element){
	Node* current = head ;
	int len = length(head) ;
	int counter = 0 ;
	for ( int i = 0 ; i < len ; i ++){
		if (current -> data == element ){
			counter ++ ;
		}
		current = current -> next ;
	}
	return counter ;
}
 
int main() {
	Node* head = NULL ;

    return 0;
}

/*  Reza Asadi (Github : RezaGooner)
	1402/08/14 ~ 2023/11/05
*/
