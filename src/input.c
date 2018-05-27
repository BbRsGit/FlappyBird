#include "input.h"
#include "setup.h"
#include <SDL2/SDL.h>

int input_handle()
    {
    SDL_Event event;
	int ret_val=0;
    while(SDL_PollEvent(&event))
        {
        switch(event.type)
            {
            case SDL_QUIT:
                exit(0);
            break;
            case SDL_MOUSEBUTTONDOWN:
            	ret_val=1;
            break;
            case SDL_MOUSEBUTTONUP:
                ret_val=2;
            break;
            case SDL_KEYDOWN:
                ret_val=3;
            break;
            }
        }
	return ret_val;
    }
