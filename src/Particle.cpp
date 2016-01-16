//
//  Particle.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "Particle.h"
Particle::Particle(int _pSize, float _speed){
    pSize = _pSize;
    //cout << "pSize:" << pSize << "\n";

    _x = ofRandom(-ofGetWidth(),ofGetWidth());
    _y = ofRandom(-ofGetHeight(),ofGetHeight());
    GoalX = ofGetWidth()/2;
    GoalY = ofGetHeight()/2;
    //speed = ofRandom(speed,speed);
    speed = ofRandom(speed,speed);
    randomRenge = ofRandom(3);
    dead = false;
}
void Particle::refresh(){
    _px = _x;
    _py = _y;
    
    _x = (ofRandom(-randomRenge,randomRenge) + _x) + (GoalX- _x) / speed;
    _y = (ofRandom(-randomRenge,randomRenge) + _y) + (GoalY- _y) / speed;

    _r = _r + (targetColor.r - _r) / speed;
    _g = _g + (targetColor.g - _g) / speed;
    _b = _b + (targetColor.b - _b) / speed;
}
void Particle::draw(){
    //cout << "Deadd is " << dead << " lifespan is " << lifeSpan << "\n";
    
    if (dead==true) {
        lifeSpan -= 100.0;
    }
    
    ofSetLineWidth((float)pSize/(float)2);
    //cout << "c.r:"<< c.r << " c.g:" << c.g << " c.b:"<< c.b << "\n";
    ofSetColor(_r, _g, _b, lifeSpan/2);
    //ofSetColor(c);
    ofFill();
    ofLine(_px,_py,_x,_y);
    //ofSetColor(_r, _g, _b);
    ofRect(_x, _y, pSize, pSize);
}
void Particle::setStart(int x,int y){
    _x = x;
    _y = y;
}
void Particle::setGoal(int x,int y, bool isDead, ofColor c){
    GoalX = x;
    GoalY = y;
    targetColor = c;

    if(isDead == true){
        dead = true;
    }
}
void Particle::setRenge(float renge){
    randomRenge = renge;
}
void Particle::setSpeed(float _speed){
    speed = _speed;
}
bool Particle::checkDead(){
    if(lifeSpan < 0){
        return true;
    }else{
        return false;
    }
}
float Particle::getLifespan(){
    return lifeSpan;
}
