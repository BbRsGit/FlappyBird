#ifndef _FLAPPY_H
#define _FLAPPY_H

#include "res_manager.h"
#include "input.h"

/** Resets flappy bird
  * Sets pozition, texture list, rotation, speed...
  */
void flappy_reset();

/** Draws flappy bird depending on the y_vel and state
  * @param delta - time in ms since the function has been called last
  */
void flappy_draw(int delta);

/** Updates flappy bird
  * @param delta - time in ms since the function has been called last
  */
void flappy_update(struct press *press,int delta);

SDL_Rect flappy_get_rect();

#endif // _FLAPPY_H
