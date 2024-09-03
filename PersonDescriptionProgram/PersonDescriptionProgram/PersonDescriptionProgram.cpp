#include <iostream>
#include <string>

using namespace std;

int main() {
    string firstName;
    string lastName;
    string description;

    cout << "Enter first name: \n";
    cin >> firstName;
    cout << "Enter last name: \n";
    cin >> lastName;
    cin.ignore(); // Ignore the newline character left in the buffer
    cout << "Enter person description: \n";
    getline(cin, description);
    cout << firstName << " " << lastName << " is " << description << ".";
    return 0;
}
