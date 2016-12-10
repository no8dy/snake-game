#include"native.h"
#include"snake.h"
extern int **block;
extern pair<int,int> dct[4];
extern snake palyer;
int tree_num = 0;
int mk_speed = 900;
int p_exist = 0;

void mk_food(void){
	srand(time(NULL));
	int x , y;
	static int slow_cnt , quick_cnt;
	while(block[(y = rand() % LINES)][(x = rand() % COLS)]);
	block[y][x] = FOOD;
	mvaddch(y , x , FOOD);
	
	quick_cnt++ , slow_cnt++;
	if(quick_cnt == 1){
		while(block[(y = rand() % LINES)][(x = rand() % COLS)]);
		block[y][x] = QUICK;
		mvaddch(y , x , QUICK);
		quick_cnt = 0;
	}
	if(slow_cnt == 20){
		while(block[(y = rand() % LINES)][(x = rand() % COLS)]);
		block[y][x] = SLOW;
		mvaddch(y , x , SLOW);
		quick_cnt = 0;
	}
	
	return;
}

void mk_tree(void){
	const int area = LINES * COLS;
	const int max = LINES * COLS / 5 * 4;
	static int cnt = 0;	
	int item = MASS;
	if(tree_num <= max){
		if(cnt < mk_speed){
			cnt++;
			return;
		}
		else
			cnt = 0;

		int y , x , snakey , snakex;
		srand(time(NULL));
		mvprintw(LINES - 1 , COLS - 15 , "LINE %d COL %d" , LINES , COLS);
		while(1){
			if(block[y = (rand() % LINES)][x = (rand() % COLS)] == 0){
//				list<snake *>::iterator i;
//				for(i = snake::snakes.begin() ; 
//						i != snake::snakes.end() ; i++){
//
//					snakey	= (*i)->body.back().first;
//					snakex	= (*i)->body.back().second;
//					if(abs(y - snakey) < 3 && abs(x - snakex) < 3);
//					else break;
//				}
				break;
			}
			refresh();
		}
		tree_num++;
		if((tree_num > LINES * COLS / 25) && (!p_exist)) item = POW , p_exist = 1;
		block[y][x] = item;
		mvaddch(y , x , item);
		if((tree_num > LINES * COLS / 25) && (p_exist)) item = MASS;
		
//		float basic = (float)area / 900;
//		if(tree_num < LINES * COLS / 50){
//			mk_speed = (int)60;// / basic;
//		}
//		else if(tree_num < LINES * COLS / 45){
//			mk_speed = (int)75;// / basic;
//		}
//		else if(tree_num < LINES * COLS / 40){
//			mk_speed = (int)85;// / basic;
//		}
//		else if(tree_num < LINES * COLS / 30){
//			mk_speed = (int)96;// / basic;
//		}
//		else{
//			mk_speed = (int)100;// / basic;
//		}	
	}
	return;
}

void clean_tree(void){
	int i , j;
	for(i = 0 ; i < LINES ; i++){
		for(j = 0 ; j < COLS ; j++){
			if(block[i][j] == MASS){
				block[i][j] = 0;
				mvaddch(i , j , ' ');
			}
		}
	}
	tree_num = 0;
	return;
}
