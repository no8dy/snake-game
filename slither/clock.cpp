#include"native.h"
#include"clock.h"

int myclock::enable = 0;
list<myclock *> init_clk_list(){
	list<myclock *> tmp;
    return tmp;
}

list<myclock *> myclock::clks(init_clk_list());

void myclock::run(void){
	for(list<fp>::iterator i = task.begin();
		   	i != task.end() ; i++){
		(*i)();
	}
	refresh();
	return;
}

void myclock::set(void){
	struct itimerval tick;
	tick.it_value.tv_sec=0;
	tick.it_value.tv_usec=1000;
	tick.it_interval.tv_sec= 0 ;
	tick.it_interval.tv_usec= 7500;//5000
	setitimer(ITIMER_REAL, &tick, NULL);
	signal(SIGALRM, myclock::act);
	return;
}

void myclock::act(int sig){
	if(enable){
		for(list<myclock *>::iterator i = myclock::clks.begin();
				i != myclock::clks.end() ; i++){
			(*i)->run();
		}
	}
	return;
}

void myclock::add(void (* func)(void)){
	task.push_back(func);
	return;	
}

void myclock::del(void (* func)(void)){
	task.remove(func);
	return;
}
