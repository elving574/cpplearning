#include <cstdlib> 
#include <iostream> 
#include <ctime>
using namespace std;
 
char getComputerMove()
{
	int move;
	srand(time(NULL));
	move = rand() % 3;

	if (move == 0) {
		return 'p';
	}
	else if (move == 1) {
		return 's';
	}
	return 'r';
} 
int getResults(char playerMove, char computerMove)
{
	if (playerMove == computerMove) {
		return 0;
	}
	if (playerMove == 's' && computerMove == 'p') {
		return 1;
	}
	if (playerMove == 's' && computerMove == 'r') {
		return -1;
	}
	if (playerMove == 'p' && computerMove == 'r') {
		return 1;
	}
	if (playerMove == 'p' && computerMove == 's') {
		return -1;
	}
	if (playerMove == 'r' && computerMove == 'p') {
		return -1;
	}
	if (playerMove == 'r' && computerMove == 's') {
		return 1;
	}
	return 0;
}

int main()
{
	char playerMove;

	cout << "\n\n\n\t\t\tWelcome to Rock Paper Scissors Game\n";

	cout << "\n\t\tEnter r for ROCK, p for PAPER, and s for SCISSORS\n\t\t\t\t\t";

	while (1) {
		cin >> playerMove;
		if (playerMove == 'p' || playerMove == 'r' || playerMove == 's') {
			break;
		}
		else {
			cout << "\t\t\tInvalid Player Move, please Try Again." << endl;
		}
	}

	char computerMove = getComputerMove();

	int result = getResults(playerMove, computerMove);

	if (result == 0) {
		cout << "\n\t\t\tGame Draw!\n";
	}
	else if (result == 1) {
		cout << "\n\t\t\tCongratulations, the player won the game!\n";
	}
	else {
		cout << "\n\t\t\tOh no, the computer won the game!\n
	}

	cout << "\t\t\tYour Move: " << playerMove << endl;
	cout << "\t\t\tComputer's Move: " << computerMove << endl;

	return 0;
}
