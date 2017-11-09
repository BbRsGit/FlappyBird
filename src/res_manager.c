#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "res_manager.h"

const char resource_list[TEX_COUNT][40]={
    "res/background_day.png",
    "res/ground.png",
    "res/label_flappy_bird.png",
    "res/bird_orange_0.png",
    "res/bird_orange_1.png",
    "res/bird_orange_2.png",
    "res/instructions.png",
    "res/pipe_green_top.png",
    "res/pipe_green_bottom.png",
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
    "res/button_pause.png"
    };

struct res_manager
    {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture **textures;
    int n_textures;
    };

static ResManager res_manager;

ResManager *get_res_manager()
    {
    return &res_manager;
    }

SDL_Texture **get_flappy_textures()
    {
    return &res_manager.textures[BIRD_1];
    }


SDL_Renderer *get_res_renderer()
    {
    return res_manager.ren;
    }

SDL_Texture *get_res_texture(int n)
    {
    return res_manager.textures[n];
    }


int res_create_window()
    {
    if(!(res_manager.win = SDL_CreateWindow("FlappyBird",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,288,512,SDL_WINDOW_SHOWN)))
        return -1;
    return 0;
    }

int res_create_renderer()
    {
    if(!(res_manager.ren = SDL_CreateRenderer(res_manager.win,-1,SDL_RENDERER_ACCELERATED)))
        return -1;
    return 0;
    }

int load_res_textures()
    {
    SDL_Surface *sur;
    res_manager.textures=(SDL_Texture**)malloc(sizeof(SDL_Texture*)*TEX_COUNT);
    res_manager.n_textures=TEX_COUNT;
    int i;
    for(i=0;i<TEX_COUNT;i++)
        {
        if(!(sur=IMG_Load(resource_list[i])))
            return -1;
        res_manager.textures[i]=SDL_CreateTextureFromSurface(res_manager.ren,sur);
        }
    return 0;
    }


SDL_Texture **get_res_texture_list(int n)
    {
    return &res_manager.textures[n];
    }

