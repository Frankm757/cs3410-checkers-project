

extern int checkCheckersWin(); //yes


int move(int t, int x, int y, int ty, int tx); // yes
extern int checkChainJump(int y, int x); //yes
extern void clear_screen(); // yes
int jump(int t, int tx, int ty, int x, int y);

extern int simpleAI();
extern void initBoard();
extern void findNext();

extern void clearBoard();
extern void emptyBoard();


//extern void checkAI();
//extern int pieceValue(int p);
//extern void initTempBoard();

extern void kingMe(int t);

extern void printBoard(int c); //yes
extern int takeTurn(); //yes
extern int checkWin(); //yes
extern int checkSur(int, int, int); //yes
extern int horizontalCheck(); // yes 
extern int verticalCheck(); //yes 
extern int diagonalCheck(); //yes 


extern  conFour();
extern int ticTacToe();


extern void init_boardT(void); //yes

extern int user_first(void);// yes
extern void play_game(void); // yes
extern int play_again(void); // yes
extern void computer_move(void); // yes
extern void player_move(void); // yes 
extern int find_win(char);// yes 
extern int middle_open(void); // yes
extern int find_corner(void); // yes 
extern int find_side(void); // yes 
extern int symbol_won(char); // yes 
extern int square_valid(int);// yes 

extern int getUserIn(); // yes 