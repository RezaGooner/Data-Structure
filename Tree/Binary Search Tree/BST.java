import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Node {
    int data;
    Node left, right;

    public Node(int value) {
        data = value ;
        left = right = null;
    }
}

class BST {
    Node root;

    BST() {
        root = null;
    }

    void insert(int value) {
        root = insertRec(root, value);
    }

    Node insertRec(Node root, int value) {
        if (root == null) {
            root = new Node(value);
            return root;
        }

        if (value < root.data) {
            root.left = insertRec(root.left, value);
        } else if (value > root.data) {
            root.right = insertRec(root.right, value);
        }

        return root;
    }

    List<Integer> searchLE(int value) {
        List<Integer> result = new ArrayList<>();
        inorder(root, value, result);
        return result;
    }

    void inorder(Node root, int value, List<Integer> nodes) {
        if (root != null) {
            inorder(root.left, value, nodes);
            if (root.data <= value) {
                nodes.add(root.data);
            }
            inorder(root.right, value, nodes);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String[] nodeValues = scanner.nextLine().split(",");

        BST tree = new BST();
        for (String value : nodeValues) {
            tree.insert(Integer.parseInt(value.trim()));
        }

        int number = scanner.nextInt();

        List<Integer> result = tree.searchLE(number);
        for (int i = 0 ; i < result.size() ; i++){
            System.out.print(result.get(i));
            if (i < result.size() - 1){
                System.out.print(",");
            }
        }
    }
}


/*  Reza Asadi (Github : RezaGooner)
	1403/03/02 ~ 2024/05/22
*/
