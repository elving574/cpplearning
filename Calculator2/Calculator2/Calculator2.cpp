#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    string command;
    while (true) {
        char op;
        float num1, num2;

        cout << "Enter an operator (+, -, *, /, ^), or 'exit' to quit: ";
        cin >> command;
        if (command == "exit")
            break;

        op = command[0];

        cout << "Enter two numbers: ";

        if (!(cin >> num1 >> num2)) {
            cout << "Error! Invalid input." << endl;
            return 1;
        }

        switch (op) {
        case '+':
            cout << "Result: " << num1 + num2;
            break;

        case '-':
            cout << "Result: " << num1 - num2;
            break;

        case '*':
            cout << "Result: " << num1 * num2;
            break;

        case '/': {
            while (num2 == 0) {
                cout << "Error! Division by zero! \n Enter divisor again: ";
                cin >> num2;
            }
            cout << "Result: " << num1 / num2;
        }
                break;

        case '^':
            cout << "Result: " << pow(num1, num2);
            break;

        default:
            cout << "Error! Invalid operator.";
        }
        cout << endl;
    }
    return 0;
}
