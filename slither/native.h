#ifndef _NATIVE_H_
#define _NATIVE_H_

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<utility>
#include<queue>
#include<vector>
#include<list>
#include<cstdlib>
#include<ncurses.h>
#include<signal.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>

using namespace std;

#define HEAD 'H'
#define BODY 'B'
#define DEAD 'X'
#define FOOD 'O'
#define MASS 'W'
#define BULLET 'F'
#define QUICK 'Q'
#define SLOW 'S'
#define POW 'P'

typedef void (*fp)();
//void (* func)(void)

#define P1_NEWLIFE '/'
#define P1_UP KEY_UP
#define P1_DOWN KEY_DOWN
#define P1_RIGHT KEY_RIGHT
#define P1_LEFT KEY_LEFT

#define P2_NEWLIFE '2'
#define P2_UP      'w'
#define P2_DOWN    's'
#define P2_RIGHT   'd'
#define P2_LEFT    'a'

#define KEY_ESC        27

#endif
