#include<iostream>
using namespace std;

constexpr int MAX_SIZE = 10;

void initializeValidGame(int& N,int& mines) {
	cout << "Input the size of the board!" << endl;
	cin >> N;
	while (N < 3 || N > 10) {
		cout << "Invalid input. Try again!" << endl;
		cin >> N;
	}
	cout << "Input how many mines do you want:" << endl;
	cin >> mines;
	while (mines < 1 || mines > 3 * N) {
		cout << "Invalid input. Try again!" << endl;
		cin >> mines;
	}
}

int main()
{
	char board[MAX_SIZE][MAX_SIZE];
	int N = 0, mines = 0;
	initializeValidGame(N, mines);
}