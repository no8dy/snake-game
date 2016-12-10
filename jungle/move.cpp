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
#include"fire.h"
#include"tree.h"
//#include"monster.h"
#define HEAD 'H'
#define BODY 'B'
#define FOOD 'O'
using namespace std;
extern int **block;
extern queue< pair<int,int> > body;
extern pair<int,int> dct[4];
extern int direct , die , speed , acc , lv;
void gen_ball(void){
	srand(time(NULL));
	int x , y;
	while(block[(y = rand() % LINES)][(x = rand() % COLS)]);
	block[y][x] = 2;
	mvaddch(y , x , FOOD);
	return;
}
void go(int d){
	if(die) return;
	if(d != -1) acc = 0;
	
	int x , y , headx , heady;
	heady = body.back().first , y = heady + dct[direct].first;
	headx = body.back().second , x = headx + dct[direct].second;

	if(d == 9) block[y][x] = 2;
	if(block[y][x] == 'P'){
		mvaddch(y , x , ' ');
		block[y][x] = 0;
		clean_tree();
		return;
	}

	if(block[y][x] != 2){
		block[body.front().first][body.front().second] = 0;
		mvaddch(body.front().first , body.front().second , ' ');
		body.pop();
	}
	else{
		lv++;
		mvprintw(0 , 10 , "lv %d" , lv);
		gen_ball();
		printf(0 , 25 , "genball");
	}

	if(block[y][x] != 0 && block[y][x] != 2){
		mvaddch(y , x , HEAD);
		mvaddch(heady , headx , BODY);
		die = 1;
		mvprintw(LINES / 3    , COLS / 3 , "/********************");
		mvprintw(LINES / 3 + 1, COLS / 3 , "*                   *");
		mvprintw(LINES / 3 + 2, COLS / 3 , "*   Game Over       *");
		mvprintw(LINES / 3 + 3, COLS / 3 , "*       q to quit   *");
		mvprintw(LINES / 3 + 4, COLS / 3 , "*                   *");
		mvprintw(LINES / 3 + 5, COLS / 3 , "*********************/");
	}
	else{
		block[y][x] = 1;
		mvaddch(y , x , HEAD);
		mvaddch(heady , headx , BODY);
		body.push(make_pair(y , x));
	}	
	return;
}
void auto_go(int a){
//	static int acc = 0;
	fire_cnt();
	mk_tree();
	if(acc < speed){
		acc++;
		return;
	}
	else
		acc = 0;
	go(-1);
	refresh();
	return;
}	


