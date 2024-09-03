#include <iostream>
using namespace std;

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
        return node;
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }
};

int main() {
    BinaryTree tree;
    int choice;
    int value;

    do {
        cout << "1. add\n";
        cout << "2. view in order\n";
        cout << "3. exit\n";
        cout << "choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "value to add: ";
            cin >> value;
            tree.add(value);
            break;
        case 2:
            tree.sort();
            break;
        case 3:
            cout << "exiting\n";
            break;
        default:
            cout << "invalid choice\n";
        }
    } while (choice != 3);
    return 0;
}
