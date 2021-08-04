//handles all of the game resurces

#ifndef _RES_MANAGER
#define _RES_MANAGER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//number of textures
#define TEX_COUNT 46

enum TEXTURES{BACKGROUND=0,
			  FLOOR=BACKGROUND+2,
			  LABEL,
			  BIRD_1,
			  BIRD_2=BIRD_1+3,
			  BIRD_3=BIRD_2+3,
			  INSTRUCTIONS=BIRD_3+3,
			  PIPE_UP,
			  PIPE_DOWN=PIPE_UP+2,
			  LARGE_NUMBERS=PIPE_DOWN+2,
			  MIDDLE_NUMBERS=LARGE_NUMBERS+10,
			  SCORE_PANNEL=MIDDLE_NUMBERS+10,
			  BUTTON_PAUSE,
			  BUTTON_RESUME,
			  MEDALS,
			  MEDAL_NEW=MEDALS+4
			};

typedef struct res_manager ResManager;

void get_res_render_draw();

int get_flappy_textures_id();

void get_res_render_ex(int texture_id,SDL_Rect *dest_rect,double rotation,int flip);

void get_res_render(int texture_id,SDL_Rect *src,SDL_Rect *dest);

int res_create_window();

int res_create_renderer();

int load_res_textures();

#endif // _RES_MANAGER
