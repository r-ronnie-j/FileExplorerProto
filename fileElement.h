#include "string"

using namespace std;

class FileElement{
private:
    string name;
    string path;
    string type;
    mainIndex m;
public:
    FileElement(){
        name="";
        path="";
        type="";
    }
    FileElement(string n,string p,string t){
        name=n;
        path=p;
        type=t;
        if(t =="img"){
            m= img;
        }else if(t == "aud"){
            m =aud;
        }else if(t == "vid"){
            m= vid;
        }else{
            t = doc;
        }
    }
    void setName(string n){
        name =n;
    }
    string getName(){
        return name;
    }
    string getPath(){
        return path;
    }
    void setPath(string p){
        path =path;
    }
    mainIndex getIndex(){
        return m;
    }
    void setIndex(mainIndex ma1){
        m = ma1;
    }
};



