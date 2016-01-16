#pragma once
#include "ofMain.h"

class Line {
    
public:
    Line();
    void setup(int fft_size);
    void update(float VOLUMETHRESHOLD);
    void draw(float *soundL, float *soundR, float avg_L, float avg_R, float max_L, float max_R);
    void setDirection(bool direction);
    void setPattern(int num);
    void setNumber(bool direction);
    void setDraw();
    void changeColor();
    void changeFrame();

private:
    float VOLUMETHRESHOLD = 5.0f;
    int fft_size;
    int directionMode = 0;
    int pattern = 0;
    int barNum = 2;
    
    int framePhase;
    int angle;
    int xCor, yCor, zCor;
    float cellHeight;
    float cellWidth;
    float ratio;//How much sound data apply
    
    bool backGroundFowardFlag;
    bool colorFlag = false;
    bool frameFlag = false;
    bool displayFlag = true;
    ofColor colL;
    ofColor colR;

};