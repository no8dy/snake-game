#include"native.h"
#include"setting.h"
#include"snake.h"
#include"clock.h"
#include"item.h"
pair<int,int> dct[4] = { make_pair(-1 , 0)  ,
   						 make_pair( 1 , 0)  ,
						 make_pair( 0 ,-1)  ,
						 make_pair( 0 , 1) };

int **block;
//set clock
myclock clk;
int main(void){
	int i , j , ch;
	set(0);
	while((ch = getch()) != '\n' && ch != '\r');
	clear() , set(1);

// set clock
// code:
	//it works , as soon as be dimensiond

// create p1->s snake
// code:
	snake *p1 = NULL;
	snake *p2 = NULL;

//	mvprintw(0 , 10 , "lv %d" , p1->show_lv());//revise?
	clk.add(&snake::clk_hang);

	mk_food();
	mk_food();
	mk_food();
	mk_food();
	mk_food();
//	clk.add(&mk_tree);
//	clk.add(&bullet::clk_hang);

	while(1){
		ch = getch();
		switch(ch){
			case P1_NEWLIFE:
				if(!p1 || !p1->life){
					if(p1) snake::snakes.remove(p1) , delete p1;
					p1 = new snake(LINES/2 , COLS/2 , 2 , 15 , "snk_1" , 1);
				}
				break;
			case P2_NEWLIFE:
				if(!p2 || !p2->life){
					if(p2) snake::snakes.remove(p2) , delete p2;
					p2 = new snake(LINES/2 + 3 , COLS/2 , 2 ,15 , "snk_2" , 2);
				}
				break;
			case P1_UP:
				if(p1) p1->up()   ;//  , p1->move();
				break;
			case P1_DOWN:
				if(p1) p1->down() ;//  , p1->move();
				break;
			case P1_RIGHT:
				if(p1) p1->right();//  , p1->move();
				break;
			case P1_LEFT:
				if(p1) p1->left() ;//  , p1->move();
				break;
			case P2_UP:
				if(p2) p2->up()   ;//  , p2->move();
				break;
			case P2_DOWN:
				if(p2) p2->down() ;//  , p2->move();
				break;
			case P2_RIGHT:
				if(p2) p2->right() ;//  , p2->move();
				break;
			case P2_LEFT:
				if(p2) p2->left();//  , p2->move();
				break;
			case 99:{
//create bullet
//code:
//				if(!bullet::enable){
//					clk.add(&bullet::clk_hang);
//					bullet::enable = 1;
//				}
//				bullet* tem = new bullet(&p1->;
//				tem->fire();
				break; }// {} added , or CE...
			case KEY_ESC:
            case 'q':
				out();
				break;
			default:
//				mvprintw(7 , 7 , "%d" , ch);
				break;
		}
//		if(!p2->life){
//			break;
//		}
	}
	mvprintw(0 , 0 , "Game Over");
	while((ch = getch()) != 'q');
	endwin();
	return 0;
}
