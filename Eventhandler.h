#include <vector>
#include <cstring>
#include <map>
vector<FileElement> imgFiles,audioFiles,videoFiles,docFiles;
map<mainIndex,vector<FileElement>*> getFileforIndex = {{img,&imgFiles},{aud,&audioFiles},{vid,&videoFiles},{doc,&docFiles}};
InputComponent *targetInput = NULL,*pathInput =NULL;
vector<InputComponent *> textGroup;
ButtonComponent *targetButton = NULL;
vector<ButtonComponent *> buttonGroup;
map<string,string> shiftClickText={{"1","!"},{"2","@"},{"3","#"},{"4","$"},{"5","%"},{"6","^"},{"7","&"},{"8","*"},{"9","("},{"0",")"},{"`","~"},{"[","{"},{"]","}"},{"\\","|"},{";",":"},{"\'","\""},{",","<"},{".",">"},{"/","?"},{"=","+"},{"-","_"}};
TextComponent *targetCollection = NULL;
vector<TextComponent *> collectionGroup;
vector<CombinedComponent> c;

bool determineTargetInput();
bool determineTargetButton();
bool determineTargetCollection();
int findFileToOpen();

void textInputHandler(SDL_KeyboardEvent e) {
    if(targetInput == NULL){
        return ;
    }
    SDL_Keycode k = e.keysym.sym;
    string setData = "";
    string data = static_cast<string>(SDL_GetKeyName(k));
    if (data.length() == 1) {
        if (isalpha(data[0])) {
            cout<<e.keysym.mod<<endl;
            cout<<SDL_GetModState()<<endl;
            if (e.keysym.mod == KMOD_CAPS) {
                cout<<"We failed to obtain the caps lock"<<endl;
                if (e.keysym.mod == KMOD_LSHIFT || e.keysym.mod == KMOD_RSHIFT) {
                    setData += tolower(data[0]);
                } else {
                    setData += data[0];
                }
            } else {
                if (e.keysym.mod == KMOD_LSHIFT || e.keysym.mod == KMOD_RSHIFT) {
                    setData += data[0];
                } else {
                    setData += tolower(data[0]);
                }
            }
        }else{
            if (e.keysym.mod == KMOD_LSHIFT || e.keysym.mod == KMOD_RSHIFT) {
                cout<<shiftClickText[data]<<endl;
                setData += shiftClickText[data];
            } else {
                setData += data[0];
            }
        }
        targetInput->changeText(setData);
        return;
    }
    if (data == "Space") {
        setData += " ";
        targetInput->changeText(setData);
        return;
    }
    if (data.find("Keypad") != string::npos) {
        cout << "Do we get here" << endl;
        setData += data[data.length() - 1];
        cout << setData << endl;
        targetInput->changeText(setData);
        return;
    }
    if (data == "Backspace") {
        targetInput->changeText();
        return;
    }
}

void mouseClickHandler() {
    targetInput =NULL;
    targetButton =NULL;
    targetCollection = NULL;
    if (determineTargetInput()) {
        targetInput->setActive(true);
        for (vector<InputComponent *>::iterator p = textGroup.begin(); p < textGroup.end(); p++) {
            if (*p == targetInput) {
                continue;
            } else {
                (*p)->setActive(false);
            }
        }
    } else {
        for (vector<InputComponent *>::iterator p = textGroup.begin(); p < textGroup.end(); p++) {
            (*p)->setActive(false);
        }
        if(determineTargetButton()){
            cout<<"Button clicked"<<endl;
            for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
                if (*p == targetButton) {
                    continue;
                } else {
                    (*p)->setActive(false);
                }
            }
            cout<<targetButton->getText()<<endl;
            if(targetButton->getText() == "<<PREV"){
                if(!startp ==0){
                    startp-=1;
                }
            }else if(targetButton->getText()=="NEXT>>"){
                if(mainDefault != none){
                    if(!((startp+1)*np >getFileforIndex[mainDefault]->size())){
                        startp+=1;
                    }
                }else{
                    if(!((startp+1)*np >tp)){
                        startp+=1;
                    }
                }
            }else if(targetButton->getText()=="Search"){
                startp=0;
                string searchText = targetButton->getTarget()->getText();
                mainDefault = none;
                goPath=false;
                searchName = searchText;
            }else if(targetButton->getText()=="GO"){
                startp=0;
                string path = targetButton->getTarget()->getText();
                pathGo=filesystem::path(path);
                mainDefault=none;
                goPath=true;
            }
        }else{
            for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
                (*p)->setActive(false);
            }
            if(determineTargetCollection()){
                cout<<"is there a target collection"<<endl;
                if(targetCollection->getText()=="Images"){
                    mainDefault = img;
                    startp=0;
                }else if(targetCollection->getText()=="Videos"){
                    mainDefault= vid;
                    startp =0;
                }else if(targetCollection->getText()=="Documents"){
                    mainDefault = doc;
                    startp=0;
                }else if(targetCollection->getText()=="Audios"){
                    mainDefault= aud;
                    startp=0;
                }else if(targetCollection->getText()=="Home"){
                    mainDefault = start;
                    startp=0;
                }
            }else{
                cout<<"Hi"<<endl;
                int position = findFileToOpen();
                if(position == 0){return ; }
                if((np*startp+position)>c.size()){
                    return;
                }else{
                    if(mainDefault==start){
                        switch (position){
                            case 1:
                                mainDefault = img;
                                searchName="";
                                goPath =false;
                                pathGo = filesystem::path();
                                break;
                            case 2:
                                mainDefault = aud;
                                searchName ="";
                                goPath = false;
                                pathGo=filesystem::path();
                                break;
                            case 3:
                                mainDefault = vid;
                                searchName = "";
                                goPath= false;
                                pathGo = filesystem::path();
                                break;
                            case 4:
                                mainDefault = doc;
                                searchName ="";
                                goPath= false;
                                pathGo= filesystem::path();
                                break;
                        }
                        return ;
                    }else{
                        cout<<(c[np*start+position-1].getFileElement().getPath().c_str())<<endl;
                        system(("xdg-open \""+c[np*start+position-1].getFileElement().getPath()+"\"").c_str());
                        return;
                    }
                }
            }
        }
    }
    return;
}

void addTargetInput(InputComponent *target) {
    for (vector<InputComponent *>::iterator p = textGroup.begin(); p < textGroup.end(); p++) {
        if (*p == target) {
            return;
        }
    }
    textGroup.push_back(target);
}

void addTargetButton(ButtonComponent *target) {
    for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
        if (*p == target) {
            return;
        }
    }
    buttonGroup.push_back(target);
}

void addTargetInput(InputComponent target) {
    addTargetInput(&target);
    return;
}
void addTargetButton(ButtonComponent target) {
    addTargetButton(&target);
    return;
}

void removeTargetInput(InputComponent *target) {
    for (vector<InputComponent *>::iterator p = textGroup.begin(); p < textGroup.end(); p++) {
        if (*p == target) {
            textGroup.erase(p);
            return;
        }
    }
}

void removeTargetInput(InputComponent target) {
    removeTargetInput(&target);
    return;
}

void removeTargetButton(ButtonComponent *target) {
    for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
        if (*p == target) {
            buttonGroup.erase(p);
            return;
        }
    }
}

void removeTargetCollection(TextComponent *target) {
    for (vector<TextComponent *>::iterator p = collectionGroup.begin(); p < collectionGroup.end(); p++) {
        if (*p == target) {
            collectionGroup.erase(p);
            return;
        }
    }
}

void removeTargetCollection(TextComponent target){
    removeTargetCollection(&target);
}


void removeTargetButton(ButtonComponent target) {
    removeTargetButton(&target);
    return;
}

bool determineTargetInput() {
    if (textGroup.empty()) {
        cout << "Is it empty" << endl;
        return false;
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (vector<InputComponent *>::iterator p = textGroup.begin(); p < textGroup.end(); p++) {
        SDL_Rect a = (*p)->getRect();
        int x1 = a.x, y1 = a.y, x2 = a.x + a.w, y2 = a.y + a.h;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
            targetInput = *p;
            return true;
        }
    }
    return false;
}
bool determineTargetButton() {
    if (buttonGroup.empty()) {
        cout << "Is it empty" << endl;
        return false;
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
        SDL_Rect a = (*p)->getRect();
        int x1 = a.x, y1 = a.y, x2 = a.x + a.w, y2 = a.y + a.h;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
            targetButton = *p;
            return true;
        }
    }
    return false;
}
void setPathInput(InputComponent* i){
    pathInput = i;
}

void addTargetCollection(TextComponent *t){
    for (vector<TextComponent *>::iterator p = collectionGroup.begin(); p < collectionGroup.end(); p++) {
        if (*p == targetCollection) {
            return;
        }
    }
    collectionGroup.push_back(t);
}

void addTargetCollection(TextComponent t){
    addTargetCollection(&t);
}

bool determineTargetCollection() {
    if (collectionGroup.empty()) {
        cout << "Is it empty" << endl;
        return false;
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (vector<TextComponent *>::iterator p = collectionGroup.begin(); p < collectionGroup.end(); p++) {
        SDL_Rect a = (*p)->getRect();
        int x1 = a.x, y1 = a.y, x2 = a.x + a.w, y2 = a.y + a.h;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
            targetCollection = *p;
            return true;
        }
    }
    return false;
}

int findFileToOpen(){
    int x, y;
    SDL_GetMouseState(&x,&y);
    if(x<sidebarx || y<sidebary){
        return 0;
    }
    int width= CURRENT_SCREEN_WIDTH - sidebarx;
    int xn =width/130;
    int height = CURRENT_SCREEN_HEIGHT - sidebary;
    int yn= height/130;
    if(x>sidebarx+xn*130){
        return 0;
    }
    if(y>sidebary+xn*130){
        return 0;
    }
    int xpos=x-sidebarx;
    int ypos= y-sidebary;
    int row = xpos/130+1;
    int column= ypos/130;
    int index= column*xn+row;
    cout<<"index :"<<index<<"row :"<<row<<"column :"<<column<<"xn :"<<xn<<"yn :"<<yn<<endl;
    if(index<np){return index;}else{
        return 0;
    }
}