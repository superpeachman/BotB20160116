//
//  Util.h
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#pragma once
#include "ofMain.h"

class Util {
public:
    void init();
    void fade(ofColor &c);
    float mouseSpeed();
    int getRed(ofColor argb);
    int getGreen(ofColor argb);
    int getBlue(ofColor argb);
    int getAlpha(ofColor argb);
    
private:
};
