#include"native.h"
#include"setting.h"

extern int **block , lv;



void set(int mod){
	int i , j;	
	if(mod == 0){

		initscr() , cbreak() , nonl() , noecho();
		intrflush(stdscr,FALSE) , keypad(stdscr,TRUE);
		curs_set(0);//invisible cursor

		mvprintw(LINES / 3 + 3 , 
				COLS / 3 , "Enter to Start");
		mvprintw(LINES / 3 + 1 , 
				COLS / 3 , "arrow key to change direction");
		mvprintw(LINES / 3 + 2 , 
				COLS / 3 , "space to clear tree");
		mvprintw(LINES / 3 + 4 , 
				COLS / 3 , "'q' to quit");
        mvprintw(LINES / 3 + 5 , COLS / 3 , 
                "P1 %c to new game , arrow key to control" , P1_NEWLIFE);
        mvprintw(LINES / 3 + 6 , COLS / 3 , 
                "P2 %c to new game , wasd key to control" , P2_NEWLIFE);
	}
	if(mod == 1){

		block = (int **)malloc(LINES * sizeof(void *) + 
							   LINES * COLS * sizeof(int));
		int *iax = (int *)(block + LINES);

		for(j = 0 ; j != LINES ; ++j , iax += COLS)
			block[j] = iax;

		for(i = 0 ; i < LINES ; i++)
			for(j = 0 ; j < COLS ; j++)
				block[i][j] = 0;
		for(i = 0 ; i < LINES ; i++)
			block[i][0] = MASS , block[i][COLS - 1] = MASS;
		for(i = 0 ; i < COLS ; i++)
			block[0][i] = MASS , block[LINES - 1][i] = MASS;

		clear();
		
	}

	box(stdscr,'|','-');
	refresh();
	return;
}

void out(void){
	endwin();
	free(block);
	exit(0);
	return;
}
