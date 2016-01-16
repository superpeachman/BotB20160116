//
//  Gifs.cpp
//  
//
//  Created by 桃田稔也 on 1/6/16.
//
//

#include "Gifs.h"
void Gifs::init(){
    fileName[0]="gif/1.gif";
    fileName[1]="gif/2.gif";
    fileName[2]="gif/3.gif";
    fileName[3]="gif/4.gif";
    fileName[4]="gif/5.gif";
    fileName[5]="gif/6.gif";
    fileName[6]="gif/7.gif";
    fileName[7]="gif/8.gif";
    fileName[8]="gif/9.gif";
    
    decoders.resize(FILENUM);
    files.resize(FILENUM);
    _cur.resize(FILENUM);
    _pre.resize(FILENUM);
    _cur2.resize(FILENUM);
    _pre2.resize(FILENUM);
    
    for(int i=0;i<FILENUM;i++){
        decoders[i].decode(fileName[i]);
        files[i] = decoders[i].getFile();
    }
}

void Gifs::update(float curBeat){
    //cout << bpmTapper.beatCosS(8) << "\n";
    
    if (!stopFlag) {
        for(int i=0;i<FILENUM;i++){
            _cur[i] = files[i].getNumFrames() - files[i].getNumFrames()*abs(curBeat);
        }
    }
}

void Gifs::draw(){
    if(drawFlag){
        float tempX,tempY;

        for (int i=0; i<rowNum; i++) {
            /* ROW */
            if (rowNum%2==1) {
                //odd number
                if(i==0){
                    tempY = ofGetHeight()/2 - files[targetGif].getHeight()/2;
                }else if(i==1){
                    tempY = ofGetHeight()/2 - files[targetGif].getHeight()/2 - files[targetGif].getHeight();
                }else if(i==2){
                    tempY = ofGetHeight()/2 - files[targetGif].getHeight()/2 + files[targetGif].getHeight();
                }else if(i%2==1){
                    //3 5 7...
                    if(i==3) tempY = ofGetHeight()/2 - files[targetGif].getHeight()/2 - files[targetGif].getHeight()*2;
                    if(i==5) tempY = ofGetHeight()/2 - files[targetGif].getHeight()/2 - files[targetGif].getHeight()*3;
                }else{
                    //4 6 8...
                    if(i==4) tempY = ofGetHeight()/2 + files[targetGif].getHeight()/2 + files[targetGif].getHeight()*1;
                    if(i==6) tempY = ofGetHeight()/2 + files[targetGif].getHeight()/2 + files[targetGif].getHeight()*2;
                }
            }else{
                //even number
                if(i==0){
                    tempY = ofGetHeight()/2;
                }else if(i==1){
                    tempY = ofGetHeight()/2 - files[targetGif].getHeight();
                }else if(i==2){
                    tempY = ofGetHeight()/2 + files[targetGif].getHeight();
                }else if(i%2==1){
                    //3 5 7...
                    tempY = ofGetHeight()/2 - files[targetGif].getHeight()*(floor((float)i/(float)2)+1);
                }else{
                    //4 6 8...
                    tempY = ofGetHeight()/2 + files[targetGif].getHeight()*(i/2);
                }
            }
            
            for (int i=0; i<columnNum; i++) {
                /* COLUMN */
                if (columnNum%2==1) {
                //odd number
                    if(i==0){
                        tempX = ofGetWidth()/2 - files[targetGif].getWidth()/2;
                    }else if(i==1){
                        tempX = ofGetWidth()/2 - files[targetGif].getWidth()/2 - files[targetGif].getWidth();
                    }else if(i==2){
                        tempX = ofGetWidth()/2 + files[targetGif].getWidth()/2;
                    }else if(i%2==1){
                    //3 5 7...
                        tempX = ofGetWidth()/2 - files[targetGif].getWidth()/2 - files[targetGif].getWidth()*(floor((float)i/(float)2)+1);
                    }else{
                    //4 6 8...
                        tempX = ofGetWidth()/2 + files[targetGif].getWidth()/2 + files[targetGif].getWidth()*(floor((float)i/(float)2)-1);
                    }
                }else{
                //even number
                    if(i==0){
                        tempX = ofGetWidth()/2 - files[targetGif].getWidth();
                    }else if(i==1){
                        tempX = ofGetWidth()/2;
                    }else if(i%2==1){
                    //3 5 7...
                        tempX = ofGetWidth()/2 + files[targetGif].getWidth()*floor((float)i/(float)2);
                    }else{
                    //2 4 6 8...
                        tempX = ofGetWidth()/2 - files[targetGif].getWidth()*(floor((float)i/(float)2)+1);
                    }
                }
                
                if(floor(_cur[targetGif]) > floor(_pre[targetGif])){
                    files[targetGif].drawFrame(_cur[targetGif], tempX, tempY);
                }else{
                    files[targetGif].drawFrame(files[targetGif].getNumFrames()-_cur[targetGif], tempX, tempY);
                }
            }
        }
    }
    
    for(int i=0;i<FILENUM;i++){
        _pre[i] = _cur[i];
    }
}

void Gifs::stop(){
    stopFlag = !stopFlag;
}
void Gifs::setDraw(){
    drawFlag = !drawFlag;
}
void Gifs::setPattern(int num){
    targetGif = num;
}
void Gifs::addColumn(bool _bool){
    if (_bool) {
        columnNum++;
    }else{
        if (columnNum != 1) columnNum--;
    }
}
void Gifs::addRow(bool _bool){
    if (_bool) {
        rowNum++;
    }else{
        if (rowNum != 1) rowNum--;
    }
}
