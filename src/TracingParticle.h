//
//  tracingParticle.h
//  
//
//  Created by 桃田稔也 on 1/10/16.
//
//

#pragma once
#include "ofMain.h"
#include "Grid.h"
#include "Particles.h"
#include "Util.h"

class TracingParticle : public PaneBase{
public:
    void init();
    void update(float soundLimit, float soundL, float soundR);
    void draw();
    void setImage(int num);
    void setSpeed(bool direction);
    void setRange(bool direction);
    void setMaxScale(bool direction);
    ofColor getBackgroundColor();
    void changeBackground();
    void changeSoundEffect();

    int getParticleNum();

private:
    void genPar();
    
    Grid grid;
    Particles particles;
    Util util;
    
    int currentImg = 0;
    int resolution = 2;
    int rangeVal = 5;
    float scaleVal = 0;
    float soundLimit = 0;
    float maxScale = 3;
    bool bgFlag = false;
    bool soundFlag = true;
    
    ofColor bg = ofColor(125,50);
    
    ofImage myImg;
    ofImage myImg2;
    ofImage myImg3;
    ofImage myImg4;
    ofImage myImg5;
    ofImage myImg6;
    ofImage myImg7;
    ofImage myImg8;
    ofImage myImg9;
};