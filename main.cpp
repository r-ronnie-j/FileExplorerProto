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
bool setTopBarInterior(InputComponent&,InputComponent&,ButtonComponent&,ButtonComponent&);

int main(int argc, char *argv[]) {
    if (!init()) {
        return -1;
    }
    bool game = true;
    SDL_Event event;
    Component topBar,sideBar,mainDisplay;
    InputComponent i1,i2;
    ButtonComponent b1,b2;
    b1.setText("Search");
    b1.setTarget(&i1);
    b2.setTarget(&i2);
    b2.setText("GO");
    addTargetInput(&i1);
    addTargetInput(&i2);
    addTargetButton(&b1);
    addTargetButton(&b2);
    while (game) {
        if (!setBackground(255, 255, 255, 255)) {
            return -1;
        }

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
        if(!setTopBarInterior(i1,i2,b1,b2)){
            return -1;
        }

        while (SDL_PollEvent(&event)) {
            if(event.type ==SDL_KEYDOWN){
                textInputHandler(event.key);
            }
            if(event.type==SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    mouseClickHandler();
                }
            }
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
        }
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

    sideBar.setRect(0,(int)SCREEN_HEIGHT/40,(int)CURRENT_SCREEN_WIDTH*0.2,CURRENT_SCREEN_HEIGHT-(int)SCREEN_HEIGHT/40);
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
    topBar.setRect(0,0,CURRENT_SCREEN_WIDTH,(int)SCREEN_HEIGHT/40);
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

bool setTopBarInterior(InputComponent& i1,InputComponent&i2,ButtonComponent& b1,ButtonComponent& b2){
    if(!b1.createButtonTexture()){
        cout<<"Button texture 1"<<endl;
        return false;
    };
    if(!b2.createButtonTexture()){
        cout<<"Button texture 2"<<endl;
        return false;
    };
    i1.setRect(1,1,(CURRENT_SCREEN_WIDTH/2 - b1.getWidth())*0.95,SCREEN_HEIGHT/40-4);
    b1.setRect(i1.getWidth(),1);
    i2.setRect(CURRENT_SCREEN_WIDTH/2,1,(CURRENT_SCREEN_WIDTH/2-b2.getWidth())*0.95,SCREEN_HEIGHT/40-4);
    b2.setRect(CURRENT_SCREEN_WIDTH/2+i2.getWidth(),1);
    if(!i1.createTextTexture()){
        cout<<"i1 texture building failed"<<endl;
        return false;
    }
    if(!i2.createTextTexture()){
        cout<<"i2 texture creation failed"<<endl;
        return false;
    }
    i1.drawBorder("udlr");
    i2.drawBorder("udlr");
    b1.drawBorder("udlr");
    b2.drawBorder("udlr");
    if(!i1.displayTexture()){
        cout<<"Display of i1 texture failed"<<endl;
        return false;
    }
    if(!i2.displayTexture()){
        cout<<"Display of texture i2 failed"<<endl;
        return false;
    }
    if(!b1.displayTexture()){
        cout<<"Failed to display the b1 texture"<<endl;
        return false;
    }
    if(!b2.displayTexture()){
        cout<<"b2 texture creation failed"<<endl;
        return false;
    }
    return true;
}

bool setMainDisplay(Component& mainDisplay){
    mainDisplay.setRect((int)CURRENT_SCREEN_WIDTH*0.2,(int)SCREEN_HEIGHT/40,CURRENT_SCREEN_WIDTH-(int)CURRENT_SCREEN_WIDTH*0.2,CURRENT_SCREEN_HEIGHT-(int)SCREEN_HEIGHT/40);

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