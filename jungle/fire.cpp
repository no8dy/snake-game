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
extern int direct , die , speed , acc , on_gun , tree_num , lv , p_exist;
int fire_y , fire_x , prey = -1 , prex = -1 , dt , on = 0;
void clean_tree(void){
	int i , j;
	for(i = 0 ; i < LINES ; i++){
		for(j = 0 ; j < COLS ; j++){
			if(block[i][j] == 'T'){
				block[i][j] = 0;
				mvaddch(i , j , ' ');
			}
		}
	}
	tree_num = 0;
	return;
}
void fire(void){
	static int time = 0;
	int i;
	dt = direct;
	fire_y = body.back().first;
	fire_x = body.back().second;
	on_gun = 0;
//	mvprintw(0 , LINES - 1 , "now %d %d direct %d value%d" , fire_y , fire_x , dt , block[fire_y][fire_x]);

	fire_y += 2 * dct[dt].first;
	fire_x += 2 * dct[dt].second;
	on = 1;

//	mvprintw(0 , 10 , "fire %d return" , time++);
	return;
}
void fire_cnt(void){
	static int cnt = 0;
	if(on){
		if(cnt < 1){
			cnt++;
			return;
		}
		else
			cnt = 0;

		if(fire_y < 0 || fire_y > LINES - 1 || fire_x < 0 || fire_x > COLS - 1){
			on = 0;
			on_gun = 1;
			mvprintw(LINES - 1 , 3 , "loaded---");
			return;
		}
		int onblock = block[fire_y][fire_x];
		if(onblock){
			if(onblock == 2 || onblock == 'T' || onblock == 'P'){
				if(onblock == 'P')
					clean_tree();

				if(onblock == 'T') tree_num--;
				mvaddch(prey , prex , ' ');
				mvaddch(fire_y , fire_x , ' ');

				if(onblock == 2) go(9);
				block[fire_y][fire_x] = 0;
				prex = -1 , prey = -1;
			}
			mvaddch(prey , prex , ' ');
			if(lv < 18){//18
				if(onblock != 0){
					on = 0 , on_gun = 1 , mvprintw(LINES - 1 , 3 , "loaded---");
					return;
				}
			}
			else{
				if(onblock == 1){
					on = 0 , on_gun = 1 , mvprintw(LINES - 1 , 3 , "loaded---");
					return;
				}
			}
		}
		mvaddch(fire_y , fire_x , FIRE);
		if(prey != -1)
			mvaddch(prey , prex , ' ');
		prey = fire_y;
		prex = fire_x;
		fire_y += dct[dt].first;
		fire_x += dct[dt].second;
//		mvprintw(0 , LINES - 1 , "now %d %d direct %d" , fire_y , fire_x , dt);
	}
	refresh();
	return;
}

