#include <iostream>
using namespace std;
enum TreeOps {
    AddValue = 1,
    InOrder,
    PreOrder,
    PostOrder,
    Exit
};
struct Node {
    int data;
    Node* left, * right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    void add(int value) {
        root = insert(root, value);
    }

    void sort() {
        cout << "\nin order: ";
        inOrder(root);
        cout << endl;
    
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }
    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }
    void postOrder(Node* node) {
        if (node != nullptr) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data << " ";
        }
    }

private:
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            if (node->right == nullptr) {
                node->right = insert(node->right, value);
            }
            else {
                Node* oldRight = node->right;
                node->right = insert(node->right, value);
                node->right->right = oldRight;
            }
        }
        return node;
    }
};



int main() {
    BinaryTree tree;
    TreeOps choice;
    int value;

    do {
        cout << "1. add\n";
        cout << "2. view in order\n";
        cout << "3. view pre order\n";
        cout << "4. view post order\n";
        cout << "5. exit\n";
        cout << "choice: ";
        int ch;
        cin >> ch;
        choice = (TreeOps)ch;

        switch (choice) {
        case AddValue:
            cout << "value to add: ";
            cin >> value;
            tree.add(value);
            break;
        case InOrder:
            tree.sort();
            break;
        case PreOrder:
            tree.preOrder(tree.root);
            break;
        case PostOrder:
            tree.postOrder(tree.root);
            break;
        case Exit:
            cout << "exiting\n";
            break;
        default:
            cout << "invalid choice\n";
        }
    } while (choice != Exit);
    return 0;
}
