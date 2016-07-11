#include<iostream>
#include<cstdlib>
#include<cstring>
#include<utility>
#include<queue>
#include<vector>
#include<cstdlib>
#include<ncurses.h>
#include<signal.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include"move.h"
#define HEAD 'H'
#define BODY 'B'
#define FOOD 'O'
#define FIRE 'F'
using namespace std;
extern int **block;
extern queue< pair<int,int> > body;
extern pair<int,int> dct[4];
extern int direct;

int tree_num = 0;
int mk_speed = 75;
int p_exist = 0;

void mk_tree(void){
	const int area = LINES * COLS;
	const int max = LINES * COLS / 5 * 4;
	static int cnt = 0;	
	int item = 'T';
	if(tree_num <= max){
		if(cnt < mk_speed){
			cnt++;
			return;
		}
		else
			cnt = 0;
		int y , x , yyy , xxx;
		srand(time(NULL));
		mvprintw(LINES - 1 , COLS - 15 , "LINE %d COL %d" , LINES , COLS);
		while(1){
			if(block[y = (rand() % LINES)][x = (rand() % COLS)] == 0){
		   		yyy	= body.back().first;
			   	xxx	= body.back().second;
				if(abs(y - yyy) < 3 && abs(x - xxx) < 3);
				else break;
			}
//			mvprintw(5 , 0 , "%d > LINES , %d > COLS , %d - %d, %d - %d" , LINES , COLS ,  y , yyy, x , xxx);
			refresh();
//			sleep(1);
		}
		tree_num++;
		if((tree_num > LINES * COLS / 25) && (!p_exist)) item = 'P' , p_exist = 1;
		block[y][x] = item;
		mvaddch(y , x , item);
		if((tree_num > LINES * COLS / 25) && (p_exist)) item = 'T';
		

//		float basic = (float)area / 900;
		if(tree_num < LINES * COLS / 50){
			mk_speed = (int)60;// / basic;
		}
		else if(tree_num < LINES * COLS / 45){
			mk_speed = (int)75;// / basic;
		}
		else if(tree_num < LINES * COLS / 40){
			mk_speed = (int)85;// / basic;
		}
		else if(tree_num < LINES * COLS / 30){
			mk_speed = (int)96;// / basic;
		}
		else{
			mk_speed = (int)100;// / basic;
		}	
	
	}
	return;
}


