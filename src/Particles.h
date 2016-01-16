//
//  Particles.h
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//
#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Grid.h"

class Particles {
public:
    void init(Grid &grid);
    void addParticleByNumber(int val);
    void draw(Grid &grid);
    void setRenge(float renge);
    void setGoals(Grid &grid);
    void setSpeed(bool direction);
    int getParticleNumber();
private:
    vector<Particle> par;
    int pSize;
    float speed = 5;
};
