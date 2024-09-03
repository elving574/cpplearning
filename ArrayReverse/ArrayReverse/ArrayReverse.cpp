#include <iostream>
using namespace std;

int main()
{
    int myNumbers[5] = {1, 2, 3, 4, 5};

    // Printing original array 
    for (int i = 0; i < 5; i++)
    {
        cout << "Original Number " << i << ": " << myNumbers[i] << "\n";
    }
    cout << "\n\n\n";
    
    // Printing reversed array
    for (int j = 4; j >= 0; j--)
    {
        cout << "Reversed Number " << j << ": " << myNumbers[j] << "\n";
    }

    return 0;
}
