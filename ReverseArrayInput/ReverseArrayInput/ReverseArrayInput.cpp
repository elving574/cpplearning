#include <iostream>
#include <vector>
using namespace std;

void reverseArrayInput();
void reverseStrArrayInput();

int main()
{
    string choice;
    while (true) // Infinite loop
    {
        restart:
        cout << "Input the type of array you want (string/int/exit) CASE SENSITIVE: ";
        cin >> choice;
        if (choice == "exit") // Check for exit
        {
            break; // Exit the loop if the user inputs "exit"
        }
        else if (choice == "string")
        {
            reverseStrArrayInput();
        }
        else if (choice == "int")
        {
            reverseArrayInput();
        }
        else
        {
            cout << "Invalid input, try again.\n";
            goto restart;
        }
    }
    return 0;
}

void reverseArrayInput()
{
    int length;
    cout << "Enter the length of the array: ";
    cin >> length;
    vector<int> myNumbers;

    // Input the array elements
    cout << "Enter " << length << " numbers separated by spaces: ";
    for (int i = 0; i < length; i++)
    {
        int tempInput;
        cin >> tempInput;
        myNumbers.push_back(tempInput);
    }

    // Printing the original array
    cout << "Original Array: ";
    for (int i = 0; i < length; i++)
    {
        cout << myNumbers[i] << " ";
    }
    cout << endl;

    // Printing the array in reverse order
    cout << "Reversed Array: ";
    for (int j = length - 1; j >= 0; j--)
    {
        cout << myNumbers[j] << " ";
    }
    cout << endl;
}

void reverseStrArrayInput()
{
    int length;
    cout << "Enter the length of the array: ";
    cin >> length;
    vector<string> myString;

    // Input the array elements
    cout << "Enter " << length << " strings separated by spaces: ";
    for (int i = 0; i < length; i++)
    {
        string tempInput;
        cin >> tempInput;
        myString.push_back(tempInput);
    }

    // Printing the original array
    cout << "Original Array: ";
    for (int i = 0; i < length; i++)
    {
        cout << myString[i] << " ";
    }
    cout << endl;

    // Printing the array in reverse order
    cout << "Reversed Array: ";
    for (int j = length - 1; j >= 0; j--)
    {
        cout << myString[j] << " ";
    }
    cout << endl;
}