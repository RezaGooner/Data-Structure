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
    } else if (root -> right == NULL && root -> left == NULL) {
        return 1 ;
    } else {
        return countLeaf(root->right) + countLeaf(root->left) ;
	}
}

int countMidNode(Node* root) { // calculate number of mid-nodes
    if (root == NULL || (root -> right == NULL && root -> left == NULL)) {
        return 0 ;
    } else {
        return 1 + countMidNode(root -> right) + countMidNode(root -> left) ;
	}
}

Node* find(Node* root, int value) { // find the node with it value
    if (root == NULL){
        return NULL ;
	} if (root -> value == value){
        return root ;
	}
    Node* rightResult = find(root -> right, value);
    if (rightResult != NULL){
        return rightResult ;
	}

    Node* leftResult = find(root -> left, value);
    if (leftResult != NULL){
        return leftResult ;
	}
	
    return NULL ;
}

Node* findParent(Node* root, int value) { // find the parent of the node
    if (root == NULL || (root -> right == NULL && root -> left == NULL)) {
        return NULL ;
	}

    if ((root -> right != NULL && root -> right -> value == value) || (root -> left != NULL && root -> left -> value == value)) {
	    return root ;
    }

    Node* rightResult = findParent(root -> right , value) ;
    if (rightResult != NULL){
        return rightResult ;
    }

    Node* leftResult = findParent(root -> left, value) ;
    if (leftResult != NULL) {
        return leftResult ;
    }

    return NULL ;
}

int count(Node* node, int& counter, int level = 0) { // calculate total of nodes
    if (node == NULL){
        return 0 ;
    }

    counter++ ;

    return count(node -> right , counter , level + 1) + count(node -> left, counter , level + 1) ;
}

void insert(Node* root , int parentValue , Node* node){ // insert node with parent value
	Node* parent = findParent(root , parentValue) ;
	if (parent -> right != NULL){
		parent -> right = node ; 
	} else if (parent -> left != NULL) {
		parent -> left = node ;
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

            if (current -> right == NULL) {
                current -> right = newNode ;
                break ;
            } else if (current -> left == NULL) {
                current -> left = newNode ;
                break ;
            } else {
                nodeQueue.push(current -> right );
                nodeQueue.push(current -> left) ;
            }
        }
    }
}

bool isFull(Node* root) { // check if the tree is full
    if (root == NULL){
        return true ;
    }

    if (root -> right == NULL && root -> left == NULL){
        return true ;
    }

    if (root -> right != NULL && root -> left != NULL){
        return isFull(root -> right) && isFull(root -> left) ;
	}
	
    return false;
}

int calculateHeight(Node* node) { // calculate height of the tree
    if (node == NULL) {
        return 0 ;
    }

    return 1 + max(calculateHeight(node->right), calculateHeight(node->left)) ;
}

int countNodesAtLevel(Node* node, int level) { // calculate number of nodes at each level
    if (node == NULL) {
        return 0 ;
    }

    if (level == 0) {
        return 1 ;
    }

    return countNodesAtLevel(node->right, level - 1) + countNodesAtLevel(node->left , level - 1) ;
}

bool isBalanced(Node* root) {
    if (root == NULL) {
	    return true ;
    }
    int rightChildHeight = calculateHeight(root->right);
    int leftChildHeight = calculateHeight(root->left);
  
    if (abs(rightChildHeight - leftChildHeight ) <= 1 && isBalanced(root->right) && isBalanced(root->left)) {
        return true ;
    }
  
    return false ;
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
        if (parentNode -> right != NULL && parentNode -> right -> value == value) {
            delete parentNode -> right ;
            parentNode -> right = NULL ;
        } else if (parentNode -> left != NULL && parentNode -> left -> value == value) {
            delete parentNode -> left ;
            parentNode -> left = NULL ;
        }
    }
}

void preOrder(Node* root) { // show in preOrder mode
    if (root == NULL){
        return ;
    }

    cout << root->value << " " ;
    preOrder(root -> right)  ;
    preOrder(root -> left) ;
}

void inOrder(Node* root) {  // show in inOrder mode
    if (root == NULL){
        return ;
    }

    inOrder(root -> right) ;
    cout << root -> value << " " ;
    inOrder(root -> left) ;
}

void postOrder(Node* root) {  // show in postOrder mode
    if (root == NULL){
        return ;
    }

    postOrder(root -> right) ;
    postOrder(root -> left) ;
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

    display(node -> right, level + 1) ;
    display(node -> left, level + 1) ;
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
	1402/09/05 ~ 2023/11/26
*/    