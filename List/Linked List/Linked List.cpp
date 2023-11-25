#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int length(Node* head) {
    int counter = 0 ;
    Node* current = head ;
    while (current != NULL) {
        counter ++ ;
        current = current -> next ;
    }
    return counter ;
}

void insert(Node*& head , int index , int newData) {
    int Length = length(head) ;

	assert(index >= 0);    
    assert(index <= Length);

    
	Node* newNode   = new Node ; 
    newNode -> data = newData ;

    if (index == 0) {
        newNode -> next = head ;
    	head = newNode ;
        return ;
    }
    

    Node* current = head ;
    
    for (int i = 1; i < index ; i++) {
        if (current -> next == NULL) {
            return ;
        }
        current = current -> next ;
    }

    newNode -> next = current -> next ;
    current -> next = newNode ;
}



bool isEmpty(Node*& head){
	if (length(head) == 0){
		return true ;
	} else {
		return false ;
	}
}	

int get(Node* head, int index) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) {
        	assert(current != NULL);
            //return NULL;
        }
        current = current->next;
    }
    if (current == NULL) {
        assert(current != NULL);
        //return NULL;
    }
    return current->data;
}

int indexOf(Node* head, int element) {
    Node* current = head;
    if (current == NULL){
    	assert(current != NULL);
	}
   	if (current -> next == NULL){
		if (current -> data != element){
			assert(current -> next != NULL && current -> data == element);
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
    bool element_no_exist = false ;
    assert(element_no_exist);
    //return -1;
}


void add(Node*& head, int newData) {
    Node* newNode = new Node;
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void remove(Node*& head, int element) {
    Node* current = head;
    Node* previous = NULL;
    
    while (current != NULL && current->data != element) {
        previous = current;
        current = current->next;
    }
    
    if (current != NULL) {
        if (previous == NULL) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
}

void removeByIndex(Node*& head, int index) {
    if (head == NULL){
        return;
	}
    Node* current = head;
    Node* previous = NULL;
    int counter = 0;
    
    while (current != NULL && counter < index) {
        previous = current;
        current = current->next;
        counter++;
    }
    
    if (current != NULL) {
        if (previous == NULL) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
}


void reverse(Node*& head) {
    Node* past = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = past;
        past = current;
        current = next;
    }
    head = past;
}

void sort(Node*& head) {
	assert(head != NULL);

    bool sorted = false ;
    while (!sorted) {
        sorted = true;
        Node* current = head;
        Node* past = NULL;

        while (current->next != NULL) {
            Node* nextNode = current->next;
            if (current->data > nextNode->data) {
                if (past == NULL) {
                    current->next = nextNode->next;
                    nextNode->next = current;
                    head = nextNode;
                } else {
                    past->next = nextNode;
                    current->next = nextNode->next;
                    nextNode->next = current;
                }
                sorted = false;
            }
            past = current;
            current = nextNode;
        }
    }
}

int pop(Node*& head) {
    assert(head != NULL);
    
    if (head->next == NULL) {
        int value = head->data;
        delete head;
        head = NULL;
        return value;
    }
    
    Node* current = head;
    Node* prev = NULL;
    
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    
    int value = current->data;
    delete current;
    prev->next = NULL;
    
    return value;
}

void display(Node* head) {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node* head = NULL;
	
    return 0;
}


/*  Reza Asadi (Github : RezaGooner)
	1402/08/13 ~ 2023/11/04
*/