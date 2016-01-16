//
//  tracingParticle.cpp
//  
//
//  Created by 桃田稔也 on 1/10/16.
//
//

#include "TracingParticle.h"
void TracingParticle::init(){
    myImg.loadImage("tracingParticles/tet.png");
    myImg2.loadImage("tracingParticles/op4.png");
    myImg3.loadImage("tracingParticles/op5.png");
    myImg4.loadImage("tracingParticles/logo.png");
    myImg5.loadImage("tracingParticles/honda.png");
    myImg6.loadImage("tracingParticles/eye.png");
    myImg7.loadImage("tracingParticles/cube2.png");
    myImg8.loadImage("tracingParticles/diamond.png");
    myImg9.loadImage("tracingParticles/base.png");
    
    grid.init(resolution, myImg);
    particles.init(grid);
    particles.setGoals(grid);

}
void TracingParticle::update(float _soundLimit, float soundL, float soundR){
    if (soundL > soundR) {
        scaleVal = soundL;
    }else{
        scaleVal = soundR;
    }
    
    soundLimit = _soundLimit;
    //cout << "ScaleVal:" << scaleVal << "\n";
}
void TracingParticle::draw(){
    //util.fade(bg);
    
    if(soundFlag){
        scaleVal = ofMap(scaleVal, 0.0, soundLimit, 1.0, maxScale, true);
    }else{
        scaleVal = 1.0f;
    }
    
    ofPushMatrix();
    switch (currentImg) {
        case 0:
            ofTranslate(ofGetWidth()/2 - myImg.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg.getHeight()*scaleVal/2);
            break;
        case 1:
            ofTranslate(ofGetWidth()/2 - myImg2.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg2.getHeight()*scaleVal/2);
            break;
        case 2:
            ofTranslate(ofGetWidth()/2 - myImg3.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg3.getHeight()*scaleVal/2);
            break;
        case 3:
            ofTranslate(ofGetWidth()/2 - myImg4.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg4.getHeight()*scaleVal/2);
            break;
        case 4:
            ofTranslate(ofGetWidth()/2 - myImg5.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg5.getHeight()*scaleVal/2);
            break;
        case 5:
            ofTranslate(ofGetWidth()/2 - myImg6.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg6.getHeight()*scaleVal/2);
            break;
        case 6:
            ofTranslate(ofGetWidth()/2 - myImg7.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg7.getHeight()*scaleVal/2);
            break;
        case 7:
            ofTranslate(ofGetWidth()/2 - myImg8.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg8.getHeight()*scaleVal/2);
            break;
        case 8:
            ofTranslate(ofGetWidth()/2 - myImg9.getWidth()*scaleVal/2, ofGetHeight()/2 - myImg9.getHeight()*scaleVal/2);
            break;
        default:
            break;
    }
    ofScale(1*scaleVal, 1*scaleVal);
    particles.draw(grid);
    //grid.draw();
    ofPopMatrix();
}
void TracingParticle::setImage(int num){
    currentImg = num;
    genPar();
}
void TracingParticle::setSpeed(bool direction){
    particles.setSpeed(direction);
    genPar();
}
void TracingParticle::setRange(bool direction){
    if (direction) {
        rangeVal++;
    }else{
        rangeVal--;
        if (rangeVal < 0) rangeVal = 0;
    }
    genPar();
}
void TracingParticle::setMaxScale(bool direction){
    if (direction) {
        maxScale += 0.1;
    }else{
        maxScale -= 0.1;
        if (maxScale < 1.0) maxScale = 1.0;
    }
    cout << "Tracing Particle - maxScale:" << maxScale << "\n";
}
ofColor TracingParticle::getBackgroundColor(){
    if (bgFlag) {
        return ofColor(128);
    }else{
        return ofColor(0);
    }
}
void TracingParticle::changeBackground(){
    bgFlag = !bgFlag;
}
void TracingParticle::changeSoundEffect(){
    soundFlag = !soundFlag;
}
int TracingParticle::getParticleNum(){
    return particles.getParticleNumber();
}
void TracingParticle::genPar(){
    int pGridSize = grid.getPanelNumber();
    
    switch (currentImg) {
        case 0:
            grid.init(resolution, myImg);
            break;
        case 1:
            grid.init(resolution, myImg2);
            break;
        case 2:
            grid.init(resolution, myImg3);
            break;
        case 3:
            grid.init(resolution, myImg4);
            break;
        case 4:
            grid.init(resolution, myImg5);
            break;
        case 5:
            grid.init(resolution, myImg6);
            break;
        case 6:
            grid.init(resolution, myImg7);
            break;
        case 7:
            grid.init(resolution, myImg8);
            break;
        case 8:
            grid.init(resolution, myImg9);
            break;
        default:
            break;
    }
    particles.addParticleByNumber(grid.getPanelNumber() - pGridSize);
    particles.setGoals(grid);
    particles.setRenge(rangeVal);
}

