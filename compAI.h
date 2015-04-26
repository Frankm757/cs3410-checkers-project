//Header file for the compAI.c
//declares functions of the AI system


struct moveNode {
	int m, x, y;

	struct moveNode *nextMove;
};

typedef struct moveNode node;

extern int aiMain();
extern int canMoveLeft();
extern int canMoveRight();
extern int canJumpLeft();
extern int canJumpRight();
extern void initCB();
extern void determineMoves();
extern void initRoot();
extern void evalRecurse(int score);
extern void eval();
extern void execMove();
extern void clearLL();
extern void printLL();