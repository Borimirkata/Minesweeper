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

void handleFirstMove(int& currentMove, int& x, int& y, bool minesBoard[][MAX_SIZE], int N) {
	if (currentMove == 1) {
		if (isMine(minesBoard, x, y)) {
			replaceMine(minesBoard, N, x, y);
		}
		currentMove++;
	}
}

int main(){
	srand(time(0));
	char board[MAX_SIZE][MAX_SIZE];
	int N = 0, mines = 0;
	int movesLeft = 0;
	initializeValidGame(N, mines);
	initializeBoard(board, N);
	printBoard(board, N);
	bool minesBoard[MAX_SIZE][MAX_SIZE];
	int currentMove = 1;
}