#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {  
        head = nullptr;
    }

    void appendSorted(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr || head->data >= value) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void remove(int value) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << value << " removed from the list." << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << value << " not found in the list." << endl;
        }
        else {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
            cout << value << " removed from the list." << endl;
        }
    }

    void display() {
        Node* temp = head;
        if (temp == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;
    string input;

    while (true) {
        cout << "Enter a command (add, addSorted, remove, view, exit): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }
        else if (input == "view") {
            list.display();
        }
        else if (input == "add") {
            string values;
            cout << "Enter values to add (separated by spaces): ";
            getline(cin, values);

            istringstream stream(values);
            int value;
            while (stream >> value) {
                list.append(value);
            }

            cout << "Values added to the list." << endl;
        }
        else if (input == "addSorted") {
            string values;
            cout << "Enter values to add: ";
            getline(cin, values);

            istringstream stream(values);
            int value;
            while (stream >> value) {
                list.appendSorted(value);
            }

            cout << "Values added to the list in sorted order." << endl;
        }
        else if (input == "remove") {
            int value;
            cout << "Enter value to remove: ";
            cin >> value;
            cin.ignore();
            list.remove(value);
        }
        else {
            cout << "Invalid command. Try again." << endl;
        }
    }

    cout << "Program exited." << endl;
    return 0;
}
