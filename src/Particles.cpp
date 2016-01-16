//
//  Particles.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "Particles.h"
void Particles::init(Grid &_grid){
    pSize = _grid.getPanelSize();
    
    par.clear();
    for(int i=0;i<_grid.getPanelNumber();i++){
        par.push_back(*new Particle(pSize, speed));
    }
}

void Particles::addParticleByNumber(int val){
    for(int i=0; i<abs(val); i++){
        if(val > 0){
            par.push_back(*new Particle(pSize, speed));
        }else{
            //par.pop_back();
        }
    }
}
void Particles::draw(Grid &_grid){
    //cout << "par.size()" << par.size() << "\n";
    //for(int i=par.size();i>0;i--){
    for(int i=0; i < par.size();i++){
        if(i<_grid.getPanelNumber()){
            par[i].refresh();
            par[i].draw();
        }else{
            if(par[i].checkDead()){
                par.pop_back();
            }else{
                par[i].refresh();
                par[i].draw();
            }
        }
    }
}
void Particles::setRenge(float renge){
    for(int i=0;i<par.size();i++){
        par[i].setRenge(ofRandom(renge));
    }
}
void Particles::setSpeed(bool direction){
    if(direction){
        if (speed < 11) {
            speed++;
        }
    }else{
        if (speed > 1) {
            speed--;
        }
    }
    for(int i=0;i<par.size();i++){
        par[i].setSpeed(speed);
    }
}
void Particles::setGoals(Grid &_grid){
    //Swap Particles
    int randomNum = ofRandom(par.size());
    for(int i = 0; i < par.size(); i++){
        Particle temp = par[i];
        par[i] = par[randomNum];
        par[randomNum] = temp;
    }
    
    for(int i=0;i<par.size();i++){
        if(i<_grid.getPanelNumber()){
            par[i].setGoal(_grid.getXByIndex(i), _grid.getYByIndex(i), false, _grid.getPanelColor(i));
        }else{
            float rad = ofDegToRad(ofRandom(360));
            float x = ofGetWidth()*cos(rad);
            float y = ofGetWidth()*sin(rad);
            par[i].setGoal(x, y, true, ofColor(0));
        }
    }
}
int Particles::getParticleNumber(){
    return par.size();
}
