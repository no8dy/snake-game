#include"native.h"
#include"item.h"
#include"snake.h"
#include"clock.h"
#include"bullet.h"
extern int **block;
extern pair<int,int> dct[4];
extern int tree_num , p_exist;
extern snake player;

int bullet::enable = 0;
list<bullet *> init_bullet_list(){
	list<bullet *> tmp;
	return tmp;
}

list<bullet *> bullet::bullets(init_bullet_list());

void bullet::clk_hang(void){
//	if(enable){
		list<bullet *>::iterator i;
		for(i = bullets.begin() ; i != bullets.end() ; i++){
			(*i)->fire_cnt();
		}
//	}
	return;
}

void bullet::fire(void){
	static int time = 0;
	int i;
	dir = owner->dir;
	fire_y = owner->body.back().first;
	fire_x = owner->body.back().second;
	
	fire_y += 2 * dct[dir].first;//if revise?
	fire_x += 2 * dct[dir].second;
	bullets.push_back(this);
	return;
}

void bullet::fire_cnt(void){
//	static int cnt = 0;
	if(static_for_cnt < 1){
		static_for_cnt++;
		mvprintw( 7 , 0 , "bult %d" , static_for_cnt);
		return;
	}
	else
		static_for_cnt = 0;

	if(fire_y < 0 || fire_y > LINES - 1 || fire_x < 0 || fire_x > COLS - 1){
		//colli* border,remove bullet
		mvprintw( 7 , 0 , "fin1" , static_for_cnt);
		mvprintw( 8 , 0 , "%d %d" , fire_y
				 , fire_x);
		bullets.remove(this);
		delete this;	
		return;
	}

	int onblock = block[fire_y][fire_x];
	if(onblock){
		if(onblock == FOOD || onblock == MASS || onblock == POW){
			if(onblock == POW)
				clean_tree();

			if(onblock == MASS) tree_num--;
			mvaddch(this->prey , this->prex , ' ');
			mvaddch(fire_y , fire_x , ' ');

			if(onblock == FOOD){
				//??
				owner->get_food(FOOD);
			}
			block[fire_y][fire_x] = 0;
			this->prey = -1 , this->prex = -1;
		}
		mvaddch(this->prey , this->prex , ' ');
	
		if(owner->lv < 18){
			if(onblock != 0){
				mvprintw( 7 , 0 , "fin3" , static_for_cnt);
				bullets.remove(this);
				delete this;
				return;
			}
		}
		else{
			if(onblock == 1){
				mvprintw( 7 , 0 , "fin3" , static_for_cnt);
				bullets.remove(this);
				delete this;
				return;
			}
		}
	}
	mvprintw(10 , 0 , "hello");
	mvaddch(fire_y , fire_x , BULLET);
	if(this->prey != -1)
		mvaddch(this->prey , this->prex , ' ');
	this->prey = fire_y;
	this->prex = fire_x;
	fire_y += dct[dir].first;
	fire_x += dct[dir].second;
	refresh();
	return;
}
