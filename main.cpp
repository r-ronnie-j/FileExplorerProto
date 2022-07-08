#include <SDL2/SDL.h>
#include <iostream>
#include "const.h"
#include "init.h"
#include "Components.h"
#include "close.h"
#include "Eventhandler.h"

using namespace std;

bool setBackground(int r, int g, int b, int a);
bool setTopBar(Component&);
bool setSideBar(Component&);
bool setMainDisplay(Component&);

int main(int argc, char *argv[]) {
    if (!init()) {
        return -1;
    }
    bool game = true;
    SDL_Event event;
    while (game) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game = false;
            }
            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        SDL_GetWindowSize(window, &CURRENT_SCREEN_WIDTH, &CURRENT_SCREEN_HEIGHT);
                        break;
                }
            }
            if(event.type ==SDL_KEYDOWN){
                cout<<"Wow";
            }
        }
        if (!setBackground(255, 255, 255, 255)) {
            return -1;
        }
        Component topBar,sideBar,mainDisplay;
        if(!setTopBar(topBar)){
            return  -1;
        }
        if(!setSideBar(sideBar)){
            return -1;
        }
        if(!setMainDisplay(mainDisplay)){
            return -1;
        }
        topBar.drawBorder("d");
        sideBar.drawBorder("r");
        mainDisplay.drawBorder("ul");
        SDL_RenderPresent(renderer);
    }
    close();
    return 0;
   }

bool setBackground(int r, int g, int b, int a) {
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) < 0) {
        cout << "We failed to set the Render Color" << endl;
        cout << SDL_GetError() << endl;
        return false;
    }
    if (SDL_RenderClear(renderer) < 0) {
        cout << "We failed to renderClear" << endl;
        cout << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool setSideBar(Component& sideBar){

    sideBar.setRect(0,(int)SCREEN_HEIGHT/35,(int)CURRENT_SCREEN_WIDTH*0.2,CURRENT_SCREEN_HEIGHT-(int)SCREEN_HEIGHT/35);
    if(!sideBar.createTexture(237,237,237,255)){
        cout<<"Failed to create sideBar"<<endl;
        return false;
    };
    if(!sideBar.displayTexture()){
        cout<<"Failed to display the sideBar"<<endl;
        return false;
    };
    sideBar.drawBorder("d");
    return true;
}

bool setTopBar(Component& topBar){
    topBar.setRect(0,0,CURRENT_SCREEN_WIDTH,(int)SCREEN_HEIGHT/35);
    if(!topBar.createTexture(240,230,200,255)){
        cout<<"Failed to create topbar"<<endl;
        return false;
    };
    if(!topBar.displayTexture()){
        cout<<"Failed to display the topBar"<<endl;
        return false;
    };
    return true;
}

bool setMainDisplay(Component& mainDisplay){
    mainDisplay.setRect((int)CURRENT_SCREEN_WIDTH*0.2,(int)SCREEN_HEIGHT/35,CURRENT_SCREEN_WIDTH-(int)CURRENT_SCREEN_WIDTH*0.2,CURRENT_SCREEN_HEIGHT-(int)SCREEN_HEIGHT/35);

    if(!mainDisplay.createTexture(251,250,200,255)){
        cout<<"Failed to create mainDisplay"<<endl;
        return false;
    };
    if(!mainDisplay.displayTexture()){
        cout<<"Failed to display the mainDisplay"<<endl;
        return false;
    };
    return true;
}