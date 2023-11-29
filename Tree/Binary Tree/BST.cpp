#include <iostream>

using namespace std ;

struct Node{
	int value ;
	Node* right ;
	Node* left ;
};

Node* create(int value){
	Node* newNode = new Node{value} ;
	return newNode ;
}

void insert(Node* &root, Node* node) {
    if (root == NULL) {
        root = node;
        return;
    }

    Node* current = root;
    while (current != NULL) {
        if (node->value > current->value) {
            if (current->right != NULL) {
                current = current->right;
            } else {
                current->right = node;
                return;
            }
        } else if (node->value < current->value) {
            if (current->left != NULL) {
                current = current->left;
            } else {
                current->left = node;
                return;
            }
        } else {
            cout << "Node exists!" ;
            return;
        }
    }
}

Node* find(Node* root , int value){
	Node* current = root ;
	while ( (current -> left != NULL) || (current -> right != NULL) ) {
		if ( value > (current -> value) ){
			if (current -> right != NULL){
				current = current -> right ;
			}
		} else if ( value < (current -> value) ){
			if (current -> left != NULL){
				current = current -> left ;
			}
		} else { // Node found
			return current ;
		}
	}
	
	return NULL ;
}

Node* findParent(Node* root, int value) {
    Node* parent = NULL;
    Node* current = root;
    
    if (root->value == value){
        return NULL;
    }

    while (current != NULL && current->value != value) {
        parent = current;

        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return NULL;
    }

    return parent;
}

	
	/*

	algorithm for remove node :	
	
			(parent)
		   /        \
	  X(node)      (node)X
	     ^            ^
	    /             \
	l-ch       		   r-ch

	This algorithm helps to find the smallest element by scrolling the left links and also 
	find the largest element by scrolling the right links by reducing the number of elements on each side.

	*/


int max(Node* root){
	Node* current = root ;
	int max ;
	while (current != NULL){
		max = current -> value ;
		current = current -> right ;
	}
	return max ;
}

int min(Node* root){
	Node* current = root ;
	int min ;
	while (current != NULL) {
		min = current -> value ;
		current = current -> left ; 
	}
	return min ;
}


Node* getMin(Node* node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node ;
}

void remove(Node* &root, int nodeValue) {
    if (root == NULL) {
        return;
    }
  
    Node* node = find(root, nodeValue);
    Node* parent = findParent(root, nodeValue);

    if (parent == NULL) {
        // node is root
        if (node->left == NULL && node->right == NULL) {
            // nood is leaf
            delete root;
            root = NULL;
        } else if (node->left != NULL) {
            // node has left-child only
            Node* temp = root;
            root = root->left;
            delete temp;
        } else if (node->right != NULL) {
            // node has right-child only
            Node* temp = root;
            root = root->right;
            delete temp;
        }
    } else {
        // nood isn't root
        if (parent->left == node) {
            if (node->left == NULL && node->right == NULL) {
                parent->left = NULL;
                delete node;
            } else if (node->left != NULL && node->right == NULL) {
                parent->left = node->left;
                delete node;
            } else if (node->left == NULL && node->right != NULL) {
                parent->left = node->right;
                delete node;
            } else {
				Node* successor = getMin(node->right);
                Node* successorParent = findParent(root, successor->value);

                if (successorParent != node) {
                    successorParent->left = successor->right;
                    successor->right = node->right;
                }

                successor->left = node->left;
                parent->left = successor;
                delete node;
            }
        } else if (parent->right == node) {
            if (node->left == NULL && node->right == NULL) {
                parent->right = NULL;
                delete node;
            } else if (node->left != NULL && node->right == NULL) {
                parent->right = node->left;
                delete node;
            } else if (node->left == NULL && node->right != NULL) {
                parent->right = node->right;
                delete node;
            } else {
				Node* successor = getMin(node->right);
                Node* successorParent = findParent(root, successor->value);

                if (successorParent != node) {
                    successorParent->left = successor->right;
                    successor->right = node->right;
                }

                successor->left = node->left;
                parent->right = successor;
                delete node;
            }
        }
    }
}

bool isBST(Node* root) {
    if (root == NULL || (root -> right == NULL && root -> left == NULL)) {
        return true ;
    }

    if (root->left != NULL && root->value <= root->left->value) {
        return false ;
    }

    if (root->right != NULL && root->value >= root->right->value) {
        return false ;
    }

    return isBST(root->left) && isBST(root->right) ;
}

void inOrder(Node* root){
	if (root == NULL){
		return ;
	}
	inOrder(root -> left) ;
	cout << root -> value << " " ;
	inOrder(root -> right) ;
}


int successor(Node* root , int value){
	Node* node = find(root , value) ;
	if ( (node -> right) != NULL ) {
		return min(node -> right) ;
	} else {
		while (node != findParent(root , node -> value) -> left ){
			node = findParent(root , node -> value) ;
		}
		return findParent(root , node -> value) -> value ;
	}
}

int predecessor(Node* root , int value){
	Node* node = find(root , value) ;
	if (node -> left != NULL) {
		return max(node -> left) ;
	} else {
		while (node != findParent(root , node -> value) -> right ) {
			node = findParent(root , node -> value ) ;
		}
		return findParent(root , node -> value) -> value ;
	}
}

int main(){
	
	Node* root = new Node{20} ;
	Node* node1 = new Node{10} ;
	Node* node2 = new Node{30} ;
	Node* node3 = new Node{5} ;
	Node* node4 = new Node{15} ;
	Node* node5 = new Node{25} ;
	Node* node6 = new Node{35} ;
	
	root -> right = node2 ;
	root -> left  = node1 ;
	
	node1 -> left  = node3 ; 
	node1 -> right = node4 ;

	insert(root ,  node5 ) ;
	insert(root ,  node6 ) ;
	

	inOrder(root) ;
	cout << endl ;
	remove(root , 10);
	inOrder(root);
	cout << endl ;
	remove(root , 30);
	inOrder(root);
	cout << endl ;
	remove(root , 35);
	inOrder(root);
	
	cout << endl << "Max : " << max(root) << " , Min : " << min(root) ;	
	return 0 ;
}

/*
 	Reza Asadi (Github : RezaGooner)
	1402/09/08 ~ 2023/11/29
*/

