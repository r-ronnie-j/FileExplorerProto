#include <SDL2/SDL_render.h>
#include "iostream"
#include "string"
#include "SDL2/SDL_ttf.h"
#include <chrono>

using namespace std;

class Component {
public:
    Component() {
        texture = NULL;
        surf = NULL;
        r = {0, 0, 0, 0};
    }

    Component(int x, int y, int w, int h) {
        texture = NULL;
        surf = NULL;
        r = {x, y, w, h};
    }

    ~Component() {
        free();
    }

    void free() {
        SDL_DestroyTexture(texture);
        texture = NULL;
        SDL_FreeSurface(surf);
        surf = NULL;
    }

    //Set the rect that the given texture will occupy in the given window
    void setRect(int x, int y, int w, int h) {
        r = {x, y, w, h};
        return;
    }

    SDL_Texture *getTexture() { return this->texture; }

    bool drawBorder(string b, int red, int green, int blue, int alpha, int thickness) {
        SDL_Rect rec = {0, 0, 0, 0};
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        for (int i = 0; i < b.length(); i++) {
            char c = tolower(b[i]);
            if (c == 'u') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = r.w;
                rec.h = thickness;
            } else if (c == 'l') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else if (c == 'd') {
                rec.x = r.x;
                rec.y = r.y + r.h;
                rec.w = r.w;
                rec.h = thickness;
            } else if (c == 'r') {
                rec.x = r.x + r.w;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else {
                continue;
            }

            if (SDL_RenderFillRect(renderer, &rec) < 0) {
                cout << "Failed to draw a line" << endl;
                cout << SDL_GetError() << endl;
                return false;
            };
        }
        return true;
    }

    bool drawBorder(string b) {
        return drawBorder(b, 0, 0, 0, 255, 2);
    }

    //creates a blank Texture
    bool createTexture(int r, int g, int b, int a) {
        free();
        surf = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, PIXEL_FORMAT);
        if (!surf) {
            cout << "Failed to create the surface" << endl;
            cout << SDL_GetError() << endl;
        }
        if (SDL_FillRect(surf, NULL, SDL_MapRGBA(surf->format, r, g, b, a)) < 0) {
            cout << "Failed to create the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        };
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            cout << "Failed to create the texture" << endl;
            cout << SDL_GetError();
            return false;
        }
        return true;
    }

    bool createTextTexture(string data, SDL_Color color) {
        free();
        surf = TTF_RenderText_Solid(font, data.c_str(), color);
        if (!surf) {
            cout << "We failed to create the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            cout << "Failed to create texture with a string" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        return true;
    }

    bool createTextTexture(string data) {
        SDL_Color color = {0, 0, 0};
        return createTextTexture(data, color);
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

    bool displayTexture(SDL_Rect d) {
        return displayTexture(&d);
    }

    bool displayTexture() {
        if (r.x == 0 && r.y == 0 && r.w == 0 && r.h == 0) {
            cout << "In class component the texture rectangle is(0,0,0,0)" << endl << "The display might not be visible"
                 << endl;
        }
        return displayTexture(&r);
    }

    int getWidth() {
        return r.w;
    }

    int getHeight() { return r.h; }

    int getX() { return r.x; }

    int getY() { return r.y; }

private:
    SDL_Texture *texture;
    SDL_Rect r;
    SDL_Surface *surf;
};

class InputComponent : public Component {
private:
    SDL_Texture *texture;
    SDL_Surface *surf;
    SDL_Rect r;
    string text;
    bool active;
public:
    InputComponent() {
        texture = NULL;
        surf = NULL;
        r = {0, 0, 0, 0};
        text = "";
        active = false;
    }

    InputComponent(int x, int y, int w, int h) {
        texture = NULL;
        surf = NULL;
        r = {x, y, w, h};
        text = "";
        active = false;
    }

    ~InputComponent() {
        free();
    }

    bool createTextTexture(SDL_Color color) {
        free();
        string toggle = "";
        if (active) {
            uint64_t ms = duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
            if (ms % 1000 > 500) {
                toggle = "l";
            } else {
                toggle = "";
            }
        }
        string actualDisplay = "   " + text + toggle;
        surf = TTF_RenderText_Solid(font, actualDisplay.c_str(), color);
        if (!surf) {
            cout << "Failed to create the surface in Input Component" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            cout << "Failed to create the texture" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        return true;
    }

    bool createTextTexture() {
        SDL_Color color = {0, 0, 0};
        return createTextTexture(color);
    }

    SDL_Rect getRect() {
        return r;
    }

    void changeText(string ch) {
        text = text + ch;
        return;
    }

    void changeText() {
        text = text.substr(0, text.length() - 1);
    }

    void setActive(bool state) {
        active = state;
    }

    void setRect(int x, int y, int w, int h) {
        r = {x, y, w, h};
        return;
    }

    bool displayTexture(SDL_Rect *d) {
        SDL_Rect srcRect = {d->x, 3 * d->y / 2, surf->w, surf->h};
        if (!SDL_RenderCopy(renderer, texture, NULL, &srcRect) < 0) {
            cout << "Failed to render copy" << endl;
            cout << SDL_GetError();
            return false;
        }
        return true;
    }

    bool displayTexture(SDL_Rect d) {
        return displayTexture(&d);
    }

    bool displayTexture() {
        if (r.x == 0 && r.y == 0 && r.w == 0 && r.h == 0) {
            cout << "In class component the texture rectangle is(0,0,0,0)" << endl << "The display might not be visible"
                 << endl;
        }
        return displayTexture(&r);
    }

    bool drawBorder(string b, int red, int green, int blue, int alpha, int thickness) {
        SDL_Rect rec = {0, 0, 0, 0};
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        for (int i = 0; i < b.length(); i++) {
            char c = tolower(b[i]);
            if (c == 'u') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = r.w;
                rec.h = thickness;
            } else if (c == 'l') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else if (c == 'd') {
                rec.x = r.x;
                rec.y = r.y + r.h;
                rec.w = r.w + thickness;
                rec.h = thickness;
            } else if (c == 'r') {
                rec.x = r.x + r.w;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else {
                continue;
            }

            if (SDL_RenderFillRect(renderer, &rec) < 0) {
                cout << "Failed to draw a line" << endl;
                cout << SDL_GetError() << endl;
                return false;
            };
        }
        return true;
    }

    bool drawBorder(string b) {
        if (active) {
            return drawBorder(b, 0, 205, 140, 255, 2);
        } else {
            return drawBorder(b, 0, 0, 0, 255, 2);
        }
    }

    void free() {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surf);
    }

    int getWidth() {
        return r.w;
    }

    int getHeight() { return r.h; }

    string getText() {
        return text;
    }
};

class ButtonComponent : public Component {
private:
    SDL_Texture *texture;
    SDL_Rect r;
    SDL_Surface *surf;
    string text;
    bool active;
    InputComponent *target;
public:
    ButtonComponent() {
        texture = NULL;
        surf = NULL;
        r = {0, 0, 0, SCREEN_HEIGHT / 40 - 6};
        text = " WOOW ";
        active = false;
        target = NULL;
    }

    ButtonComponent(int x, int y, int w, int h) {
        texture = NULL;
        surf = NULL;
        r = {x, y, 0, SCREEN_HEIGHT / 40 - 6};
        text = " WOOW ";
        active = false;
        target = NULL;
    }

    ButtonComponent(int x, int y) {
        ButtonComponent(x, y, 0, 0);
    }

    ~ButtonComponent() {
        free();
    }

    InputComponent* getTarget(){
        return target;
    }
    void setText(string data) {
        text = data;
    }

    void free() {
        SDL_DestroyTexture(texture);
        texture = NULL;
        SDL_FreeSurface(surf);
        surf = NULL;
    }
    string getText(){
        return text;
    }
    void setRect(int x, int y, int w, int h) {
        r.x = x;
        r.y = y;
        return;
    }

    void setRect(int x, int y) {
        r.x = x;
        r.y = y + 2;
        return;
    }

    SDL_Rect getRect() {
        return r;
    }

    bool drawBorder(string b, int red, int green, int blue, int alpha, int thickness) {
        SDL_Rect rec = {0, 0, 0, 0};
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        for (int i = 0; i < b.length(); i++) {
            char c = tolower(b[i]);
            if (c == 'u') {
                rec.x = r.x - thickness;
                rec.y = r.y - thickness;
                rec.w = r.w + 2 * thickness;
                rec.h = thickness;
            } else if (c == 'l') {
                rec.x = r.x - thickness;
                rec.y = r.y - thickness;
                rec.w = thickness;
                rec.h = r.h + 2 * thickness;
            } else if (c == 'd') {
                rec.x = r.x;
                rec.y = r.y + r.h;
                rec.w = r.w + 2;
                rec.h = thickness;
            } else if (c == 'r') {
                rec.x = r.x + r.w;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else {
                continue;
            }

            if (SDL_RenderFillRect(renderer, &rec) < 0) {
                cout << "Failed to draw a line" << endl;
                cout << SDL_GetError() << endl;
                return false;
            };
        }
        return true;
    }

    bool drawBorder(string b) {
        return drawBorder(b, 0, 0, 0, 255, 2);
    }

    bool createButtonTexture() {
        free();
        SDL_Color color = {66, 133, 244};
        SDL_Surface *s = TTF_RenderText_Solid(font, ("  " + text + "  ").c_str(), color);
        if (!s) {
            cout << "We failed to generate the text surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        r.w = s->w;
        SDL_Surface *bs = SDL_CreateRGBSurfaceWithFormat(0, s->w, r.h, 32, PIXEL_FORMAT);
        if (!bs) {
            cout << "We failed to generate the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        uint32_t colour = SDL_MapRGBA(bs->format, 238, 241, 212, 255);
        if (SDL_FillRect(bs, NULL, colour) < 0) {
            cout << "We failed to generate a color to the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        };
        SDL_BlitSurface(s, NULL, bs, NULL);
        surf = bs;
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(s);
        return true;
    }

    bool displayTexture(SDL_Rect *d) {
        if (!SDL_RenderCopy(renderer, texture, NULL, d) < 0) {
            cout << "Failed to render copy" << endl;
            cout << SDL_GetError();
            return false;
        }
        return true;
    }

    bool displayTexture(SDL_Rect d) {
        return displayTexture(&d);
    }

    bool displayTexture() {
        if (r.x == 0 && r.y == 0 && r.w == 0 && r.h == 0) {
            cout << "In class component the texture rectangle is(0,0,0,0)" << endl << "The display might not be visible"
                 << endl;
        }
        return displayTexture(&r);
    }

    void setTarget(InputComponent *c) {
        target = c;
    }

    void setActive(bool status) {
        active = status;
    }

    int getWidth() {
        return r.w;
    }

    int getHeight() { return r.h; }
};

class TextComponent {
private:
    string text;
    SDL_Texture *texture;
    SDL_Surface *surf;
    SDL_Rect r;
public:
    TextComponent() {
        text = "";
        texture = NULL;
        surf = NULL;
        r = {0, 0, 0, 0};
    }

    ~TextComponent() {
        free();
    }

    void setText(string s) {
        text = s;
    }

    string getText(){
        return text;
    }

    void free() {
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(texture);
    }

    void setRect(int x, int y) {
        r.x = x;
        r.y = y;
        return;
    }

    void setRect(int x, int y, int w, int h) {
        setRect(x, y);
    }

    bool drawBorder(string b, int red, int green, int blue, int alpha, int thickness) {
        SDL_Rect rec = {0, 0, 0, 0};
        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        for (int i = 0; i < b.length(); i++) {
            char c = tolower(b[i]);
            if (c == 'u') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = r.w;
                rec.h = thickness;
            } else if (c == 'l') {
                rec.x = r.x;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else if (c == 'd') {
                rec.x = r.x;
                rec.y = r.y + r.h;
                rec.w = r.w;
                rec.h = thickness;
            } else if (c == 'r') {
                rec.x = r.x + r.w;
                rec.y = r.y;
                rec.w = thickness;
                rec.h = r.h;
            } else {
                continue;
            }

            if (SDL_RenderFillRect(renderer, &rec) < 0) {
                cout << "Failed to draw a line" << endl;
                cout << SDL_GetError() << endl;
                return false;
            };
        }
        return true;
    }

    bool drawBorder(string b) {
        return drawBorder(b, 0, 0, 0, 255, 2);
    }

    bool generateTexture(string s) {
        SDL_Color color = {0, 0, 0};
        SDL_Surface *su = TTF_RenderText_Solid(bFont, text.c_str(), color);
        if (!su) {
            cout << "We failed to generate the surface at text" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        r.w = su->w;
        r.h = su->h;
        surf= su;
        texture = SDL_CreateTextureFromSurface(renderer, su);
        if (!texture) {
            cout << "We failed to generate the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        return false;
    }

    void generateTexture() {
        generateTexture(text);
    }

    bool displayTexture(){
        SDL_RenderCopy(renderer,texture,NULL,&r);
    }
    SDL_Rect getRect(){
        return r;
    }
    int getWidth() {
        return r.w;
    }

    int getHeight() {
        return r.h;
    }
    int getY(){
        return r.y;
    }
    int getX(){
        return r.x;
    }

    SDL_Surface *getSurf() {
        return surf;
    }
};

class ImageComponent {
private:
    string path;
    SDL_Texture *texture;
    SDL_Surface *surf;
    SDL_Rect r;
public:
    ImageComponent() {
        texture = NULL;
        surf = NULL;
        path = "";
        r = {0, 0, 0, 0};
    }

    ~ImageComponent() {
        free();
    };

    void setPath(string s) {
        path = s;
    }

    void setRect(int x, int y, int w, int h) {
        r = {x, y, w, h};
    }

    void free() {
        SDL_FreeSurface(surf);
        surf=NULL;
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    string getPath() {
        return path;
    }

    bool generateTexture() {
        free();
        surf = IMG_Load(path.c_str());
        if (!surf) {
            cout << "We failed to generate the surface at image" << endl;
            cout << SDL_GetError();
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (!texture) {
            cout << "Failed to generate the image surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        return true;
    }

    SDL_Surface *getSurf() {
        return surf;
    }
};

class CombinedComponent {
private:
    SDL_Surface *surf;
    SDL_Texture *texture;
    SDL_Rect r;
    string path;
    string name;
    FileElement f;
public:
    CombinedComponent() {
        surf = NULL;
        texture = NULL;
        r = {0, 0, 0, 0};
        path = "";
        name = "";
    }

    ~CombinedComponent() {
        free();
    }

    void free() {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surf);
    }

    void setPath(string p) {
        path = p;
    }

    string getPath() { return path; }

    void setName(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void setRect(int x, int y, int w, int h) {
        r = {x, y, w, h};
    }

    bool generateTexture(string p, string n) {
        int acceptedL = (int)r.w/10;
        if(acceptedL<n.length()){
            n = n.substr(0,acceptedL-3);
            n=n+"...";
        }
        SDL_Color colour={0,0,0};
        SDL_Surface* t = TTF_RenderText_Solid(font,n.c_str(),colour);
        ImageComponent i;
        i.setPath(p);
        i.generateTexture();
        surf = SDL_CreateRGBSurfaceWithFormat(0, r.w, r.h, 32, PIXEL_FORMAT);
        uint32_t color = SDL_MapRGBA(surf->format,255,255,255,0);
        SDL_FillRect(surf,NULL,color);
        SDL_Rect r1 = {0, 0, r.w, r.h - t->h};
        if (SDL_BlitScaled(i.getSurf(), NULL, surf, &r1) < 0) {
            cout << "We failed to blit the surface" << endl;
            cout << SDL_GetError() << endl;
            return false;
        }
        r1 = {(r.w-t->w)/2, r.h-t->h, r.w, t->h};
        if(SDL_BlitSurface(t,NULL,surf,&r1)<0){
            cout<<"Failed to generate the surface combinedd"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer,surf);
        if(!texture){
            cout<<"Failed to create the texture"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        }
        return true;
    }
    bool generateTexture(){
        return generateTexture(path,name);
    }
    bool displayTexture(){
        if(SDL_RenderCopy(renderer,texture,NULL,&r)<0){
            cout<<"We failed to generate the combined surface"<<endl;
            cout<<SDL_GetError()<<endl;
            return false;
        }
        return true;
    }
    void addFileElement(FileElement f){
        this->f= f;
    }
    FileElement getFileElement(){
        return this->f;
    }
};


