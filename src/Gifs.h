//
//  Gifs.h
//  
//
//  Created by 桃田稔也 on 1/6/16.
//
//
#pragma once
#include "ofMain.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"

class Gifs {
public:
    void init();
    void update(float curBeat);
    void stop();
    void draw();
    void setPattern(int num);
    void setDraw();
    void addColumn(bool _bool);
    void addRow(bool _bool);
private:
    vector<ofxGifDecoder> decoders;
    vector<ofxGifFile> files;
    
    //bool isOverlapping(Gif gif, vector<Gif> gifs);
    
    static const int FILENUM = 9;//Gif File Number
    string fileName [FILENUM];
    
    vector<float> xPos;
    vector<float> yPos;
    vector<float> rate;
    vector<float> _cur;
    vector<float> _pre;
    vector<float> _cur2;
    vector<float> _pre2;
    
    int targetGif = 0;
    int columnNum = 1;
    int rowNum = 1;
    bool stopFlag = false;
    bool drawFlag = true;
    
};

