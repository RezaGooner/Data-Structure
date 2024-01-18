#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* right;
    Node* left;
};

Node* create(int data) {
    Node* node = new Node{
        data,
        nullptr,
        nullptr
    };
    return node;
}

Node* insert(Node* root, int data) {
    if (!root) {
        return create(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

int count(Node* node){
	int num = 0 ;
	if (!node) {
		return 0 ;
	}
	num ++ ;
	
	num += count(node->left);
	num += count(node->right);
	
	return num ; 
}

int countLeaf(Node* node){
	if (!node){
		return 0 ;
	}
	
	int num = 0 ;
	
	if (!node->left && !node->right){
		return 1 ;
	}
	
	num += countLeaf(node->left);
	num += countLeaf(node->right);
	
	return num ;
}

Node* get(Node* head , int data){
	Node* current = head ;
	
	while (true){
		if (!current){
			return nullptr ;
		}
		
		if (data > current->data){
			current = current->right ; 
		} else if (data < current->data){
			current = current->left ;
		} else {
			return current ;
		}
	}
}

void inOrder(Node* node) {
    if (node) {
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}

Node* getParent(Node* head, int data) {
    Node* current = head;

    while (current) {
        if (current->left && current->left->data == data) {
            return current;
        }

        if (current->right && current->right->data == data) {
            return current;
        }

        if (data > current->data) {
            current = current->right;
        } else if (data < current->data) {
            current = current->left;
        } else {
            return nullptr;
        }
    }

    return nullptr;
}

int successor(Node* head, int data) {
    Node* node = get(head, data);

    if (node) {
        if (node->right) {
            Node* current = node->right;

            while (current && current->left) {
                current = current->left;
            }

            if (current) {
                return current->data;
            }
        } else {
            Node* current = node;

            while (current) {
                Node* parent = getParent(head, current->data);

                if (parent && parent->left == current) {
                    return parent->data;
                }

                current = parent;
            }
        }
    }

    return -999; // node is biggest (not succesor)
}


int predecessor(Node* head, int data) {
    Node* node = get(head, data);

    if (node) {
        if (node->left) {
            Node* current = node->left;

            while (current && current->right) {
                current = current->right;
            }

            if (current) {
                return current->data;
            }
        } else {
            Node* current = node;

            while (current) {
                Node* parent = getParent(head, current->data);

                if (parent && parent->right == current) {
                    return parent->data;
                }

                current = parent;
            }
        }
    }

    return -999; // node is smallest (not predecessor)
}

Node* getMin(Node* head){
	Node* current = head ;
	
	if (!current){
		return nullptr ;
	} 
	
	while (true){
		if (!current->left){
			return current ;
		}
		current = current->left ;
	}
}

void remove(Node* head , int data){	
    Node* node = get(head, data);
	
    if (!head || !node) {
        return;
    }
	
	Node* parent = getParent(head , data);
	
	if (!node->left && !node->right){ // has no children
		
		if (data > parent->data){
			parent->right = nullptr ;
		} else {
			parent->left = nullptr ;
		}
	} else if (node->right && node->left){
		Node* alternative = getMin(node->right);
		if (alternative->right){
			getParent(head , alternative->data)->left = alternative->right ;
		}
		node->data = alternative->data ;
	} else { // has one child
		if (data > parent->data){
			if (node->right){
				parent->right = node->right ;
			} else {
				parent->right = node->left ;
			}
		} else {
			if (node->right){
				parent->left = node->right ;
			} else {
				parent->left = node->left ;
			}
		}
	}
}


int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 18);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 11);
    root = insert(root, 10); // ??????
    root = insert(root, 19);
    root = insert(root, 25);
    root = insert(root, 22);
    root = insert(root, 22); // ??????

    inOrder(root);
    
    cout << endl << "number of nodes : "<< count(root) ;
    cout << endl << "number of leaves : " << countLeaf(root) ;
    
    cout << endl << "successor of 5 : " << successor(root , 5);
    cout << endl << "successor of 11 : " << successor(root , 11);
    cout << endl << "successor of 25 : " << successor(root , 25);
    cout << endl << "successor of 10 : " << successor(root , 10);
    cout << endl << "successor of 3 : " << successor(root , 3);
    cout << endl << "successor of 18 : " << successor(root , 18);
    
	cout << endl ;
    cout << endl << "predecessor of 5 : " << predecessor(root , 5);
    cout << endl << "predecessor of 11 : " << predecessor(root , 11);
    cout << endl << "predecessor of 25 : " << predecessor(root , 25);
    cout << endl << "predecessor of 10 : " << predecessor(root , 10);
    cout << endl << "predecessor of 3 : " << predecessor(root , 3);
    cout << endl << "predecessor of 18 : " << predecessor(root , 18);
    
    cout << "\n\n" << "delete 7 " << endl ;
    remove(root , 7);
	inOrder(root);
	    
    cout << "\n\n" << "delete 11 " << endl ;
    remove(root , 11);
	inOrder(root);
	
	cout << "\n\n" << "delete 19 " << endl ;
    remove(root , 19);
	inOrder(root);
	
	cout << "\n\n" << "delete 28 " << endl ;
    remove(root , 28);
	inOrder(root);

    
    return 0;
}