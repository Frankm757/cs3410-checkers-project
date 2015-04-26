/*
	The Comp ai class calculates the best move for the computer 
	by using a value matrix of the board combined with points assinged for the resulting move being a jump or eventually resulting the the computer losing a piece 


*/



#include "games.h"
#include "compAI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compBoard[8][8];
int tempCompBoard[8][8];

node *root;
node *curNode;

int best[3] = { 0, 0, 0 };

int boardValue[8][8] = {
	{ 0, 4, 0, 4, 0, 4, 0, 4 },
	{ 4, 0, 3, 0, 3, 0, 3, 0 },
	{ 0, 3, 0, 2, 0, 2, 0, 4 },
	{ 4, 0, 2, 0, 1, 0, 3, 0 },
	{ 0, 3, 0, 1, 0, 2, 0, 4 },
	{ 4, 0, 2, 0, 2, 0, 3, 0 },
	{ 0, 3, 0, 3, 0, 3, 0, 4 },
	{ 4, 0, 4, 0, 4, 0, 4, 0 }
};

int getPlaceValue(int y, int x) {	

	return boardValue[y][x];

}


int aiMain() {
	initCB();
	
	determineMoves();

	//printLL();

	eval();

	execMove();

	clearLL();
	
	return 1;
}

void execMove() {
	switch (best[0]) {
	case 1:
		if (move(2, best[2], best[1], best[1] - 1, best[2] - 1) == 0){
			printf("x %d:", best[2]);
			printf("y %d:", best[1]);
			printf("move 1");
		}
			break;
	case 2:
		move(2, best[2], best[1], best[1] - 1, best[2] + 1);


			break;
			
	case 3:
		if (jump(2, best[2] - 1, best[1] - 1, best[2], best[1]) == 2){
			best[0] = 3;
			best[1] = best[1] - 2;
			best[2] = best[2] - 2;
			execMove;
		}
			break;
	case 4:
		if (jump(2, best[2] + 1, best[1] - 1, best[2], best[1]) == 2){
			best[0] = 4;
			best[1] = best[1] - 2;
			best[2] = best[2] + 2;
			execMove;
		} 
			break;
	default:
		printf("BEST MOVE SWITCH NOT PROPERLY FUNCTIONING **********");
		if (getUserIn() == 0)
			break;
	}
}

void printLL() {
	curNode = root;

	while (curNode->nextMove != NULL) {
		printf("x %d:", curNode->x);
		printf("y %d:", curNode->y);
		printf("Move %d:", curNode->m);
		curNode = curNode->nextMove;
	}

}


void clearLL() {
	curNode = root;
	if (curNode->nextMove != NULL) {
		root = curNode->nextMove;
		free(curNode);
		clearLL();
	}
	else { 
		free(curNode);
		return; }
}

void initCB() {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			compBoard[y][x] = getPieceAt(y, x);
			tempCompBoard[y][x] = compBoard[y][x]; 
		}
	}
}

void eval() {

	curNode = root->nextMove;

	evalRecurse(-33);
}


void evalRecurse(int score) {
	int tempScore = 0;



	if (curNode->nextMove == NULL)
		return;
	else {
		switch (curNode->m) {
			case 1: 
				tempScore = getPlaceValue(curNode->y - 1, curNode->x - 1);

				if ((curNode->y - 1) == 0 || (curNode->x - 1) == 0) {
					tempScore++;
				}
				else if (tempCompBoard[curNode->y - 2][curNode->x - 2] == 1 || tempCompBoard[curNode->y - 2][curNode->x + 2] == 1) // check if it will be jumped
					tempScore--;
				
				if (tempScore > score) {
					best[0] = curNode->m;
					best[1] = curNode->y;
					best[2] = curNode->x;

					curNode = curNode->nextMove;
					evalRecurse(tempScore);
				}
			
				break;
			case 2:
				tempScore = getPlaceValue(curNode->y - 1, curNode->x + 1);

				if ((curNode->y - 1) == 0 || (curNode->x + 1) == 7) {
					tempScore++;
				}
				else if (tempCompBoard[curNode->y - 2][curNode->x - 2] == 1 || tempCompBoard[curNode->y - 2][curNode->x + 2] == 1) // check if it will be jumped
					tempScore--;

				if (tempScore > score) {
					best[0] = curNode->m;
					best[1] = curNode->y;
					best[2] = curNode->x;
					curNode = curNode->nextMove;
					evalRecurse(tempScore);
				}

				break;
			case 3:
				tempScore = getPlaceValue(curNode->y - 2, curNode->x - 2) + 4;

				if ((curNode->y - 2) == 0 || (curNode->x - 2) == 0) {
					tempScore++;
				}
				else if (tempCompBoard[curNode->y - 3][curNode->x - 3] == 1 || tempCompBoard[curNode->y - 3][curNode->x + 3] == 1) // check if it will be jumped
					tempScore--;

				if (tempScore > score) {
					best[0] = curNode->m;
					best[1] = curNode->y;
					best[2] = curNode->x;
					curNode = curNode->nextMove;
					evalRecurse(tempScore);
				}
				break;
			case 4:
				tempScore = getPlaceValue(curNode->y - 2, curNode->x - 2) + 4;

				if ((curNode->y -2) == 0 || (curNode->x +2) == 7) {
					tempScore++;
				}
				else if (tempCompBoard[curNode->y - 3][curNode->x - 3] == 1 || tempCompBoard[curNode->y - 3][curNode->x + 3] == 1) // check if it will be jumped
					tempScore--;

				if (tempScore > score) {
					best[0] = curNode->m;
					best[1] = curNode->y;
					best[2] = curNode->x;
					curNode = curNode->nextMove;
					evalRecurse(tempScore);
				}
				break;
		}
	}

	
}


void determineMoves() {

	

	curNode = (node *)malloc(sizeof(node));

	root = curNode; 

	

	
	root->m = 0;
	root->x = 101;
	root->y = 101;
	root->nextMove = (node *)malloc(sizeof(node));;

	curNode = root->nextMove;
	
	

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (tempCompBoard[y][x] == 2) {
				if (canMoveLeft(y,x) == 1) {
					
					curNode->m = 1;
					curNode->x = x;
					curNode->y = y;
					
					curNode->nextMove = (node *)malloc(sizeof(node));

					

					curNode = curNode->nextMove;
					

				}
				if (canMoveRight(y, x) == 1) {
					curNode->m = 2;
					curNode->x = x;
					curNode->y = y;

					curNode->nextMove = (node *)malloc(sizeof(node));



					curNode = curNode->nextMove;
				}
				if (canJumpLeft(y, x) == 1) {
					curNode->m = 3;
					curNode->x = x;
					curNode->y = y;

					curNode->nextMove = (node *)malloc(sizeof(node));



					curNode = curNode->nextMove;
				}
				if (canJumpRight(y, x) == 1) {
					curNode->m = 4;
					curNode->x = x;
					curNode->y = y;

					curNode->nextMove = (node *)malloc(sizeof(node));



					curNode = curNode->nextMove;
				}
			}
		}
	}

	curNode->nextMove = NULL;

}

int canMoveLeft(int y, int x) {
	if ((x - 1) != -1 && (y-1) != -1) {
		if (tempCompBoard[y - 1][x - 1] == 0){
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int canMoveRight(int y, int x) {
	if ((x + 1) != 8 && (y - 1) != -1) {
		if (tempCompBoard[y - 1][x + 1] == 0){
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int canJumpLeft(int y, int x) {
	if ((x - 1) != 8 && (y - 1) != -1 && (x - 2) != -1 && (y - 2) != -1) {
		if (tempCompBoard[y - 2][x - 2] == 0 && tempCompBoard[y - 1][x - 1] == 1){
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int canJumpRight(int y, int x) {
	if ((x + 1) != 8 && (y - 1) != -1 && (x + 2) != -1 && (y - 2) != -1) {
		if (tempCompBoard[y - 2][x + 2] == 0 && tempCompBoard[y - 1][x + 1] == 1){
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}