#ifndef _TOWERS_H
#define _TOWERS_H

#include <SDL2/SDL.h>

typedef struct Tower
	{
	SDL_Rect upper;
	SDL_Rect bottom;
	}Tower;

void tower_init(Tower *towers,int num);

int tower_collided(Tower *tower,SDL_Rect *rect);

int tower_update(Tower *towers,int num);

int tower_draw(Tower *towers,int num);

#endif // _TOWERS_H
