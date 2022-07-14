#include "filesystem"

//This function is the main function responsible for generation of the main display
bool findGrid(vector<CombinedComponent>&,int,int,int);

void findFiles(mainIndex mainI,vector<FileElement>&f){
    switch (mainI){
        case img :
            f.clear();
            for(int i=0;i<filePath.size();i++){
                string pathName = filePath.at(i);
                filesystem::path path(pathName);
                std::error_code ec;
                filesystem::recursive_directory_iterator iter(path,filesystem::directory_options::skip_permission_denied,ec);
                for(iter;iter!=std::filesystem::recursive_directory_iterator();iter++){
                    if(ec){
                        cout<<"Some error"<<endl;
                        continue;
                    }
                    for(int k=0;k<imgExt.size();k++){
                        if(imgExt.at(k) == iter->path().extension()){
                            FileElement f1(iter->path().filename(),iter->path().string(),"img");
                            f.push_back(f1);
                            break ;
                        }
                    }
                }
            }
            return;
        case vid:
            f.clear();
            for(int i=0;i<filePath.size();i++){
                string pathName = filePath.at(i);
                filesystem::path path(pathName);
                std::error_code ec;
                filesystem::recursive_directory_iterator iter(path,filesystem::directory_options::skip_permission_denied,ec);
                for(filesystem::directory_entry ix:iter){
                    if(ec){
                        cout<<"Some error"<<endl;
                        continue;
                    }
                    for(int k=0;k<vidExt.size();k++){
                        if(vidExt.at(k) == ix.path().extension()){
                            FileElement f1(ix.path().filename(),ix.path().string(),"vid");
                            f.push_back(f1);
                            break ;
                        }
                    }
                }
            }
            return;
        case doc :
            f.clear();
            for(int i=0;i<filePath.size();i++){
                string pathName = filePath.at(i);
                filesystem::path path(pathName);
                error_code ec;
                filesystem::recursive_directory_iterator iter(path,filesystem::directory_options::skip_permission_denied,ec);
                for(filesystem::directory_entry ix:iter){
                    if(ec){
                        cout<<"Some error"<<endl;
                        continue;
                    }
                    for(int k=0;k<docsExt.size();k++){
                        if(docsExt.at(k) == ix.path().extension()){
                            FileElement f1(ix.path().filename(),ix.path().string(),"doc");
                            f.push_back(f1);
                            break ;
                        }
                    }
                }
            }
            return;
        case aud:
            f.clear();
            for(int i=0;i<filePath.size();i++){
                string pathName = filePath.at(i);
                filesystem::path path(pathName);
                std::error_code ec;
                filesystem::recursive_directory_iterator iter(path,filesystem::directory_options::skip_permission_denied,ec);
                for(filesystem::directory_entry ix:iter){
                    if(ec){
                        cout<<"Some error"<<endl;
                        continue;
                    }
                    for(int k=0;k<audExt.size();k++){
                        if(audExt.at(k) == ix.path().extension()){
                            FileElement f1(ix.path().filename(),ix.path().string(),"aud");
                            f.push_back(f1);
                            break ;
                        }
                    }
                }
            }
            return;
        default:
            return;
    }

}

bool displayInMain(string s,vector<CombinedComponent>& c,int x,int y){
    c.clear();
    vector<FileElement> f;
    for(vector<FileElement>::iterator z = imgFiles.begin();z<imgFiles.end();z++){
        cout<<"audio"<<endl;
        if(z->getName().find(s)>=0){
            z->setIndex(img);
            f.push_back(*z);
        }
    }
    for(vector<FileElement>::iterator z = videoFiles.begin();z<videoFiles.end();z++){
        cout<<"video"<<endl;
        cout<<z->getName().find(s)<<endl;
        if(z->getName().find(s)!=string::npos){
            z->setIndex(vid);
            f.push_back(*z);
        }
    }
    for(vector<FileElement>::iterator z = audioFiles.begin();z<audioFiles.end();z++){
        cout<<"audio"<<endl;

        if(z->getName().find(s)!=string::npos){
            z->setIndex(aud);
            f.push_back(*z);
        }
    }
    for(vector<FileElement>::iterator z = docFiles.begin();z<docFiles.end();z++){
        cout<<"docs"<<endl;
        if(z->getName().find(s)!=string::npos){
            z->setIndex(doc);
            f.push_back(*z);
        }
    }
    findGrid(c,f.size(),x,y);
    for(int i=0;i<f.size();i++){
        c[i].setName(f.at(i).getName());
        c[i].setPath(dataPicture[f.at(i).getIndex()]);
        //c[i].addFileElement(f[i]);
    }
    return true;
}
bool displayInMain(mainIndex m,vector<CombinedComponent>&c,int x,int y){
    c.clear();
    vector<FileElement> f;
    switch (m) {
        case start:
            findGrid(c,4,x,y);
            c[0].setName("images");
            c[0].setPath("/media/ronnie/Files/CPlusPlus/Home/images/pics.png");
            c[1].setName("audio");
            c[1].setPath("/media/ronnie/Files/CPlusPlus/Home/images/audio.png");
            c[2].setName("video");
            c[2].setPath("/media/ronnie/Files/CPlusPlus/Home/images/video.png");
            c[3].setName("docs");
            c[3].setPath("/media/ronnie/Files/CPlusPlus/Home/images/docs.png");
            return true;
        case img:
            findGrid(c,imgFiles.size(),x,y);
            for(int i=0;i<imgFiles.size();i++){
                c[i].setPath(dataPicture[m]);
                c[i].setName(imgFiles.at(i).getName());
                c[i].addFileElement(imgFiles[i]);
            }
            return true;
        case aud:
            findGrid(c,audioFiles.size(),x,y);
            for(int i=0;i<audioFiles.size();i++){
                c[i].setPath(dataPicture[m]);
                c[i].setName(audioFiles.at(i).getName());
                c[i].addFileElement(audioFiles[i]);
            }
            return true;
        case vid:
            findGrid(c,videoFiles.size(),x,y);
            for(int i=0;i<videoFiles.size();i++){
                c[i].setPath(dataPicture[m]);
                c[i].setName(videoFiles.at(i).getName());
                c[i].addFileElement(videoFiles[i]);
            }
            return true;
        case doc:
            findGrid(c,docFiles.size(),x,y);
            for(int i=0;i<docFiles.size();i++){
                c[i].setPath(dataPicture[m]);
                c[i].setName(docFiles.at(i).getName());
                c[i].addFileElement(docFiles[i]);
            }
            return true;
        default:
            return false;
    }
}
bool displayInMain(filesystem::path p,vector<CombinedComponent>&c,int x,int y){
    c.clear();
    vector<FileElement> f;
    error_code eq;
    filesystem::recursive_directory_iterator iter(p,filesystem::directory_options::skip_permission_denied,eq);
    for(filesystem::directory_entry op:iter){
        bool flag=false;
        if(eq){
            continue;
        }
        FileElement f1;
        f1.setName(op.path().filename());
        for(int i=0;i<imgExt.size();i++){
            if(op.path().extension()==imgExt[i]){
                f1.setIndex(img);
                f1.setPath(op.path().string());
                f.push_back(f1);
                flag = true;
                break ;
            }
        }
        if(flag) continue;
        for(int i=0;i<audExt.size();i++){
            if(op.path().extension()==audExt[i]){
                f1.setIndex(aud);
                f1.setPath(op.path().string());
                f.push_back(f1);
                flag= true;
                break ;
            }
        }
        if(flag) continue;
        for(int i=0;i<vidExt.size();i++){
            if(op.path().extension()==vidExt[i]){
                f1.setIndex(vid);
                f1.setPath(op.path().string());
                f.push_back(f1);
                flag = true;
                break ;
            }
        }
        if(flag) continue;
        for(int i=0;i<docsExt.size();i++){
            if(op.path().extension()==docsExt[i]){
                f1.setIndex(doc);
                f1.setPath(op.path().string());
                f.push_back(f1);
                flag = true;
                break ;
            }
        }
    }
    findGrid(c,f.size(),x,y);
    for(int i=0;i<f.size();i++){
        c[i].setName(f.at(i).getName());
        c[i].setPath(dataPicture[f.at(i).getIndex()]);
        c[i].addFileElement(f[i]);
    }
    return true;
}

//This function will be used to find the grid required for the main page to display
bool findGrid(vector<CombinedComponent>&c,int n,int x,int y){
    int available_width=CURRENT_SCREEN_WIDTH - x;
    int xp=10,yp=10,w=120,h=120;
    int gap=10;
    int m=np;
    while(n>0){
        if(m==0){
            m=np;
            xp=10;
            yp=10;
        }
        if (xp+w>available_width){
            xp= 10;
            yp =yp+gap+h;
        }
        CombinedComponent c1;
        c1.setRect(x+xp,y+yp,w,h);
        c.push_back(c1);
        xp= xp + w +gap;
        n--;
        m--;
    }
}

