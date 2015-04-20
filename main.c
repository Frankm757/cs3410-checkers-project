// Checkers Group Project 
// Frank Martino & Will Robb & Justin Chiller & Hien Vo
/*
	Rather than just being a simple checkers game this, program contains 3 seperate games all playable, accesesd through one unifying menu;
	The three games that are playable in this program, are as follows: Checkers, Connect Four, and Tic Tac Toe;


	Credits:
	Tic Tac Toe was -- Will Robb
	Connect Four was -- Justin Chiller 
	The UI and menu was -- Hein Vo
	The Checkers game, and general code composition -- Frank Martino

	The tic Tac Toe game is played versus the computer, and as far as we can tell is unbeatable; 
	The Connect Four Game is solely two player;
	The Checkers game both has Single player(versus the computer) and two player;  

	All three game boards are displayed via Ascii charecters, and are played using a coordinate syste to refer to pieces on the board;

	The program only accepts integers as input

	The C code was compiled and run in visual studio 2013, and as such may not compile/run in ecclipse/codeblocks and has not been tested to run in those enviroments;

	Finally the system(cls) code used to clear the screen in between turns is only functional in Windows, not unix or on a mac;

	TO DO LIST:
		--Checkers AI
		--Checkers King Me function 
		


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"


void menu();
void checkers();
void checkersMenu();
void userMove(); 

int quitt = 0;
int turnn = 1;
int ai = 0;

//The main function begins the program by calling the menu function 
main() {
	menu();
}



// The menu alows the users to select which game they wish to play 
void menu() {
	int gameChoice= 0;

	do{
		clear_screen();
		printf("Welcome! \n");
		printf("Please select which game you want to play: \n");
		printf(" 1. Checkers \n");
		printf(" 2. Connect Four\n");
		printf(" 3. Tic Tac Toe\n");
		printf(" Type 0 to quit\n");


			//scanf_s("%d", &gameChoice);

		gameChoice = getUserIn();

		switch (gameChoice)
		{
		case 1:
			quitt = 0;
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
	} while (gameChoice != 0 && quitt != 1);

	return;
	
}

//The checkers menu allows users to decide if they want to play 1 or 2 player checkers 
void checkersMenu()
{
	int i;

	do{
		clear_screen();
		printf("Welcome to Checker Game\n");
		printf("Select your option\n");
		printf("1. Player vs Player\n");
		printf("2. Player vs AI\n");
		printf("3. Exit\n");


		scanf_s("%d", &i);

		switch (i)
		{
		case 1:
			quitt = 0;
			checkers();
			//printf("Option 1\n");
			break;

		case 2:
			ai = 1;
			checkers();
		
			//printf("Option 2\n");
			break;

		case 3:
			quitt = 3;
			break;

			//case 4:
			//printf("Option 4\n");
			//break;
		default:

			printf("Please enter valid option\n");
			printf("or choose again another option (1. Player vs Player 2. Player vs AI 3. Exit)\n");
			break;
		}

	} while (quitt != 3 && i != 3);

	return;

}


// This is the equivelent of the main function for the checkers game
// It monitors the turns and contains the game loop used to play 
void checkers() {

	while (quitt != 1 && quitt != 2) {
		printBoard(1);
		if (turnn == 1) {
		
			userMove();
			kingMe(1);
			if (checkCheckersWin() == 1) {
				printf("Player 1 wins!");
				break;
			}
			turnn = 2;
		}
		else if(ai != 1) {
			userMove();
			kingMe(2);
			if (checkCheckersWin() == 1) {
				printf("Player 2 wins!");
				break;
			}
			turnn = 1;
		}
		else {
			//checkAI();
			int t = simpleAI();
			kingMe(2);
			if (checkCheckersWin() == 1) {
				printf("Computer wins!");
				break;
			}
			turnn = 1;
		}
	}


	return;
}

// User move function is called from the checkers function it asks the user to select their move and if valid executes that move
void userMove() {
	int choice;
	int x = 0;
	int tx, ty, y;
	int jumpable = 0;
	

	do {
		printf("Player %d:", turnn);
		printf("please make your move(type 5 for help): ");

		scanf_s("%d\\n", &choice);

		

		switch (choice){
		case 0:
			quitt = 1;
			return;
		case 1:

			printf("Please enter the (x,y) of the checker you want to use: \n x = ");
			scanf_s("%d", &x);
			printf(" y = ");
			scanf_s("%d", &y);


			printf("Please enter the (x,y) the target location: \n Target x = ");
			scanf_s("%d", &tx);
			printf(" Target y = ");
			scanf_s("%d", &ty);

			if (move(turnn, x, y, ty, tx) != 0)
				return;
			else
				printf("INVALID MOVE: please make a different move \n ");
			printBoard(1);
			userMove();
			return;
			break;
		case 2:

			printf("Please enter the (x,y) of the checker you want to use: \n x = ");
			scanf_s("%d", &x);
			printf(" y = ");
			scanf_s("%d", &y);


			printf("Please enter the (x,y) of the checker you want to jump: \n Target x = ");
			scanf_s("%d", &tx);
			printf(" Target y = ");
			scanf_s("%d", &ty);

			jumpable = jump(turnn,  tx,  ty, x, y);

			if (jumpable != 0) {
				if (jumpable == 2) {
					printBoard(1);
					printf("Coninue chain jump? (1 for yes, 0 for no) ");
					scanf_s("%d\\n", &x);

					while (x == 1) {
						printBoard(1);

						printf("Please enter the (x,y) of the checker you want to use: \n x = ");
						scanf_s("%d", &x);
						printf(" y = ");
						scanf_s("%d", &y);


						printf("Please enter the (x,y) of the checker you want to jump: \n Target x = ");
						scanf_s("%d", &tx);
						printf(" Target y = ");
						scanf_s("%d", &ty);

						jumpable = jump(turnn, tx, ty, x, y);
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
			//printBoard(1);
			userMove();
			return;
			break;
		
		case 4:
			quitt = 2;
			return;
		case 5:
			printf("valid commands: \n 1. move \n 2. jump \n 4. end game, goto main menu \n 5. help \n Press 0 to quit the program \n");
			userMove();
			return;
		default:

			printf("Please enter valid option\n");
			printf("or choose again another option (1. Player vs Player 2. Player vs AI 3. Exit)\n");
			break;

		}
	} while (quitt != 0 || quitt != 2);
	return;
}
