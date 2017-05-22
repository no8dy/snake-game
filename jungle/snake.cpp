#include<iostream>
#include<cstdlib>
#include<cstring>
#include<utility>
#include<queue>
#include<vector>
#include<ncurses.h>
#include<thread>
#include<signal.h>
#include<time.h>
#include<sys/time.h>
#include"setting.h"
#include"move.h"
#include"fire.h"
#include"tree.h"
#define HEAD 'H'
#define BODY 'B'
#define FOOD 'O'
using namespace std;
queue< pair<int,int> > body;
pair<int,int> dct[4] = { make_pair(1 , 0) , make_pair(0 , 1) , make_pair(-1 , 0) , make_pair(0 , -1) };
int **block;
int direct = 3 , die = 0 , speed = 20 , acc = 0 , on_gun = 1 , lv = 4;
//pthread_t id;
int main(void){
	int i , j , ch;
	struct itimerval tick;
	tick.it_value.tv_sec=1;
	tick.it_value.tv_usec=0;
	tick.it_interval.tv_sec=0;//
	tick.it_interval.tv_usec=5000;//

	set(0);

	mvprintw(LINES / 3 + 3 , COLS / 3 , "Enter to Start");
	mvprintw(LINES / 3 + 1 , COLS / 3 , "arrow key to change direction");
	mvprintw(LINES / 3 + 2 , COLS / 3 , "space to clear tree");
	mvprintw(LINES / 3 + 4 , COLS / 3 , "'q' to quit");

	while((ch = getch()) != '\n' && ch != '\r');

	clear();
	set(1);
	//std::vector<std::vector<int> > block(LINES, std::vector<int>(COLS));
	block = (int **)malloc(LINES * sizeof(void *) + LINES * COLS * sizeof(int));
	int *iax = (int *)(block + LINES);
	for(j = 0 ; j != LINES ; ++j , iax += COLS){
		block[j] = iax;
	}

	for(i = 0 ; i < LINES ; i++)
		for(j = 0 ; j < COLS ; j++)
			block[i][j] = 0;
	for(i = 0 ; i < LINES ; i++)
		block[i][0] = 1 , block[i][COLS - 1] = 1;
	for(i = 0 ; i < COLS ; i++)
		block[0][i] = 1 , block[LINES - 1][i] = 1;

	for(i = 3 ; i >= 0 ; i--){
		block[LINES/2][COLS/2 + i] = 1;
		body.push(make_pair(LINES/2 , COLS/2 + i));
		mvaddch(body.back().first , body.back().second , BODY);
	}
	mvaddch(body.back().first , body.back().second , HEAD);

//	mvaddstr(0 , 1 , "Any Button to Start");
//	getch();
//`	mvaddstr(0 , 1 , "-------------------");

	setitimer(ITIMER_REAL, &tick, NULL);
	gen_ball();
	go(direct);
	signal(SIGALRM, auto_go);
	//	signal(SIGALRM, fire_cnt);
	while(1){
		ch = getch();
		switch(ch){
			case KEY_UP:
				go(direct = 2);
				break;
			case KEY_DOWN:
				go(direct = 0);
				break;
			case KEY_RIGHT:
				go(direct = 1);
				break;
			case KEY_LEFT:
				go(direct = 3);
				break;
			case 32:
				if(on_gun){
					fire();
					mvprintw(LINES - 1 , 3 , "shouting");
					//		pthread_create(&id,NULL,(void *)fire,&direct);
					thread t1(fire);
					t1.join();
				}
				break;
			case 'q':
				out();
				break;
		}
		if(die){
			break;
		}
	}

	while((ch = getch()) != 'q');
	endwin();
	return 0;
}

