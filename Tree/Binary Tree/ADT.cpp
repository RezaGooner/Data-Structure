#include <iostream>
#include <string>

using namespace std ;

template <typename T>
int getASCII(T c) { 
    return static_cast<int>(c);
}

template <typename T>
int compare(const T& str1, const T& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    int minLength = min(len1, len2);

    for (int i = 0; i < minLength; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
    }

    if (len1 < len2) {
        return -1;
    } else if (len1 > len2) {
        return 1;
    }

    return 0;
}


template <typename T>
struct Record{

	T		key   	;
	T		value 	;
	bool	deleted ;
	Record* left  	;
	Record* right 	;	

};

template <typename T>
Record<T>* create(T key , T value){
	Record<T>* newRecord    = new Record<T> ;
	newRecord -> key     = 		  key ;
	newRecord -> value   =	    value ;
	newRecord -> deleted =      false ;
	return newRecord ;
}

template <typename T>
void insert(Record<T>*& root, Record<T>* record) {
    if (root == NULL) {
        root = record;
        return;
    }

    Record<T>* parent = root;
    while (true) {
        if (compare(parent->key, record->key) < 0) {
            if (parent->right != NULL) {
                parent = parent->right;
            } else {
                break;
            }
        } else if (compare(parent->key, record->key) > 0) {
            if (parent->left != NULL) {
                parent = parent->left;
            } else {
                break;
            }
        } else { // record already exists!
            return;
        }
    }

    if (compare(parent->key, record->key) < 0) {
        parent->right = record;
    } else {
        parent->left = record;
    }
}

template <typename T>
void inOrder(Record<T>* root){
	if (root == NULL){
		return ;
	}
	inOrder(root -> left);
	if (!(root -> deleted)){
		cout << root -> key << " : " << root -> value << endl ;
	}
	inOrder(root -> right);
}

int main() {
    Record<string>* root = NULL;
    Record<string>* record1 = create<string>("key1", "value1");
    Record<string>* record2 = create<string>("key2", "value2");
    Record<string>* record3 = create<string>("key3", "value3");
	Record<string>* record4 = create<string>("key4", "value4");
    Record<string>* record5 = create<string>("key5", "value5");
    Record<string>* record6 = create<string>("key6", "value6");
    Record<string>* record7 = create<string>("key7", "value7");
    Record<string>* record8 = create<string>("key8", "value8");

    insert(root, record1);
    insert(root, record2);
    insert(root, record3);
    insert(root, record4);
    insert(root, record5);
    insert(root, record6);
    insert(root, record7);
    insert(root, record8);
    
    inOrder(root);

    return 0;
}