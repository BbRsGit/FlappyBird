#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>

#include "res_manager.h"

const char resource_list[TEX_COUNT][40]={
    "res/background_day.png",
	"res/background_night.png",
    "res/ground.png",
    "res/label_flappy_bird.png",
    "res/bird_orange_0.png",
    "res/bird_orange_1.png",
    "res/bird_orange_2.png",
    "res/bird_blue_0.png",
    "res/bird_blue_1.png",
    "res/bird_blue_2.png",
    "res/bird_red_0.png",
    "res/bird_red_1.png",
    "res/bird_red_2.png",
    "res/instructions.png",
    "res/pipe_green_top.png",
	"res/pipe_red_top.png",
    "res/pipe_green_bottom.png",
	"res/pipe_red_bottom.png",
    "res/number_large_0.png",
    "res/number_large_1.png",
    "res/number_large_2.png",
    "res/number_large_3.png",
    "res/number_large_4.png",
    "res/number_large_5.png",
    "res/number_large_6.png",
    "res/number_large_7.png",
    "res/number_large_8.png",
    "res/number_large_9.png",
    "res/number_middle_0.png",
    "res/number_middle_1.png",
    "res/number_middle_2.png",
    "res/number_middle_3.png",
    "res/number_middle_4.png",
    "res/number_middle_5.png",
    "res/number_middle_6.png",
    "res/number_middle_7.png",
    "res/number_middle_8.png",
    "res/number_middle_9.png",
    "res/panel_score.png",
    "res/button_pause.png",
    "res/button_resume.png",
    "res/medal_bronze.png",
    "res/medal_silver.png",
    "res/medal_gold.png",
    "res/medal_platinum.png",
    "res/label_new.png"
    };

struct res_manager
    {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture **textures;
    int n_textures;
    SDL_Surface *icon;
    };

static ResManager res_manager;

int get_flappy_textures_id()
    {
    return BIRD_1+(rand()%3)*3;
    }

void get_res_render_draw()
	{
	SDL_RenderPresent(res_manager.ren);
	SDL_RenderClear(res_manager.ren);
	}

void get_res_render_ex(int texture_id,SDL_Rect *dest_rect,double rotation,int flip)
	{
	SDL_RenderCopyEx(res_manager.ren,res_manager.textures[texture_id],NULL,dest_rect,rotation,NULL,flip);
	}

void get_res_render(int texture_id,SDL_Rect *src,SDL_Rect *dest)
	{
	SDL_RenderCopy(res_manager.ren,res_manager.textures[texture_id],src,dest);
	}

int res_create_window()
    {
    if(!(res_manager.win = SDL_CreateWindow("FlappyBird",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,288,512,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
        return -1;
    res_manager.icon=IMG_Load("res/flappy_bird_icon.png");
    if(res_manager.icon)
        SDL_SetWindowIcon(res_manager.win,res_manager.icon);
    return 0;
    }

int res_create_renderer()
    {
    if(!(res_manager.ren = SDL_CreateRenderer(res_manager.win,-1,SDL_RENDERER_ACCELERATED)))
		{
		return -1;
		}
	//we made the game resizable and chose to use logical size as given size
	SDL_RenderSetLogicalSize(res_manager.ren,288,512);
    return 0;
    }

int load_res_textures()
    {
    res_manager.textures=(SDL_Texture**)malloc(sizeof(SDL_Texture*)*TEX_COUNT);
    res_manager.n_textures=TEX_COUNT;
    int i;
    for(i=0;i<TEX_COUNT;i++)
        {
        if(!(res_manager.textures[i]=IMG_LoadTexture(res_manager.ren,resource_list[i])))
        	return -1;
        }
    return 0;
    }
