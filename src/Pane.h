//
//  Pane.h
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//
#pragma once
#include "ofMain.h"
#include "PaneBase.h"
#include "Util.h"

class Pane : public PaneBase{
public:
    void init(int x, int y, int s, ofColor &c);
    void draw();
private:
    Util colUtil;
};
