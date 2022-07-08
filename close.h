//We are going to use  this file to close all the necessary global pointers .
void close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return;
}
