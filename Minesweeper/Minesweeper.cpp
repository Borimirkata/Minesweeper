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

bool playMinesweeper(char board[][MAX_SIZE], bool minesBoard[][MAX_SIZE], int N, int x, int y,
	int& movesLeft, int& flags, const char inputArr[MAX_LENGTH], int& valid);

bool isValidSpace(int N, int x, int y) {
	return (x >= 0 && x < N && y >= 0 && y < N);
}

void initializeBoard(char board[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = initialValue;
		}
	}
}

void initializeMinesBoard(bool minesBoard[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			minesBoard[i][j] = false;
		}
	}
}

bool isMine(const bool minesBoard[][MAX_SIZE], int x, int y) {
	if (minesBoard[x][y] == true) {
		return true;
	}
	return false;
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
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Invalid input. Try again!" << endl;
		cin >> N;
	}
	initializeBoard(board, N);
	cout << "Input how many mines do you want(Between 1 and " << 3 * N << ")!" << endl;
	cin >> mines;
	while (mines < 1 || mines > 3 * N) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Invalid input. Try again!" << endl;
		cin >> mines;
	}
	flags = mines;
	placeMines(board, minesBoard, N, mines);
	movesLeft = counterMovesLeft(board, N, mines);
	cout << "Possible commands are:(open),(mark),(unmark) and the coordinates!" << endl;
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
	return (compareStrings(input, "open") ||
		compareStrings(input, "mark") ||
		compareStrings(input, "unmark"));
}

void untilItsValid(int N, int& x, int& y, char* inputArr, int flags) {
	if (!inputArr) {
		return;
	}
	while (!isValidSpace(N, x, y) || !validateString(inputArr) || cin.fail()) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Invalid action!Try again!" << endl;
		cin >> inputArr >> x >> y;
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

void handleFirstMove(int& currentMove, int& x, int& y, bool minesBoard[][MAX_SIZE], int N, const char inputArr[MAX_LENGTH]) {
	if (validateString(inputArr) && compareStrings(inputArr, "open")) {
		if (isMine(minesBoard, x, y)) {
			replaceMine(minesBoard, N, x, y);
		}
		currentMove++;
	}
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

void stepOnMine(char board[][MAX_SIZE], const bool minesBoard[][MAX_SIZE], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (minesBoard[i][j]) {
				board[i][j] = bombValue;
			}
		}
	}
}

void checkMines(char board[][MAX_SIZE], bool minesBoard[][MAX_SIZE], int N, int x, int y,
	int movesLeft, int flags, const char inputArr[MAX_LENGTH], int& valid) {

	if (isValidSpace(N, x, y)) {
		if (isMine(minesBoard, x, y) == false) {
			playMinesweeper(board, minesBoard, N, x, y, movesLeft, flags, inputArr, valid);
		}
	}
}

void putFlag(char board[][MAX_SIZE], int x, int y, int& flags) {
	if (flags == 0) {
		cout << "You cannot put any more flags" << endl;
		return;
	}
	if (board[x][y] != initialValue) {
		cout << "You cannot place your flag there!" << endl;
		return;
	}
	else if (board[x][y] == initialValue) {
		board[x][y] = flagValue;
		flags--;
	}
}

void removeFlag(char board[][MAX_SIZE], int x, int y, int& flags) {
	if (board[x][y] != flagValue) {
		cout << "These coordinates were not marked!" << endl;
		return;
	}
	else if (board[x][y] == flagValue) {
		board[x][y] = initialValue;
		flags++;
	}
}

void handleWinningCondition(char board[][MAX_SIZE], const bool minesBoard[][MAX_SIZE], int N) {
	stepOnMine(board, minesBoard, N);
	printBoard(board, N);
	cout << "Congratulations, You win!" << endl;
}

bool playMinesweeper(char board[][MAX_SIZE], bool minesBoard[][MAX_SIZE], int N, int x, int y,
	int& movesLeft, int& flags, const char inputArr[MAX_LENGTH], int& valid) {

	if (compareStrings(inputArr, "open")) {
		if (board[x][y] != initialValue) {
			if (valid == 0) {
				cout << "Cannot open there!" << endl;
				valid++;
			}
			return false;
		}
		if (minesBoard[x][y] == true) {
			stepOnMine(board, minesBoard, N);
			printBoard(board, N);
			cout << "You lost the Game!" << endl;
			return true;
		}
		int count = countConsecutiveNeighborMines(minesBoard, x, y, N);
		board[x][y] = count + '0';
		if (count == 0) {
			valid++;
			checkMines(board, minesBoard, N, x - 1, y, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x + 1, y, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x, y + 1, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x, y - 1, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x - 1, y + 1, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x - 1, y - 1, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x + 1, y + 1, movesLeft, flags, inputArr, valid);
			checkMines(board, minesBoard, N, x + 1, y - 1, movesLeft, flags, inputArr, valid);
		}
		return false;
	}
	else if (compareStrings(inputArr, "mark")) {
		putFlag(board, x, y, flags);
	}
	else if (compareStrings(inputArr, "unmark")) {
		removeFlag(board, x, y, flags);
	}
	else {
		cout << "Invalid command" << endl;
	}
	return false;
}

int main() {
	srand(time(0));
	bool gameOver = false;
	char board[MAX_SIZE][MAX_SIZE];
	int N = 0, mines = 0;
	char inputArr[MAX_LENGTH];
	int movesLeft = 0;
	int flags = 0;
	bool minesBoard[MAX_SIZE][MAX_SIZE];

	initializeValidGame(board, minesBoard, N, mines, flags, movesLeft);
	int validOpen = 0;
	int currentMove = 1;
	while (gameOver == false) {
		printBoard(board, N);
		int x, y;
		cout << "Flags: " << flags << endl;
		cout << "Enter command and coordinates: ";
		cin >> inputArr >> x >> y;
		untilItsValid(N, x, y, inputArr, flags);

		if (currentMove == 1) {
			handleFirstMove(currentMove, x, y, minesBoard, N, inputArr);
		}

		validOpen = 0;
		gameOver = playMinesweeper(board, minesBoard, N, x, y, movesLeft, flags, inputArr, validOpen);
		movesLeft = counterMovesLeft(board, N, mines);
		if (gameOver == false && movesLeft == 0) {
			handleWinningCondition(board, minesBoard, N);
			return 0;
		}
	}
}