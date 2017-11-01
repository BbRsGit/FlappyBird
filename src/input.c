#include "input.h"
#include "setup.h"
#include <SDL2/SDL.h>

void input_handle(struct press* press)
    {
    SDL_Event event;
    press->is_pressed=0;
    while(SDL_PollEvent(&event))
        {
        switch(event.type)
            {
            case SDL_QUIT:
                game_quit();
            break;
            case SDL_MOUSEBUTTONDOWN:
                press->x=event.button.x;
                press->y=event.button.y;
                press->is_pressed=1;
            break;
            case SDL_MOUSEBUTTONUP:
                press->x=event.button.x;
                press->y=event.button.y;
                press->is_pressed=2;
            break;
            case SDL_MOUSEMOTION:
                press->x=event.motion.x;
                press->y=event.motion.y;
            break;
            case SDL_KEYDOWN:
                press->is_pressed=1;
            break;
            }
        }
    }
