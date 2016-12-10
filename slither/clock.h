#ifndef _CLOCK_H_
#define _CLOCK_H_

typedef void (*fp)();

class myclock{
public:
	myclock()
   	{ if(!enable) enable = 1 , set();
		clks.push_back(this); }
	static int enable;
	static list<myclock *> clks;
	static void set(void);
	static void act(int sig);
	
	void add(void (* func)(void));
	void del(void (* func)(void));
	void run(void);
private:
	list<fp> task;
};
#endif
