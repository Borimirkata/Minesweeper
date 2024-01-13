#include<iostream>
using namespace std;

constexpr int MAX_SIZE = 10;
const char initialValue = '+';
const char bombValue = '*';

bool isValidSpace(int N, int x, int y) {
	return (x >= 0 && x < N && y >= 0 && y < N);
}

bool isMine(const bool minesBoard[][MAX_SIZE], int x, int y) {
	if (minesBoard[x][y] == true) {
		return true;
	}
	return false;
}

void initializeBoard(char board[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = initialValue;
		}
	}
}

void printBoard(const char board[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void initializeMinesBoard(bool minesBoard[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			minesBoard[i][j] = false;
		}
	}
}

void placeMines(const char board[][MAX_SIZE], bool minesBoard[][MAX_SIZE], int N, int mines) {
	initializeMinesBoard(minesBoard, N);
	int placedMines = 0;
	while (placedMines < mines) {
		int random = rand() % (N * N);
		int x = random / N;
		int y = random % N;
		if (minesBoard[x][y] == false) {
			minesBoard[x][y] = true;
			placedMines++;
		}
	}
	return;
}

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
	initializeBoard(board, N);
	printBoard(board, N);
	bool minesBoard[MAX_SIZE][MAX_SIZE];
}