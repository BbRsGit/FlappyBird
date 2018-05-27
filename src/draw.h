#ifndef _DRAW_H
#define _DRAW_H

#include "flappy.h"
#include "towers.h"

void background_update();

void draw_background(int delta);

void draw_all(Flappy *flappy,Tower *towers,int num,int delta);

#endif //_DRAW_H
