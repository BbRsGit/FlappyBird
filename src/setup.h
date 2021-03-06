//file that takes care of initializing and seting up the game and resources
#ifndef _SETUP_H
#define _SETUP_H

#define GAME_SPEED 1.3

#include "res_manager.h"
#include "score.h"

/** Sets up SDL and IMG
    returns -1 on error else 0
*/
int game_init();

/** Sets up the window and the renderer renderer
  * Returns -1 on error else 0
  */
int game_screen_init();

/** Loads all of the resources required for the game
  * Return 0 on error
  */
int game_load_res();

/** Called by exit(), closes SDL and saves highscore
  */
void game_quit();

#endif //_SETUP_H
