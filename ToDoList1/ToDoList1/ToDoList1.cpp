#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to display the menu options
void displayMenu() {
    cout << "===== To-Do List Menu =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Exit" << endl;
    cout << "===========================" << endl;
}

int main() {
    vector<string> tasks; // Vector to store tasks

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter task: ";
            string task;
            cin.ignore();
            getline(cin, task);
            tasks.push_back(task);
            cout << "Task added successfully!" << endl;
            break;
        }
        case 2: {
            cout << "Tasks:" << endl;
            for (int i = 0; i < tasks.size(); i++) {
                cout << i + 1 << ". " << tasks[i] << "\n" << endl;
            }
            break;
        }
        case 3: {
            if (tasks.empty()) {
                cout << "No tasks to mark as completed." << endl;
            }
            else {
                cout << "Enter task number to mark as completed: ";
                int taskNum;
                cin >> taskNum;
                if (taskNum >= 1 && taskNum <= tasks.size()) {
                    tasks.erase(tasks.begin() + taskNum - 1);
                    cout << "Task marked as completed!" << endl;
                }
                else {
                    cout << "Invalid task number!" << endl;
                }
            }
            break;
        }
        case 4: {
            cout << "Exiting program." << endl;
            break;
        }
        default: {
            cout << "Invalid choice! Please enter a valid option." << endl;
        }
        }
    } while (choice != 4);

    return 0;
}
