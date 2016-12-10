#include"native.h"
#include"snake.h"
#include"bullet.h"
#include"item.h"
#include"clock.h"

extern int **block;
extern class clock clk;
extern pair<int,int> dct[4];

int snake::enable = 0;
list<snake *> init_snake_list(){
	list<snake *> tmp;
    return tmp;
}

list<snake *> snake::snakes(init_snake_list());

void snake::clk_hang(void){
	
//	static int j;	
	if(enable){
//		j = 0;
		list<snake *>::iterator i;
		for(i = snakes.begin() ; i != snakes.end() ; i++){
			(*i)->move_cnt();
//			mvprintw(j , 0 , "snkh %d %d %a" 
//					(*i)->body.back().first
//					(*i)->body.back().second , (*i));
//			j++;
		}
	}
	refresh();
	return;
}

snake::snake(int y , int x , int ini_dir , int ini_spd , const char *ini_name , int ini_blk){
//	int static j =0;
	int i;
	lv = 4 , dir = ini_dir;
	life = 1 , speed = ini_spd;
	strcpy(this->name , ini_name) , this->blk = ini_blk;
	wait_food = 0;
	static_for_cnt = 0;

	for(i = 3 ; i >= 0 ; i--){
		block[y][x + i] = 1;
		this->body.push(make_pair(y , x + i));
		mvaddch(this->body.back().first , this->body.back().second , BODY);		
	}

	mvaddch(this->body.back().first , this->body.back().second , HEAD);
	
	if(!enable) enable = 1;
	snakes.push_back(this);

//	mvprintw(j + 10 , 0 , "snk added %d" , j);
//	j++;
}

void snake::move_cnt(void){
//	static int acc = 0;
//	static int i;
//	mvprintw(0 , 25 , "cnt %d" , i++);
//	refresh();

	if(static_for_cnt < this->speed - 1){
		static_for_cnt++;
		return;
	}
	else
		static_for_cnt = 0;

//	mvprintw(0 , 50 , "spd %d" , this->speed);
//	static int j;
//	mvprintw(0 , 35 , "acc %d" , j++);
//	refresh();

	this->move();
	return;
}

void snake::move(void){
	if(!life) return;

	int nxtx , nxty , headx , heady;
	heady = this->body.back().first , nxty = heady + dct[dir].first;
	headx = this->body.back().second , nxtx = headx + dct[dir].second;

	if(nxty < 0 || nxty > LINES - 1 || nxtx < 0 || 
			nxtx > COLS - 1 || block[nxty][nxtx] == MASS ){

		while(!body.empty()){
			block[body.front().first][body.front().second] = 0;
			mvaddch(body.front().first , body.front().second , ' ');
			body.pop();
		}
		mvaddch(heady , headx , FOOD);
		block[heady][headx] = FOOD;
		life = 0;
//		snakes.remove(this); // suspicious bug
		return;
	}

	if(wait_food) 
		block[nxty][nxtx] = wait_food , wait_food = 0;

	int type;
 	type = block[nxty][nxtx];

	if(type == FOOD){
		mk_food();
		lv++;
	}
	else{
		if(type == QUICK){
			if(speed >= 15)
				speed -= 7 ;
			else if(speed > 5)
				speed -= 3;
			else if(speed > 1)
				speed -= 1;	
			mvprintw(LINES - 1 , 0 , "spd = %d" , speed);//attention
		}
		else if(type == SLOW){
			speed += 1;	
		}
		else if(type == POW){
			clean_tree();
		}
		else if(type != blk && type != 0){
			while(!body.empty()){
				block[body.front().first][body.front().second] = 0;
				mvaddch(body.front().first , body.front().second , ' ');
				body.pop();
			}
			mvaddch(heady , headx , FOOD);
			block[heady][headx] = FOOD;
			life = 0;
			//		snakes.remove(this); // suspicious bug
			return;
		}
		block[this->body.front().first][this->body.front().second] = 0;
		mvaddch(this->body.front().first , this->body.front().second , ' ');
		this->body.pop();
	}	
	
	block[nxty][nxtx] = blk;
	mvaddch(nxty , nxtx , HEAD);//add new head
	mvaddch(heady , headx , BODY);
	this->body.push(make_pair(nxty , nxtx));
	
	return;
}
