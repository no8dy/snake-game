#ifndef _SNAKE_H_
#define _SNAKE_H_

class snake{
private:

	int wait_food;
	int static_for_cnt;

public:
	snake(int y , int x , int ini_dir , int ini_spd , const char *ini_name , int ini_blk);

	int lv;
	int dir;
	int blk;
	int life;
	int speed;
	char name[10];

	static int enable;
	static void clk_hang(void);
	static list<snake *> snakes;

	void move(void);
	void move_cnt(void);

	queue< pair<int,int> > body;

	int up(void)
		{ return this->dir = 0; }
	int down(void)
		{ return this->dir = 1; }
	int left(void)
		{ return this->dir = 2; }
	int right(void)
		{ return this->dir = 3; }

	void get_food(int food){
		wait_food = food;
		return; }
};

#endif
