#ifndef _BULLET_H_
#define _BULLET_H_
class bullet{
private:
	int fire_y , fire_x;
	int prey , prex;
	int dir;
	int static_for_cnt;
	snake *owner;

public:
	bullet(snake *who)
	{ this->owner = who;
   	  prey = - 1 , prex = - 1;
   	  if(!enable) enable = 1 ;
   	  static_for_cnt = 0;	 }

	static int enable;
	static void clk_hang(void);
	static list<bullet *> bullets;

	void fire_cnt(void);
	void fire(void);
};
#endif
