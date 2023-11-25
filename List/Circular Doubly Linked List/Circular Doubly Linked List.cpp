#include <iostream>
#include <cassert>
using namespace std;

struct Node {
	int data ;
	Node* next ;
	Node* past ;	
};

void add(Node*& head , int Data){
	Node* newNode = new Node ;
	newNode -> past = NULL ;
	newNode -> next = NULL ;
	newNode -> data = Data ;
	if (head == NULL){
		head = newNode ;
		head -> next = head ;
		head -> past = head ;
	} else {
		Node* current = head ;
		while (current -> next != NULL && current -> next != head){
			current = current -> next ;
			if (current == head){
				break ;
			}
		}
		current -> next = newNode ;
		newNode -> past = current ;
		head -> past = newNode ;
		newNode -> next = head ;	
	}

}

void insert(Node*& head , int index , int element){
	Node* current = head ;
	Node* newNode = new Node ;
	newNode -> data = element ;
	newNode -> next = NULL ;
	newNode -> past = NULL ;
	for (int i = 0 ; i < index - 1 ; i++){
		assert ( current != NULL);
		current = current -> next ;
	}
	newNode -> past = current ;
	newNode -> next = current -> next ;
	current -> next -> past = newNode ;
	current -> next = newNode ;
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
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
		assert ( current != NULL);
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

void remove(Node*& head , int element){
	Node* current = head ;
	while (current != NULL && current -> next != head){
		if (current -> data == element){
			current -> past -> next = current -> next ;
			current -> next -> past = current -> past ;
			delete current ;
			return ;
					
		}
		current = current -> next ;
	}
}

void removeByIndex(Node* head , int index){
	Node* current = head ;

	for (int i = 0 ; i < index ; i++){
		if (current == NULL){
			return ;
		}
		current = current -> next ;
	}
	current -> past -> next = current -> next ;
	current -> next -> past = current -> past ; 
	delete current ;
}

void sort(Node*& head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        Node* current = head;
        Node* last = NULL;

        while (current->next != last && current -> next != head) {
            if (current->data > current->next->data) {
                if (current == head) {
                    Node* nextNode = current->next;
                    current->next = nextNode->next;
                    nextNode->next = current;
                    current->past = nextNode;
                    nextNode->past = NULL;
                    head = nextNode;
                    if (current->next != NULL) {
                        current->next->past = current;
                    }
                } else {
                    Node* prevNode = current->past;
                    Node* nextNode = current->next;
                    prevNode->next = nextNode;
                    current->next = nextNode->next;
                    nextNode->past = prevNode;
                    nextNode->next = current;
                    current->past = nextNode;
                    if (current->next != NULL) {
                        current->next->past = current;
                    }
                }
                sorted = false;
            } else {
                current = current->next;
            }
        }
        last = current;
    }
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


int main(){
	Node* head = NULL ;
	
	return 0 ;
	
}

/*  Reza Asadi (Github : RezaGooner)
	1402/08/14 ~ 2023/11/05
*/