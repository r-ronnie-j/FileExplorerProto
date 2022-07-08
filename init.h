//This file is used to initiate all the variables we might be using in the program

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "iostream"

using namespace std;
bool init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        cout<<"We failed to initialize the SDL"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    if(TTF_Init()<0){
        cout<<"Failed to initialize the TTF file"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    SDL_DisplayMode mode;
    if(SDL_GetDesktopDisplayMode(0,&mode)<0){
        cout<<"We failed to get the display mode"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    CURRENT_SCREEN_HEIGHT=SCREEN_HEIGHT = mode.h;
    CURRENT_SCREEN_WIDTH = SCREEN_WIDTH = mode.w;
    PIXEL_FORMAT = mode.format;
    window = SDL_CreateWindow("File Explorer",0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_RESIZABLE);
    if(!window){
        cout<<"Failed to create the window"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout<<"We failed to create a renderer"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    surface = SDL_GetWindowSurface(window);
    if(!surface){
        cout<<"Window surface was unable to generate"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    font = TTF_OpenFont("/media/ronnie/Files/CPlusPlus/Home/fonts/OpenSans-Light.ttf",12);
    if(!font){
        cout<<"We failed to initialize the font"<<endl;
        cout<<SDL_GetError()<<endl;
        return false;
    }
    return true;
}
