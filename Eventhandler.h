#include <vector>
#include <cstring>
#include <map>

InputComponent *targetInput = NULL;
vector<InputComponent *> textGroup;
ButtonComponent *targetButton = NULL;
vector<ButtonComponent *> buttonGroup;
map<string,string> shiftClickText={{"1","!"},{"2","@"},{"3","#"},{"4","$"},{"5","%"},{"6","^"},{"7","&"},{"8","*"},{"9","("},{"0",")"},{"`","~"},{"[","{"},{"]","}"},{"\\","|"},{";",":"},{"\'","\""},{",","<"},{".",">"},{"/","?"}};


bool determineTargetInput();
bool determineTargetButton();

void textInputHandler(SDL_KeyboardEvent e) {
    if(targetInput == NULL){
        return ;
    }
    SDL_Keycode k = e.keysym.sym;
    string setData = "";
    string data = static_cast<string>(SDL_GetKeyName(k));
    cout << (e.keysym.mod == KMOD_LSHIFT) << endl;
    if (data.length() == 1) {
        if (isalpha(data[0])) {
            if (e.keysym.mod == KMOD_CAPS) {
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
            targetButton->setActive(true);
            for (vector<ButtonComponent *>::iterator p = buttonGroup.begin(); p < buttonGroup.end(); p++) {
                if (*p == targetButton) {
                    continue;
                } else {
                    (*p)->setActive(false);
                }
            }
        }else{

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