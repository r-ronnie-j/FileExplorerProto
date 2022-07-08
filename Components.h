#include <SDL2/SDL_render.h>
#include "iostream"
#include "string"
#include "SDL2/SDL_ttf.h"

using namespace std;

class Component {
public:
    Component() {
        texture = NULL;
        surf=NULL;
        r = {0, 0, 0, 0};
    }

    Component(int x, int y, int w, int h) {
        texture = NULL;
        surf=NULL;
        r = {x, y, w, h};
    }

    ~Component() {
        free();
    }

    void free() {
        SDL_DestroyTexture(texture);
        texture =NULL;
        SDL_FreeSurface(surf);
        surf= NULL;
    }

    //Set the rect that the given texture will occupy in the given window
    void setRect(int x, int y, int w, int h) {
        r = {x, y, w, h};
        cout<<x<<y<<w<<h<<endl;
        return;
    }

    SDL_Texture *getTexture() { return this->texture; }

    bool drawBorder(string b,int red,int green,int blue,int alpha,int thickness){
        SDL_Rect rec={0,0,0,0};
        SDL_SetRenderDrawColor(renderer,red,green,blue,alpha);
        for(int i=0;i<b.length();i++){
            char c=tolower(b[i]);
            if(c=='u'){
                rec.x=r.x;
                rec.y=r.y;
                rec.w=r.w;
                rec.h=thickness;
            }
            else if(c=='l'){
                rec.x=r.x;
                rec.y=r.y;
                rec.w=thickness;
                rec.h=r.h;
            }
            else if(c=='d'){
                rec.x=r.x;
                rec.y=r.y+r.h;
                rec.w=r.w;
                rec.h=thickness;
            }
            else if(c=='r'){
                rec.x=r.x+r.w;
                rec.y=r.y;
                rec.w=thickness;
                rec.h=r.h;
            }
            else{
                continue;
            }

            if(SDL_RenderFillRect(renderer,&rec)<0){
                cout<<"Failed to draw a line"<<endl;
                cout<<SDL_GetError()<<endl;
                return false;
            };
        }
        return true;
    }
    bool drawBorder(string b){
        return drawBorder(b,0,0,0,255,2);
    }

    //creates a blank Texture
    bool createTexture(int r, int g, int b, int a) {
        free();
        surf = SDL_CreateRGBSurfaceWithFormat(0,SCREEN_WIDTH,SCREEN_HEIGHT,32,PIXEL_FORMAT);
        if(!surf){
            cout<<"Failed to create the surface"<<endl;
            cout<<SDL_GetError()<<endl;
        }
        if(SDL_FillRect(surf, NULL,SDL_MapRGBA(surf->format,r,g,b,a))<0){
            cout<<"Failed to create the surface"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        };
        texture = SDL_CreateTextureFromSurface(renderer,surf);
        if(!texture){
            cout<<"Failed to create the texture"<<endl;
            cout<<SDL_GetError();
            return false;
        }
        return true;
    }
    bool createTextTexture(string data,SDL_Color color){
        free();
        surf = TTF_RenderText_Solid(font,data.c_str(),color);
        if(!surf){
            cout<<"We failed to create the surface"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer,surf);
        if(!texture){
            cout<<"Failed to create texture with a string"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        }
        return true;
    }
    bool createTextTexture(string data){
        SDL_Color color={0,0,0};
        return createTextTexture(data,color);
    }

    //Display the texture with a given render rectangle
    bool displayTexture(SDL_Rect *d) {
        if (!SDL_RenderCopy(renderer, texture, NULL, d) < 0) {
            cout << "Failed to render copy" << endl;
            cout << SDL_GetError();
            return false;
        }
        return true;
    }
    bool displayTexture(SDL_Rect d){
        return displayTexture(&d);
    }
    bool displayTexture(){
        if(r.x==0 && r.y==0 && r.w ==0 && r.h ==0){
            cout<<"In class component the texture rectangle is(0,0,0,0)"<<endl<<"The display might not be visible"<<endl;
        }
        return displayTexture(&r);
    }

private:
    SDL_Texture *texture;
    SDL_Rect r;
    SDL_Surface* surf;
};