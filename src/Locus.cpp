//
//  Locus.cpp
//  
//
//  Created by 桃田稔也 on 1/11/16.
//
//
#include "Locus.h"
void Locus::init(){
    
}
void Locus::draw(){
    ofPushStyle();
    ofClear(color.r, color.g, color.b, alpha);
    ofPopStyle();
}
void Locus::setAlpha(bool direction){
    if (direction) {
        if (alpha<255){
            alpha += 5;
        }
        cout << "Yes:" << alpha << "\n";
    }else{
        if (alpha>0){
            alpha -= 5;
        }
        cout << "No:" << alpha << "\n";

    }
}
void Locus::setColor(ofColor _color){
    color = _color;
}
