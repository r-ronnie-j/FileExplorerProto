//This file is to contain all the constants that the file needs to use.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//We are defining the global constants in this file.
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int CURRENT_SCREEN_WIDTH =  1280;
int CURRENT_SCREEN_HEIGHT = 720;
Uint32 PIXEL_FORMAT;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface* surface;
TTF_Font *font ;
enum mainIndex{start,all,img,aud,vid,doc,none};
mainIndex mainDefault=start;