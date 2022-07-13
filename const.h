//This file is to contain all the constants that the file needs to use.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "array"
#include "map"
#include "filesystem"

using namespace std;
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
TTF_Font *bFont;
enum mainIndex{start,all,img,aud,vid,doc,none};
int startp =0,np=0,tp=0;
mainIndex mainDefault=start;
array<string,2> filePath= {"/media/ronnie/Data/Udemy - QML for Beginners with Qt 5 2020-10"};
array<string,9>imgExt{".tif",".tiff",".bmp",".png",".jpg",".jpeg",".gif",".eps",".raw"};
array<string,6>vidExt{".mp4",".mov",".wmv",".avi",".mpeg-2",".webm"};
array<string,6>audExt={".mp3",".m4a",".flac",".wav",".wma",".aac"};
array<string,8>docsExt = {".doc",".docs",".pdf",".xls",".txt",".odt",".ppt",".pptx"};
map<mainIndex,string> dataPicture ={{img,"/media/ronnie/Files/CPlusPlus/Home/images/images.webp"},{aud,"/media/ronnie/Files/CPlusPlus/Home/images/audiofile.png"},{vid,"/media/ronnie/Files/CPlusPlus/Home/images/videoFile.jpeg"},{doc,"/media/ronnie/Files/CPlusPlus/Home/images/documents.png"}};
string searchName="";
filesystem::path pathGo;
bool goPath =false;
