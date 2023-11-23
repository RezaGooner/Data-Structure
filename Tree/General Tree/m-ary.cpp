#include <iostream>
#include <vector>

using namespace std;

int m ; // degree of m-ary

struct TreeNode {
    int value;
    vector<TreeNode*> children;
};

TreeNode* getNode(TreeNode* root, int value) { // Receive the value of the node and returns the address of the node
    if (root == NULL)
        return NULL;

    if (root->value == value)
        return root;

    for (TreeNode* child : root->children) {
        TreeNode* foundNode = getNode(child, value);
        if (foundNode != NULL)
            return foundNode;
    }

    return NULL;
}

int getNumChildren(const TreeNode* node) { //  Calculate the number of child nodes
    return node->children.size();
}

void addChild(TreeNode* parent, TreeNode* child) { // Add a node to the children of another node
    if (getNumChildren(parent) >= m) {
        cout << "Error! Cannot have more than " << m << " children for each node." << endl;
        return;
    }
    parent->children.push_back(child);
}

void newNode(TreeNode* root) { // Create new node
    int newValue , parentValue;
    cout << "Enter new node value : ";
    cin >> newValue;
    cout << "Enter parent node value : " ;
    cin >> parentValue ;
    
    TreeNode* newNode = new TreeNode;
    newNode->value = newValue;
    TreeNode* parentNode = getNode(root, parentValue);
    if (parentNode != NULL) {
        addChild(parentNode, newNode);
    } else {
        cout << "Error! Parent does not exist." << endl;
    }
    
    cout << endl ;
}

int getHeight(TreeNode* node) { // Calculate the height of the tree
    if (node == NULL)
        return 0;

    int maxHeight = 0;
    for (int i = 0; i < node->children.size(); ++i) {
        maxHeight = max(maxHeight, getHeight(node->children[i]));
    }

    return maxHeight + 1;
}

int countLeaves(TreeNode* node) { // Calculation of the number of leaves (nodes without children)
    if (node == NULL)
        return 0;

    if (node->children.size() == 0)
        return 1;

    int leaves = 0;
    for (int i = 0; i < node->children.size(); ++i) {
        leaves += countLeaves(node->children[i]);
    }

    return leaves;
}

int getNumNodes(int degree, int root) { // Calculate the maximum possible number of nodes considering its degree
    if (degree == 0) {
        return 1;
    }

    int numNodes = 1;

    for (int i = 0; i < degree; i++) {
        int childRoot = root * degree + i;
        numNodes += getNumNodes(degree, childRoot);
    }

    return numNodes;
}


void remove(TreeNode* root, int value) { // Remove node (node or root)
	if (root == NULL)
	return;
	
	if (root->value == value) {
	    delete root;
	    return;
	}
	
	for (int i = 0; i < root->children.size(); ++i) {
    	if (root->children[i]->value == value) {
        	delete root->children[i];
        	root->children.erase(root->children.begin() + i);
        	return;
   		} else {
        	remove(root->children[i], value);
    	}
	}
}

void display(TreeNode* node, int level = 0) { // Display nodes of tree
    if (node == nullptr)
        return;

    for (int i = 0; i < level; ++i)
        cout << "  ";

    cout << node->value << endl;

    for (TreeNode* child : node->children)
        display(child, level + 1);
}

int main() {
	
    cout << "Enter the value of m: ";
    cin >> m;
    cout << endl;

    TreeNode* root = new TreeNode{0};

	for (int i = 0 ; i < 10 ; i++){
		newNode(root);
	}
	
	display(root);
	cout << "****************" << endl ;

    remove(root , 3);

	display(root);

    return 0;
}