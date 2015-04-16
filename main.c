// Checkers Group Project 
// Frank Martino & Will Robb & Justin Chiller & Hien Vo
/*
	This program contains 3 different playable games, Checkers, Connect Four and Tic Tac Toe; 


	Credits:
	Tic Tac Toe was -- Will Robb
	Connect Four was -- Justin Chiller 
	The UI and menu was -- Hein Vo
	The Checkers game, and general code composition -- Frank Martino

	The tic Tac Toe game is played versus the computer, and as far as we can tell is unbeatable; 
	The Connect Four Game is solely two player;
	The Checkers game both has Single player(versus the computer) and two player;  

	All three game boards are displayed via Ascii charecters, and are played using a coordinate syste to refer to pieces on the board;

	The C code was compiled and run in visual studio 2013, and as such may not compile/run in ecclipse/codeblocks and has not been tested to run in those enviroments;

	Finally the system(cls) code used to clear the screen in between turns is only functional in Windows, not unix or on a mac;

	TO DO LIST:
		--Checkers AI
		--Checkers King Me function 
		--MORE COMMENTS
		--Code Sterilization


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BOARD_ROWS 6
#define BOARD_COLS 7

//This is the global array storing the connect four board as it is initialy instanciated; 
int connectBoard[BOARD_ROWS][BOARD_COLS] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
};

//This global array is used for storing the checkers board and is set up as it is initially instanciated 
//1's represent x's and 2's represent o's, 0's are empty spaces;
int board[8][8] = {
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 0, 2, 0, 2, 0, 2, 0 },
	{ 0, 2, 0, 2, 0, 2, 0, 2 },
	{ 2, 0, 2, 0, 2, 0, 2, 0 }
};

//The done variable is used for exiting the connect four game 
int done = 0;
//quit is used in navigation of the checkers game
int quit = 0;
//turn is used by bot hconnect four and checkers to monitor whose turn it is and id the eventual winner 
int turn = 1;
//jumpable is used to signify if there is a possible jump
int jumpable = 0;
//The board T is used for tic tac toe
//and the computer / user charecters are also used for tic tac toe 
char boardT[3][3];
char computer, user;


int checkCheckersWin();
void printBoardF();
void userMove();
int move();
int checkChainJump(int y, int x);
void clear_screen();
int jump();
void checkers();
void checkersMenu();
void menu();
void printBoardC();
int takeTurn();
int checkWin();
int checkSur(int, int, int);
int horizontalCheck();
int verticalCheck();
int diagonalCheck();
int conFour();
void init_boardT(void);
void draw_boardT(void);
int user_first(void);
void play_game(void);
int play_again(void);
void computer_move(void);
void player_move(void);
int find_win(char);
int middle_open(void);
int find_corner(void);
int find_side(void);
int symbol_won(char);
int square_valid(int);
int ticTacToe(void);


//The main function begins the program by calling the menu function 
main() {
	menu();
}

// The menu alows the users to select which game they wish to play 
void menu() {
	int gameChoice= 0;

	do{
		printf("Welcome! \n");
		printf("Please select which game you want to play: \n");
		printf(" 1. Checkers \n");
		printf(" 2. Connect Four\n");
		printf(" 3. Tic Tac Toe\n");
		printf(" Type 0 to quit\n");


		scanf_s("%d", &gameChoice);

		switch (gameChoice)
		{
		case 1:
			quit = 0;
			checkersMenu();
			//printf("Option 1\n");
			break;

		case 2:
			//printf("Option 2\n");
			conFour();
			break;

		case 3:
			//exit(0);
			ticTacToe();
			break;

		case 0:
			exit(0);
			break;
		default:

			printf("Please enter valid option\n");
			printf("or choose again another option (1. Player vs Player 2. Player vs AI 3. Exit)\n");
			break;
		}
		printf("Press 0 to EXIT");
	} while (gameChoice != 0 && quit != 1);

	return;
	
}

//The checkers menu allows users to decide if they want to play 1 or 2 player checkers 
void checkersMenu()
{
	int i;

	do{
		printf("Welcome to Checker Game\n");
		printf("Select your option\n");
		printf("1. Player vs Player\n");
		printf("2. Player vs AI\n");
		printf("3. Exit\n");


		scanf_s("%d", &i);

		switch (i)
		{
		case 1:
			quit = 0;
			checkers();
			//printf("Option 1\n");
			break;

		case 2:
			//printf("Option 2\n");
			break;

		case 3:
			//exit(0);
			break;

		//case 4:
			//printf("Option 4\n");
			//break;
		default:

			printf("Please enter valid option\n");
			printf("or choose again another option (1. Player vs Player 2. Player vs AI 3. Exit)\n");
			break;
		}
	
	} while (quit != 1 && i != 3);

	return;

}

// This is the equivelent of the main function for the checkers game
// It monitors the turns and contains the game loop used to play 
void checkers() {
	//printf("Hello world");
	//int turn = 1;
	

	while (quit != 1 && quit != 2) {
		printBoardC();
		if (turn == 1) {
			userMove();
			if (checkCheckersWin() == 1) {
				printf("Player 1 wins!");
				break;
			}
			turn = 2;
		}
		else {
			userMove();
			if (checkCheckersWin() == 1) {
				printf("Player 2 wins!");
				break;
			}
			turn = 1;
		}
		clear_screen();
	}
	


	
	getchar();
}



// The print Board C function is used to print the checker board out to the console 
void printBoardC() {

	printf("\n      0   1   2   3   4   5   6   7 \n");
	printf("   ---------------------------------\n");
	for (int y = 0; y < 8; y++) {
		
		printf("%d",y);
		printf("  ");
			for (int x = 0; x < 8; x++) {
				
				if (board[y][x] == 0) {
					printf(" |  ");
				}
				if (board[y][x] == 1) {
					printf(" | X");
				}
				if (board[y][x] == 2) {
					printf(" | O");
				}


				//printf("  |  " + board[x][y]);
			}
			printf(" | \n");
		printf("   ---------------------------------\n");
	}
	return;
}


// This is the clear screen function it is only usable on windows machines;
// It clears the console in between reprints of the board
void clear_screen()
{
	std:system("cls");
}

// User move function is called from the checkers function it asks the user to select their move and if valid executes that move
void userMove() {
	int choice;
	int x = 0;

	do {

		printf("please make your move(type 5 for help): ");

		scanf_s("%d\\n", &choice);

		//printf("%d", choice);

		switch (choice){
		case 0:
			quit = 1;
			break;
		case 1:
			if (move() != 0)
				return;
			else
				printf("INVALID MOVE: please make a different move \n ");
			printBoardC();
			userMove();
			return;
			break;
		case 2:
			if (jump() != 0) {
				if (jumpable == 2) {
					printBoardC();
					printf("Coninue chain jump? (1 for yes, 0 for no) ");
					scanf_s("%d\\n", &x);

					while (x == 1) {
						printBoardC();
						jump();
						if (jumpable == 2) {
							printf("Coninue chain jump? (1 for yes, 0 for no) ");
							scanf_s("%d\\n", &x);
						}
						else {
							x = 0;
						}
					}
				}
				return;

			}
			else
				printf("INVALID JUMP: please make a different move \n");
			printBoardC();
			userMove();
			return;
			break;
		case 3:
			break;
		case 4:
			quit = 2;
			return;
		case 5:
			printf("valid commands: \n 1. move \n 2. jump \n 3. king-me \n 4. end game, goto main menu \n 5. help \n Press 0 to quit the program \n");
			userMove();
			return;
		default:

			printf("Please enter valid option\n");
			printf("or choose again another option (1. Player vs Player 2. Player vs AI 3. Exit)\n");
			break;

		}
	} while (quit != 0 || quit != 2);
	return;
}

//This function scans the board to check if the game is over by looking to see if either side is without pieces 
int checkCheckersWin() {
	int x = 0, o = 0;
	for (int i = 0; i < 8; i++) {
		for (int k = 0; k < 8; k++) {
			if (board[i][k] == 1) {
				x++;
			}
			else if (board[i][k] == 2) {
				o++;
			} 
		}
	}

	if (x == 0 || o == 0)
		return 1;

	return 0;
}

//this function  moves the checker piece when the player wishes to do so 
int move() {

	int x, y, ty, tx;
	/*
	printf("please enter the X location of the checker you want to move: ");
	scanf_s("%d\\n", &x);

	printf("please enter the Y location of the checker you want to move: ");
	scanf_s("%d\\n", &y);

	printf("please enter the target X location: ");
	scanf_s("%d\\n", &tx);

	printf("please enter the target Y location: ");
	scanf_s("%d\\n", &ty);
	*/


	printf("Please enter the (x,y) of the checker you want to use: \n x = ");
	scanf_s("%d", &x);
	printf(" y = ");
	scanf_s("%d", &y);


	printf("Please enter the (x,y) the target location: \n Target x = ");
	scanf_s("%d", &tx);
	printf(" Target y = ");
	scanf_s("%d", &ty);


	if (board[ty - 1][tx - 1] == board[y][x] || board[ty - 1][tx + 1] == board[y][x] || board[ty + 1][tx - 1] == board[y][x] || board[ty + 1][tx + 1] == board[y][x]) {
		if (turn == 1) {
			if (board[y][x] == 1 && board[ty][tx] == 0) {

				board[y][x] = 0;
				board[ty][tx] = 1;

				return 1;
			}
			else
				return 0;
		}
		if (turn == 2) {
			if (board[y][x] == 2 && board[ty][tx] == 0) {

				board[y][x] = 0;
				board[ty][tx] = 2;

				return 1;
			}
			else
				return 0;
		}
	}
	return 0;
}

int jump() {
	int x, y, tx, ty;
	int dx, dy;
	/*
	printf("please enter the X location of the checker you want to jump with: ");
	scanf_s("%d\\n", &x);

	printf("please enter the Y location of the checker you want to jump with: ");
	scanf_s("%d\\n", &y);

	printf("please enter the X location of your jump target: ");
	scanf_s("%d\\n", &tx);

	printf("please enter the Y location of your jump target: ");
	scanf_s("%d\\n", &ty);*/

	printf("Please enter the (x,y) of the checker you want to use: \n x = ");
	scanf_s("%d", &x);
	printf(" y = ");
	scanf_s("%d", &y);


	printf("Please enter the (x,y) of the checker you want to jump: \n Target x = ");
	scanf_s("%d", &tx);
	printf(" Target y = ");
	scanf_s("%d", &ty);


	if (ty >= 7 || ty <= 0 || tx > 7 || tx < 0) //make sure the jump is possible/valid
		return 0;

	if (turn == 1) {
		if (board[ty][tx] == 2 && board[y][x] == 1){
			int dx = tx - x;

			if (dx == 1) {
				dx = tx + 1;
			}
			else {
				dx = tx - 1;
			}

			
			dy = ty + 1;
			

			if (board[dy][dx] == 0) {
				board[dy][dx] = 1;
				board[ty][tx] = 0;
				board[y][x] = 0;

				checkChainJump(dy,dx);

				return 1;
			}
			else {
				return 0; 
			}
		}
		else {
			return 0;
		}
	}
		
	if (turn == 2) {
		if (board[ty][tx] == 1 && board[y][x] == 2){
			int dx = tx - x;

			if (dx == 1) {
				dx = tx + 1;
			}
			else {
				dx = tx - 1;
			}


			dy = ty - 1;


			if (board[dy][dx] == 0) {
				board[dy][dx] = 2;
				board[ty][tx] = 0;
				board[y][x] = 0;
			
				checkChainJump(dy,dx);

				return 1;
			}
			else {
				return 0;
			}

		}
		else {
			return 0;
		}
	}

	return 0;
}

int checkChainJump(int y, int x) {
	if (board[y][x] == 1) {
		if (board[y + 1][x + 1] == 2 || board[y + 1][x - 1] == 2) {
			if (board[y + 2][x + 2] == 0 || board[y + 2][x - 2] == 0) {
				jumpable = 2;
				return 0;
			}
		}
	}
	else if(board[y][x] == 2) {
		if (board[y - 1][x + 1] == 1 || board[y - 1][x - 1] == 1) {
			if (board[y - 2][x - 2] == 0 || board[y - 2][x + 2] == 0) {
				jumpable = 2;
				return 0;
			}
		}
	}
	jumpable = 20;
	return 0;
}

void printBoardF() {
	int row, col;

	//system("clear");
	puts("\n    ****Connect Four****\n");
	puts("  ------------------------------------------");
	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			printf("  |  ");
			if (connectBoard[row][col] == 0)
				printf(" ");
			else if (connectBoard[row][col] == 1)
				printf("x");
			else if (connectBoard[row][col] == 2)
				printf("o");
		}
		puts("  |");
		puts("  ------------------------------------------");
	}
	puts("     1     2     3     4     5     6     7\n");

}
int takeTurn() {
	int row = BOARD_ROWS, col = 0;
	char piece = 'X';

	if (turn == 2)
		piece = 'O';
	else
		piece = 'X';

	printf("Player %d (%c):\nEnter number coordinate: ", turn,
		piece);

	while (1) {
		if (1 != scanf_s("%d", &col) || col < 0 || col > 7) {
			while (getchar() != '\n')
				;
			puts("Number out of bounds! Try again.");
		}
		else {
			break;
		}
	}
	col--;

	if (col == -1) {
		done = 1;
		return 1;
	}

	for (row = row - 1; row >= 0; row--) {
		if (connectBoard[row][col] == 0) {
			connectBoard[row][col] = turn;
			return 1;
		}
	}
	return 0;

}

int checkWin() {

	if (horizontalCheck() == 1)
		return 1;
	if (verticalCheck() == 1)
		return 1;
	if (diagonalCheck() == 1)
		return 1;

	return 0;



}

int horizontalCheck() {
	int row, col, idx;
	int count = 0;
	int last = 3;
	//const int WIDTH = 1;

	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS; col++) {

			if (connectBoard[row][col] == 0) {
				last = 3;
				count = 0;
			}
			else {
				if (connectBoard[row][col] == last) {
					count++;
					if (count == 4)
						return 1;
				}
				else {
					count = 1;
					last = connectBoard[row][col];
				}
			}
			
		}
	}
	return 0;

}

int verticalCheck() {
	int row, col, idx;
	int count = 0;
	int last = 3;
	//const int WIDTH = 1;

	for (col = 0; col < BOARD_COLS; col++) {
		for (row = 0; row < BOARD_ROWS; row++) {

			if (connectBoard[row][col] == 0) {
				last = 3;
				count = 0;
			}
			else {
				if (connectBoard[row][col] == last) {
					count++;
					if (count == 4)
						return 1;
				}
				else {
					count = 1;
					last = connectBoard[row][col];
				}
			}
		}
	}
	return 0;

}
int diagonalCheck() {
	int row, col;
	int plusp = 0, plusm = 0;

	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			if (connectBoard[row][col] != 0) {
				if (row == BOARD_ROWS) {
					return 0;
				}
				else if (col == 0) {
					plusp = connectBoard[row + 1][col + 1];
				}
				else if (col == BOARD_COLS) {
					plusm = connectBoard[row + 1][col - 1];
				}
				else {
					plusp = connectBoard[row + 1][col + 1];
					plusm = connectBoard[row + 1][col - 1];
				}

				if (connectBoard[row][col] == plusp && connectBoard[row][col] == plusm){
					return checkSur(col + 1, row + 1 , 1);
					return checkSur(col - 1, row + 1, 2);
				}
				else if (connectBoard[row][col] == plusp && connectBoard[row][col] != plusm) {
					return checkSur(col + 1, row + 1, 1);
				}
				else if (connectBoard[row][col] != plusp && connectBoard[row][col] == plusm) {
					return checkSur(col - 1, row + 1, 2);
				}
				else
					return 0;

			}
		}
	}

	return 0;


}

int checkSur(int c, int r, int dirCode) {
	switch (dirCode){
	case 1:
		if (r + 1 >= BOARD_ROWS || c + 1 >= BOARD_COLS)
			return 0;

		if (connectBoard[r + 1][c + 1] == turn && connectBoard[r + 2][c + 2] == turn)
			return 1;
		else
			return 0;

		break;
	case 2:
		if (r + 1 >= BOARD_ROWS || c - 1 <= 0)
			return 0;

		if (connectBoard[r + 1][c - 1] == turn && connectBoard[r + 2][c - 2] == turn)
			return 1;
		else
			return 0;

		break;
	};
}


int conFour() {

	//int turn = 0;

	//char board[BOARD_ROWS * BOARD_COLS];
	//memset(board, ' ', BOARD_ROWS * BOARD_COLS);

	for (int i = 0; i < BOARD_COLS * BOARD_ROWS; i++) {
		printBoardF();
		while (!takeTurn()) {
			printBoardF();
			puts("**Column full!**\n");
		}

		
		
		
		if (checkWin() == 1)
			break;

		if (turn == 1)
			turn = 2;
		else
			turn = 1;
		
	}
	printBoardF();
	
	getchar();

	if (turn == BOARD_ROWS * BOARD_COLS && !done) {
		puts("It's a tie!");
	}
	else {
		printf("Player %d wins!\n", turn);
	}

	getchar();

	return 0;
}
/* Initialize the boardT, ask who goes first, play a game, ask if user wants to play again. */
int ticTacToe(void)
{
	while (1)
	{
		init_boardT();
		if (user_first())
		{
			computer = 'O';
			user = 'X';
		}
		else
		{
			computer = 'X';
			user = 'O';
		}
		play_game();
		if (!play_again())
			break;
	}

	return 0;
}

/* Make sure boardT starts empty. */
void init_boardT(void)
{
	int row, col;

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			boardT[row][col] = ' ';

	return;
}

/* Display the boardT to standard output. */
void draw_boardT(void)
{
	int row;

	printf("\n");
	for (row = 0; row < 3; row++)
	{
		printf(" %c * %c * %c \n", boardT[row][0], boardT[row][1], boardT[row][2]);
		if (row != 2)
			printf("***********\n");
	}
	printf("\n");

	return;
}

/* Ask if user wants to go first */
int user_first(void)
{
	char response;

	printf("Do you want to go first? (y/n) ");
	do
	{
		response = getchar();
	} while ((response != 'y') && (response != 'Y') &&
		(response != 'n') && (response != 'N'));

	if ((response == 'y') || (response == 'Y'))
		return 1;
	else
		return 0;
}

/* Loop through 9 turns or until somebody wins. */
void play_game(void)
{
	int turn;

	for (turn = 1; turn <= 9; turn++)
	{
		/* Check if turn is even or odd to determine which player should move. */
		if (turn % 2 == 1)
		{
			if (computer == 'X')
				computer_move();
			else
				player_move();
		}
		else
		{
			if (computer == 'O')
				computer_move();
			else
				player_move();
		}

		draw_boardT();

		if (symbol_won(computer)) {
			printf("\nI WIN!!!\n\n");
			return;
		}
		else if (symbol_won(user)) {
			printf("\nCongratulations, you win!\n\n");
			return;
		}
	}

	printf("\nThe game is a draw.\n\n");
	return;
}

/* Ask if user wants to play again */
int play_again(void)
{
	char response;

	printf("Do you want to play again? (y/n) ");
	do
	{
		response = getchar();
	} while ((response != 'y') && (response != 'Y') &&
		(response != 'n') && (response != 'N'));

	if ((response == 'y') || (response == 'Y'))
		return 1;
	else
		return 0;
}

/* Choose a move for the computer. */
void computer_move(void)
{
	int square;
	int row, col;

	/* Use first strategy rule that returns valid square */
	square = find_win(computer);
	if (!square)
		square = find_win(user);
	if (!square)
		square = middle_open();
	if (!square)
		square = find_corner();
	if (!square)
		square = find_side();

	printf("\nI am choosing square %d!\n", square);

	row = (square - 1) / 3;
	col = (square - 1) % 3;

	boardT[row][col] = computer;

	return;
}

/*
* Find a win for the given symbol.
* If a winning square exists, return the square;
* Otherwise, return 0;
*/
int find_win(char symbol)
{
	int square, row, col;
	int result = 0;

	/*
	* Loop through the 9 squares.
	* For each, if it is empty, fill it in with the given symbol and check
	* if this has resulted in a win.  If so, keep track of this square in result.
	* Either way, reset the square to empty afterwards. After the loop, if one or
	* more wins have been found, the last will be recorded in result.
	* Otherwise, result will still be 0.
	*/
	for (square = 1; square <= 9; square++)
	{
		row = (square - 1) / 3;
		col = (square - 1) % 3;

		if (boardT[row][col] == ' ')
		{
			boardT[row][col] = symbol;
			if (symbol_won(symbol))
				result = square;
			boardT[row][col] = ' ';
		}
	}

	return result;
}

/* If middle square is empty, return 5; Otherwise return 0. */
int middle_open(void)
{
	if (boardT[1][1] == ' ')
		return 5;
	else
		return 0;
}

/* Return the number of an empty corner, if one exists; Otherwise return 0. */
int find_corner(void)
{
	if (boardT[0][0] == ' ')
		return 1;
	if (boardT[0][2] == ' ')
		return 3;
	if (boardT[2][0] == ' ')
		return 7;
	if (boardT[2][2] == ' ')
		return 9;

	return 0;
}

/* Return the number of an empty side square, if one exists; Otherwise return 0. */
int find_side(void)
{
	if (boardT[0][1] == ' ')
		return 2;
	if (boardT[1][0] == ' ')
		return 4;
	if (boardT[1][2] == ' ')
		return 6;
	if (boardT[2][1] == ' ')
		return 8;

	return 0;
}

/* Check if the given symbol has already one the game. */
int symbol_won(char symbol)
{
	int row, col;

	for (row = 0; row < 3; row++)
	{
		if ((boardT[row][0] == symbol) && (boardT[row][1] == symbol) && (boardT[row][2] == symbol))
			return 1;
	}

	for (col = 0; col < 3; col++)
	{
		if ((boardT[0][col] == symbol) && (boardT[1][col] == symbol) && (boardT[2][col] == symbol))
			return 1;
	}

	if ((boardT[0][0] == symbol) && (boardT[1][1] == symbol) && (boardT[2][2] == symbol))
		return 1;

	if ((boardT[0][2] == symbol) && (boardT[1][1] == symbol) && (boardT[2][0] == symbol))
		return 1;

	return 0;
}

/* Have the user choose a move. */
void player_move(void)
{
	int square;
	int row, col;

	do
	{
		printf("Enter a square (ex. 1 thru 9): ");
		scanf_s("%d", &square);
	} while (!square_valid(square));

	row = (square - 1) / 3;
	col = (square - 1) % 3;

	boardT[row][col] = user;

	return;
}

/* Check if the given square is valid and empty. */
int square_valid(int square)
{
	int row, col;

	row = (square - 1) / 3;
	col = (square - 1) % 3;

	if ((square >= 1) && (square <= 9))
	{
		if (boardT[row][col] == ' ')
			return 1;
	}

	return 0;
}