//
//  Grid.h
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//
//
#pragma once
#include "ofMain.h"
#include "Pane.h"
class Grid {

public:
    void init(int paneSize, ofImage &image);
    void draw();
    void drawByIndex(int index);
    int getIndex(int _x,int _y);
    int getXByIndex(int index);
    int getYByIndex(int index);
    ofColor getPanelColor(int index);
    int getPanelNumber();
    int getPanelSize();
    
    vector<Pane> panes;
    Pane pane;

private:
    ofColor org = ofColor(0,0);//Compare to image color
    int paneSize;
};