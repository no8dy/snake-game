#include<iostream>
#include<cstdlib>
#include<cstring>
#include<utility>
#include<queue>
#include<vector>
#include<ncurses.h>
#include<signal.h>
#include<time.h>
#include<sys/time.h>
#include"setting.h"
#include"move.h"
#define HEAD 'H'
#define BODY 'B'
#define FOOD 'O'
extern int **block , lv;
void set(int mod){
	initscr();
	cbreak();
	nonl();
	noecho();
	intrflush(stdscr,FALSE);
	keypad(stdscr,TRUE);
	curs_set(0);//disable visual cursor
	box(stdscr,'|','-');
	refresh();
	if(mod == 1) mvprintw(LINES - 1 , 3 , "loaded---");
	if(mod == 1) mvprintw(0 , 10 , "lv %d" , lv);

	return;
}
void out(void){

	endwin();
	free(block);
	exit(0);
	return;
}
