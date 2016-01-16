//
//  Util.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "Util.h"
void Util::init() {
}
void Util::fade(ofColor &c){
    ofSetColor(c);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
}
float Util::mouseSpeed(){
    float dx = ofGetMouseX() - ofGetMouseY();
    float dy = ofGetMouseX() - ofGetMouseY();
    return sqrt(dx * dx + dy * dy);
}

int Util::getRed(ofColor argb){
    int r = argb.r;
    return r;
}

int Util::getGreen(ofColor argb){
    int g = argb.g;
    return g;
}

int Util::getBlue(ofColor argb){
    int b = argb.b;
    return b;
}

int Util::getAlpha(ofColor argb){
    int a = argb.a;
    return a;
}