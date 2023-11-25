#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

int countLeaf(Node* root) { // calculate number of leaves
    if (root == NULL) {
        return 0 ;
    } else if (root -> left == NULL && root -> right == NULL) {
        return 1 ;
    } else {
        return countLeaf(root->left) + countLeaf(root->right) ;
	}
}

int countMidNode(Node* root) { // calculate number of mid-nodes
    if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
        return 0 ;
    } else {
        return 1 + countMidNode(root -> left) + countMidNode(root -> right) ;
	}
}

Node* find(Node* root, int value) { // find the node with it value
    if (root == NULL){
        return NULL ;
	} if (root -> value == value){
        return root ;
	}
    Node* leftResult = find(root -> left, value);
    if (leftResult != NULL){
        return leftResult ;
	}

    Node* rightResult = find(root -> right, value);
    if (rightResult != NULL){
        return rightResult ;
	}
	
    return NULL ;
}

Node* findParent(Node* root, int value) { // find the parent of the node
    if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
        return NULL ;
	}

    if ((root -> left != NULL && root -> left -> value == value) || (root -> right != NULL && root -> right -> value == value)) {
	    return root ;
    }

    Node* leftResult = findParent(root -> left , value) ;
    if (leftResult != NULL){
        return leftResult ;
    }

    Node* rightResult = findParent(root -> right, value) ;
    if (rightResult != NULL) {
        return rightResult ;
    }

    return NULL ;
}

int count(Node* node, int& counter, int level = 0) { // calculate total of nodes
    if (node == NULL){
        return 0 ;
    }

    counter++ ;

    count(node -> left , counter , level + 1) ;
    count(node -> right, counter , level + 1) ;

    return counter ;
}

void insert(Node* root , int parentValue , Node* node){ // insert node with parent value
	Node* parent = findParent(root , parentValue) ;
	if (parent -> left != NULL){
		parent -> left = node ; 
	} else if (parent -> right != NULL) {
		parent -> right = node ;
	} else {
		cout << "Node cann't accept any other children!" << endl ;
	}
}

void create(Node*& root) { // create new node
    int value;
    cout << "Enter new value : ";
    cin >> value;
    Node* newNode = new Node{value, NULL, NULL} ;

    if (root == NULL) {
        root = newNode ;
    } else {
        queue<Node*> nodeQueue ;
        nodeQueue.push(root) ;

        while (!nodeQueue.empty()) {
            Node* current = nodeQueue.front() ;
            nodeQueue.pop() ;

            if (current -> left == NULL) {
                current -> left = newNode ;
                break ;
            } else if (current -> right == NULL) {
                current -> right = newNode ;
                break ;
            } else {
                nodeQueue.push(current -> left );
                nodeQueue.push(current -> right) ;
            }
        }
    }
}

bool isFull(Node* root) { // check if the tree is full
    if (root == NULL){
        return true ;
    }

    if (root -> left == NULL && root -> right == NULL){
        return true ;
    }

    if (root -> left != NULL && root -> right != NULL){
        return isFull(root -> left) && isFull(root -> right) ;
	}
	
    return false;
}

int calculateHeight(Node* node) { // calculate height of the tree
    if (node == NULL) {
        return 0 ;
    }

    int leftHeight = calculateHeight(node->left) ;
    int rightHeight = calculateHeight(node->right) ;

    return 1 + max(leftHeight, rightHeight) ;
}

int countNodesAtLevel(Node* node, int level) { // calculate number of nodes at each level
    if (node == NULL) {
        return 0 ;
    }

    if (level == 0) {
        return 1 ;
    }

    int leftCount = countNodesAtLevel(node->left, level - 1) ;
    int rightCount = countNodesAtLevel(node->right, level - 1) ;

    return leftCount + rightCount ;
}

bool isPerfect(Node* root) { // check if the tree is perfect
    int height = calculateHeight(root) ;

    for (int level = 0; level < height - 1; level++) {
        int expectedNodeCount = pow(2, level) ;
        int actualNodeCount = countNodesAtLevel(root, level) ;

        if (actualNodeCount != expectedNodeCount) {
            return false ;
        }
    }
	if (!isFull(root)) {
		return false ;
	}
    
	return true ;
}

bool isComplete(Node* root) { // check if the tree is complete
    queue<Node*> queue ;
    queue.push(root) ;

    bool endReached = false ;

    while (!queue.empty()) {
        Node* current = queue.front() ;
        queue.pop() ;
		
		if (current == NULL) {
            endReached = true ;
        } else {
		    if (endReached) {
                return false ;
            }
            queue.push(current -> left) ;
            queue.push(current -> right) ;
        }
    }
    return true ;
}

void remove(Node*& root, int value) { // remove node with it value
    Node* parentNode = findParent(root, value) ;
    if (parentNode != NULL) {
        if (parentNode -> left != NULL && parentNode -> left -> value == value) {
            delete parentNode -> left ;
            parentNode -> left = NULL ;
        } else if (parentNode -> right != NULL && parentNode -> right -> value == value) {
            delete parentNode -> right ;
            parentNode -> right = NULL ;
        }
    }
}

void preOrder(Node* root) { // show in preOrder mode
    if (root == NULL){
        return ;
    }

    cout << root->value << " " ;
    preOrder(root -> left)  ;
    preOrder(root -> right) ;
}

void inOrder(Node* root) {  // show in inOrder mode
    if (root == NULL){
        return ;
    }

    inOrder(root -> left) ;
    cout << root -> value << " " ;
    inOrder(root -> right) ;
}

void postOrder(Node* root) {  // show in postOrder mode
    if (root == NULL){
        return ;
    }

    postOrder(root -> left) ;
    postOrder(root -> right) ;
    cout << root -> value << " " ;
}

void display(Node* node, int level = 0) {  // show in normal mode
    if (node == NULL){
        return ;
    }

    for (int i = 0; i < level; ++i) {
        cout << "  " ;
    }

    cout << node -> value << endl ;

    display(node -> left, level + 1) ;
    display(node -> right, level + 1) ;
}

int main() {
    Node* root = NULL ;

    int numNodes ;
    cout << "Enter the number of nodes : " ;
    cin >> numNodes ;
	cout << endl ;
	
    for (int i = 0; i < numNodes; i++) {
        cout << "Creating node " << i + 1 << endl ;
        create(root) ;
    }

	int counter = 0 ;
	cout << endl << "Number of nudes : " << count(root , counter) << endl << endl ;  

    cout << "Tree:" << endl ;
    display(root) ;

    cout << endl << "Pre-order traversal : " ;
    preOrder(root) ;
    cout << endl ;

    cout << "In-order traversal : " ;
    inOrder(root) ;
    cout << endl ;

    cout << "Post-order traversal : " ;
    postOrder(root) ;
    cout << endl << endl ;

    cout << "Is the tree full? " << (isFull(root) ? "Yes" : "No") << endl ;
    cout << "Is the tree complete? " << (isComplete(root) ? "Yes" : "No") << endl ;
    cout << "Is the tree perfect? " << (isPerfect(root) ? "Yes" : "No") << endl << endl ;
    
    cout << "Number of leaves : " << countLeaf(root) << endl ; 
    cout << "Number of mid-nodes : " << countMidNode(root) ;

    return 0;
}

/*
    Reza Asadi (Github : RezaGooner)
	1402/09/04 ~ 2023/11/25
*/    