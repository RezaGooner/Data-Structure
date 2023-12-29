#include <iostream>

using namespace std;

struct Node {
    int value = 0;
    Node* right;
    Node* left;
};

Node* create(int value) {
    Node* newNode = new Node{value};
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(Node*& root, Node* node) {
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
            cout << "Node exists!";
            return;
        }
    }
}

Node* find(Node* root, int value) {
    Node* current = root;

    while (current != NULL) {
        if (value > current->value) {
            current = current->right;
        } else if (value < current->value) {
            current = current->left;
        } else { // Node found
            return current;
        }
    }

    return NULL;
}

Node* findParent(Node* root, int value) {
    Node* parent = NULL;
    Node* current = root;

    if (root->value == value) {
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

Node* max(Node* node) {
    if (node == NULL) {
        return NULL; 
    }
    
    Node* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    
    return current;
}

Node* min(Node* node) {
    if (node == NULL) {
		return NULL; 
    }
    
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

int getMin(Node* node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node -> value;
}

/* 

	The `searchKey` function iteratively traverses the tree and searches for the given key (`value`) in the subtree rooted at `root`. 
	In each iteration, it first assigns the parent to the current node (`root`), and then based on the comparison of the key with the value of the node, 
	it goes to the left or right subtree. If the key is less than the value of the node, it goes to the left subtree, otherwise, it goes to the right subtree. 
	The iterative process continues until the desired node is found or the current node (`root`) becomes `NULL` (if the key is not present in the tree).
	
	In addition to the search operation, the `searchKey` function receives the parent of the target node (`Node* parent`) and 
	assigns the parent to the current node (`root`) in each iteration. This allows easy access to the parent node, which is crucial for deletion operations. 
	Having direct access to the parent node enables necessary modifications and ensures that the deletion operation is performed correctly without unintended complications.
	
	When you want to remove a node, you need to have access to the node's parent, which is used for necessary changes related to the deleted node. 
	If you don't have direct access to the parent node, the deletion operation may not be performed correctly or may encounter errors. 
	The `searchKey` function ensures proper access to the parent node, guaranteeing the correctness of the deletion operation and preventing unintended complexities.
	
	By utilizing the `searchKey` function to find the parent of the target node during deletion, 
	you can ensure that the deletion operation works correctly and avoid unintended issues.

*/
void searchKey(Node*& root, int value, Node*& parent) {
    while (root != NULL && root->value != value) {
        parent = root;

        if (value < root->value) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
}

void remove(Node* root, int value) {
    Node* parent = NULL;
    Node* current = root;

    // search key in the BST and set its parent pointer
    searchKey(current, value, parent);

    // return if the key is not found in the tree
    if (current == NULL) {
        return;
    }

    // Case 1: node to be deleted has no children (it is a leaf node)
    if (current->left == NULL && current->right == NULL) {
        // if the node to be deleted is not a root node, then set its
        // parent left/right child to NULL
        if (current != root) {
            if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        // if the tree has only a root node, delete it and set root to nullptr
        else {
            root = NULL;
        }
        delete current;
    }

    // Case 2: node to be deleted has two children
    else if (current->left && current->right) {
        // find its in-order predecessor node
        Node* predecessor = min(current->right);

        // store the value of the predecessor in the current node
        int predecessorValue = predecessor->value;

        // recursively delete the predecessor. Note that the predecessor
        // will have at most one child (right child)
        remove(root, predecessor->value);

        // copy the value of the predecessor to the current node
        current->value = predecessorValue;
    }

    // Case 3: node to be deleted has only one child
    else {
        // choose a child node
        Node* child = (current->left) ? current->left : current->right;

        // if the node to be deleted is not a root node, then set its parent
        // to its child
        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }
        delete current;  // deallocate the memory
    }
}

void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    cout << root->value << " ";
    inOrder(root->right);
}

int successor(Node* root, int value) {
    Node* node = find(root, value);

    if (node == NULL) {
        return -1; // Node with the given value does not exist
    }

    if (node->right != NULL) {
        return min(node->right)->value;
    } else {
        Node* parent = findParent(root, node->value);
        if (parent == NULL) {
            return -1; // Node is the root, no successor exists
        }

        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = findParent(root, node->value);
        }

        if (parent == NULL) {
            return -1; // Node is the rightmost leaf, no successor exists
        }
        return parent->value;
    }
}

int predecessor(Node* root, int value) {
    Node* node = find(root, value);

    if (node == NULL) {
        return -1; // Node with the given value does not exist
    }

    if (node->left != NULL) {
        return max(node->left) -> value;
    } else {
        Node* parent = findParent(root, node->value);
        if (parent == NULL) {
			return -1; // No predecessor exists
        }
        while (node != parent->right) {
            node = parent;
            parent = findParent(root, node->value);
            if (parent == NULL) {
                return -1; // No predecessor exists
            }
        }
        return parent->value;
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


int main() {
    Node* root = NULL;
    insert(root, create(20));
    insert(root, create(10));
    insert(root, create(30));
    insert(root, create(5));
    insert(root, create(15));
    insert(root, create(25));
    insert(root, create(35));
    insert(root, create(22));
    insert(root, create(27));

    cout << "inOrder traversal : ";
    inOrder(root);
    cout << endl;

    remove(root, 30);
    cout << "inOrder traversal after remove node<30> : ";
    inOrder(root);
	cout << endl << successor(root , 10) << endl << predecessor(root , 10) << endl << (isBST(root) ? "Yes" : "No") << endl << endl ;
	
	
	inOrder(root) ;
	cout << endl ;
	remove(root , 10);
	inOrder(root);
	cout << endl ;
	remove(root , 27);
	inOrder(root);
	cout << endl ;
	remove(root , 22);
	inOrder(root);
	
	
	cout << endl << "----------------" << endl;
	cout << endl << "Max : " << max(root) -> value << " , Min : " << min(root) -> value	 ;	
	cout << endl << find(root , 5) -> value << endl ;
	cout << min(root) -> value ;
	cout << endl << endl << successor(root , 5) << endl << predecessor(root , 10) ;

    return 0;
}

/*
 	Reza Asadi (Github : RezaGooner)
	1402/09/08 ~ 2023/11/29
*/

