//
//  PaneBase.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "PaneBase.h"
void PaneBase::init(int x, int y, int s, ofColor &c){
    _x = x;
    _y = y;
    _s = s;
    _c = c;
}
void PaneBase::fade(){
    ofFill();
    ofSetColor(0,5);
    ofRect(_x,_y,_s,_s);
}

void PaneBase::draw(){
    ofFill();
    ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),200);
    ofRect(_x,_y,_s,_s);
}