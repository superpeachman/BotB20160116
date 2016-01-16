//
//  Pane.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "Pane.h"

void Pane::init(int x, int y, int s, ofColor &c){
    PaneBase::init(x,y,s,c);
    colUtil = *new Util();
}
void Pane::draw(){
    PaneBase::draw();
}