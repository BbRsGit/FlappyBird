#ifndef _FLAPPY_H
#define _FLAPPY_H

#include <SDL2/SDL.h>

typedef struct Flappy
	{
	SDL_Rect collision;
	float y_vel;
	int texture_id;
	float rotation;
	int cur_texture;
	}Flappy;

#include "towers.h"

/** Resets flappy bird
  * Sets pozition, texture list, rotation, speed...
  */
void flappy_reset(Flappy *flappy);

/** Draws flappy bird depending on the y_vel and state
  */
void flappy_draw(Flappy *flappy);

/** Updates flappy bird
  */
void flappy_update(Flappy *flappy,int is_jump);

/** checks if a collision has occured
 * */
void flappy_collision(Flappy *flappy,Tower *tower,int num);

#endif // _FLAPPY_H
