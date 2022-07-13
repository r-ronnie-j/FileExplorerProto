#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "const.h"
#include "fileElement.h"
#include "init.h"
#include "Components.h"
#include "close.h"
#include "Eventhandler.h"
#include "generator.h"

using namespace std;

bool setBackground(int r, int g, int b, int a);

bool setTopBar(Component &);

bool setSideBar(Component &);

bool setMainDisplay(Component &);

bool setTopBarInterior(InputComponent &, InputComponent &, ButtonComponent &, ButtonComponent &);

bool setSidebarInterior(ButtonComponent& b3,ButtonComponent& b4,int,int,TextComponent&,TextComponent&,TextComponent&,TextComponent&,TextComponent&);

int main(int argc, char *argv[]) {
    if (!init()) {
        return -1;
    }
    SDL_SetWindowMinimumSize(window,900,900);
    bool game = true;
    SDL_Event event;
    Component topBar, sideBar, mainDisplay;
    InputComponent i1, i2;
    ButtonComponent b1, b2,b3,b4;
    TextComponent t0,t1,t2,t3,t4;
    t0.setText("Home");
    t1.setText("Images");
    t2.setText("Videos");
    t3.setText("Audios");
    t4.setText("Documents");
    b1.setText("Search");
    b1.setTarget(&i1);
    b3.setText("<<PREV");
    b4.setText("NEXT>>");
    b2.setTarget(&i2);
    b2.setText("GO");
    addTargetInput(&i1);
    addTargetInput(&i2);
    setPathInput(&i2);
    addTargetButton(&b1);
    addTargetButton(&b2);
    addTargetButton(&b3);
    addTargetButton(&b4);
    addTargetCollection(&t0);
    addTargetCollection(&t1);
    addTargetCollection(&t2);
    addTargetCollection(&t3);
    addTargetCollection(&t4);
    findFiles(img,imgFiles);
    cout<<"img loaded"<<endl;
    findFiles(vid,videoFiles);
    cout<<"Vid loaded"<<endl;
    findFiles(aud,audioFiles);
    cout<<"audio loaded"<<endl;
    findFiles(doc,docFiles);
    cout<<"docs loaded"<<endl;
    vector<CombinedComponent> c;
    while (game) {
        if (!setBackground(255, 255, 255, 255)) {
            return -1;
        }
        if (!setTopBar(topBar)) {
            return -1;
        }
        if (!setSideBar(sideBar)) {
            return -1;
        }
        if (!setMainDisplay(mainDisplay)) {
            return -1;
        }
        topBar.drawBorder("d");
        sideBar.drawBorder("r");
        mainDisplay.drawBorder("ul");
        if (!setTopBarInterior(i1, i2, b1, b2)) {
            return -1;
        }
        setSidebarInterior(b3,b4,sideBar.getWidth(),sideBar.getY(),t0,t1,t2,t3,t4);
        if(mainDefault!=none) {
            displayInMain(mainDefault, c, sideBar.getWidth(), sideBar.getY());
        }else{
            if(!goPath){
                tp=c.size();
                displayInMain(searchName,c,sideBar.getWidth(),sideBar.getY());
            }else{
                tp=c.size();
                displayInMain(pathGo,c,sideBar.getWidth(),sideBar.getY());
                cout<<"Display complete";
                cout<<c.size()<<endl;
            }
        }
        int m = ((int)(CURRENT_SCREEN_WIDTH-sideBar.getWidth())/130)*(int)((CURRENT_SCREEN_HEIGHT-sideBar.getY())/130);
        np=m;
        if(m*(startp+1)>c.size()){
            m=c.size();
        }else{
            m=(startp+1)*np;
        }
        for(int i=startp*np;i<m;i++){
            cout<<"generated"<<i<<endl;
            c[i].generateTexture();
            c[i].displayTexture();
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                textInputHandler(event.key);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
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

bool setSideBar(Component &sideBar) {

    sideBar.setRect(0, (int) SCREEN_HEIGHT / 40, (int) CURRENT_SCREEN_WIDTH * 0.2,
                    CURRENT_SCREEN_HEIGHT - (int) SCREEN_HEIGHT / 40);
    if (!sideBar.createTexture(237, 237, 237, 255)) {
        cout << "Failed to create sideBar" << endl;
        return false;
    };
    if (!sideBar.displayTexture()) {
        cout << "Failed to display the sideBar" << endl;
        return false;
    };
    sideBar.drawBorder("d");
    return true;
}

bool setTopBar(Component &topBar) {
    topBar.setRect(0, 0, CURRENT_SCREEN_WIDTH, (int) SCREEN_HEIGHT / 40);
    if (!topBar.createTexture(240, 230, 200, 255)) {
        cout << "Failed to create topbar" << endl;
        return false;
    };
    if (!topBar.displayTexture()) {
        cout << "Failed to display the topBar" << endl;
        return false;
    };
    return true;
}

bool setTopBarInterior(InputComponent &i1, InputComponent &i2, ButtonComponent &b1, ButtonComponent &b2) {
    if (!b1.createButtonTexture()) {
        cout << "Button texture 1" << endl;
        return false;
    };
    if (!b2.createButtonTexture()) {
        cout << "Button texture 2" << endl;
        return false;
    };
    i1.setRect(1, 1, (CURRENT_SCREEN_WIDTH / 2 - b1.getWidth()) * 0.95, SCREEN_HEIGHT / 40 - 4);
    b1.setRect(i1.getWidth(), 1);
    i2.setRect(CURRENT_SCREEN_WIDTH / 2, 1, (CURRENT_SCREEN_WIDTH / 2 - b2.getWidth()) * 0.95, SCREEN_HEIGHT / 40 - 4);
    b2.setRect(CURRENT_SCREEN_WIDTH / 2 + i2.getWidth(), 1);
    if (!i1.createTextTexture()) {
        cout << "i1 texture building failed" << endl;
        return false;
    }
    if (!i2.createTextTexture()) {
        cout << "i2 texture creation failed" << endl;
        return false;
    }
    i1.drawBorder("udlr");
    i2.drawBorder("udlr");
    b1.drawBorder("udlr");
    b2.drawBorder("udlr");
    if (!i1.displayTexture()) {
        cout << "Display of i1 texture failed" << endl;
        return false;
    }
    if (!i2.displayTexture()) {
        cout << "Display of texture i2 failed" << endl;
        return false;
    }
    if (!b1.displayTexture()) {
        cout << "Failed to display the b1 texture" << endl;
        return false;
    }
    if (!b2.displayTexture()) {
        cout << "b2 texture creation failed" << endl;
        return false;
    }
    return true;
}

bool setMainDisplay(Component &mainDisplay) {
    mainDisplay.setRect((int) CURRENT_SCREEN_WIDTH * 0.2, (int) SCREEN_HEIGHT / 40,
                        CURRENT_SCREEN_WIDTH - (int) CURRENT_SCREEN_WIDTH * 0.2,
                        CURRENT_SCREEN_HEIGHT - (int) SCREEN_HEIGHT / 40);

    if (!mainDisplay.createTexture(251, 250, 200, 255)) {
        cout << "Failed to create mainDisplay" << endl;
        return false;
    };
    if (!mainDisplay.displayTexture()) {
        cout << "Failed to display the mainDisplay" << endl;
        return false;
    };
    return true;
}

bool setSidebarInterior(ButtonComponent& b3,ButtonComponent& b4,int w,int y,TextComponent& t0,TextComponent& t1,TextComponent& t2,TextComponent& t3,TextComponent& t4){
    if(!b3.createButtonTexture()){
        cout<<"Failed to create the texture of lower button"<<endl;
        return false;
    }
    if(!b4.createButtonTexture()){
        cout<<"Failed to create the texture of lower button 2"<<endl;
        return false;
    }
    b3.setRect(5,CURRENT_SCREEN_HEIGHT - 30);
    b4.setRect(w- b4.getWidth()-5,CURRENT_SCREEN_HEIGHT - 30);
    b3.drawBorder("uldr");
    b4.drawBorder("uldr");
    t0.generateTexture();
    t1.generateTexture();
    t2.generateTexture();
    t3.generateTexture();
    t4.generateTexture();
    t0.setRect(10,y+5,t0.getWidth(),t0.getHeight());
    t1.setRect(10,t0.getY()+t0.getHeight()+5,t1.getWidth(),t1.getHeight());
    t2.setRect(10,t1.getY()+t1.getHeight()+5,t2.getWidth(),t2.getHeight());
    t3.setRect(10,t2.getY()+t2.getHeight()+5,t3.getWidth(),t3.getHeight());
    t4.setRect(10,t3.getY()+t3.getHeight()+5,t4.getWidth(),t4.getHeight());
    b3.displayTexture();
    b4.displayTexture();
    t0.displayTexture();
    t1.displayTexture();
    t2.displayTexture();
    t3.displayTexture();
    t4.displayTexture();
    return true;
}
