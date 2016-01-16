//
//  Locus.h
//  
//
//  Created by 桃田稔也 on 1/11/16.
//
//
#pragma once
#include "ofMain.h"
class Locus {
    
public:
    void init();
    void draw();
    void setAlpha(bool direction);
    void setColor(ofColor color);
private:
    int alpha = 10;
    ofColor color = ofColor(0);
};
