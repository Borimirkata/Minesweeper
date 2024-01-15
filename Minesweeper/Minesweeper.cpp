/**
*
* Solution to course project # 5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Borimir Aleksiev
* @idnumber 8MI0600283 * @compiler VC
*
* Minesweeper Game Task Solution
*
*/

#include<iostream>
using namespace std;

constexpr int MAX_SIZE = 10;
constexpr int MAX_MINES = 30;
constexpr int MAX_LENGTH = 1024;
const char initialValue = '+';
const char bombValue = '*';
const char flagValue = '!';

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
	cout << " |";
	for (int i = 0; i < N; i++) {
		cout << i << " ";
	}
	cout << endl;

	cout << "-|";
	int length = N * 2;
	for (int i = 0; i < length; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << i << "|";
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

int countNeighborMines(const bool minesBoard[][MAX_SIZE], int x, int y, int N) {
	int bombs = 0;
	if (isValidSpace(N, x, y) && isMine(minesBoard, x, y)) {
		bombs++;
	}
	return bombs;
}

int countConsecutiveNeighborMines(const bool minesBoard[][MAX_SIZE], int& x, int& y, int N) {
	return countNeighborMines(minesBoard, x - 1, y, N) +
		countNeighborMines(minesBoard, x + 1, y, N) +
		countNeighborMines(minesBoard, x, y + 1, N) +
		countNeighborMines(minesBoard, x, y - 1, N) +
		countNeighborMines(minesBoard, x - 1, y + 1, N) +
		countNeighborMines(minesBoard, x - 1, y - 1, N) +
		countNeighborMines(minesBoard, x + 1, y + 1, N) +
		countNeighborMines(minesBoard, x + 1, y - 1, N);
}

void replaceMine(bool minesBoard[][MAX_SIZE], int N, int& x, int& y) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (minesBoard[i][j] == false) {
				minesBoard[i][j] = true;
				minesBoard[x][y] = false;
				return;
			}
		}
	}
}

bool compareStrings(const char* inputArr, const char* str2) {
	if (!inputArr || !str2) {
		return false;
	}
	while (*inputArr && *str2) {
		if (*inputArr != *str2) {
			return false;
		}
		inputArr++;
		str2++;
	}
	return (*inputArr == '\0' && *str2 == '\0');
}

bool validateString(const char* input) {
	if (!input) {
		return false;
	}
	return (compareStrings(input, "open") || compareStrings(input, "mark") || compareStrings(input, "unmark"));
}

int counterMovesLeft(const char board[][MAX_SIZE], int N, int mines) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == initialValue || board[i][j] == flagValue) {
				counter++;
			}
		}
	}
	return (counter - mines);
}

void initializeValidGame(char board[][MAX_SIZE], bool minesBoard[][MAX_SIZE], int& N, int& mines, int& flags, int& movesLeft) {
	cout << "Input the size of the board(Between 3 and 10)!" << endl;
	cin >> N;
	while (N < 3 || N > 10) {
		cout << "Invalid input. Try again!" << endl;
		cin >> N;
	}
	initializeBoard(board, N);
	cout << "Input how many mines do you want(Between 1 and " << 3 * N << ")!" << endl;
	cin >> mines;
	while (mines < 1 || mines > 3 * N) {
		cout << "Invalid input. Try again!" << endl;
		cin >> mines;
	}
	flags = mines;
	placeMines(board, minesBoard, N, mines);
	movesLeft = counterMovesLeft(board, N, mines);
}

void handleFirstMove(int& currentMove, int& x, int& y, bool minesBoard[][MAX_SIZE], int N) {
	if (currentMove == 1) {
		if (isMine(minesBoard, x, y)) {
			replaceMine(minesBoard, N, x, y);
		}
		currentMove++;
	}
}

int main() {
	srand(time(0));
	char board[MAX_SIZE][MAX_SIZE];
	int N = 0, mines = 0;
	int movesLeft = 0;
	char inputArr[MAX_LENGTH];
	bool minesBoard[MAX_SIZE][MAX_SIZE];
	int currentMove = 1;
	int flags = 0;
	initializeValidGame(board, minesBoard, N, mines, flags, movesLeft);
}