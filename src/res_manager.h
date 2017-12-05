//handles all of the game resurces

#ifndef _RES_MANAGER
#define _RES_MANAGER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//number of textures
#define TEX_COUNT 37

enum TEXTURES{BACKGROUND=0,FLOOR,LABEL,BIRD_1,INSTRUCTIONS=BIRD_1+3,PIPE_UP,PIPE_DOWN,LARGE_NUMBERS,MIDDLE_NUMBERS=LARGE_NUMBERS+10,SCORE_PANNEL=MIDDLE_NUMBERS+10,BUTTON_PAUSE,BUTTON_RESUME,MEDALS,MEDAL_NEW=MEDALS+4};

typedef struct res_manager ResManager;

SDL_Texture **get_flappy_textures();

ResManager *get_res_manager();

SDL_Renderer *get_res_renderer();

SDL_Texture *get_res_texture(int n);

SDL_Texture **get_res_texture_list(int n);

int res_create_window();

int res_create_renderer();

int load_res_textures();

#endif // _RES_MANAGER
