#include "Line.h"

Line::Line(){
    fft_size = 0;
    backGroundFowardFlag = true;
    framePhase = 0;
    angle = 180;
    xCor=0;
    yCor=0;
    zCor=1;
    cellHeight = 0.0f;
    ratio = 0.0f;
    colL = * new ofColor();
    colR = * new ofColor();
}
void Line::setup(int _fft_size) {
    fft_size = _fft_size;
    ratio = 0.7f;
}
void Line::update(float vol) {
    VOLUMETHRESHOLD = vol;
    cellHeight = (float)ofGetHeight() / (float)fft_size;
    cellWidth = (float)ofGetWidth() / (float)fft_size;
    
    if (frameFlag) {
        if(pattern==0){
            framePhase = framePhase + 10;
            if(framePhase > ofGetHeight()) framePhase = 0;
        }else{
            framePhase = framePhase + 10;
            if(framePhase > ofGetWidth()) framePhase = 0;
        }
    }
    
    switch (directionMode) {
        case 0:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 1;
            yCor = 0;
            zCor = 0;
            break;
        case 1:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 1;
            yCor = 1;
            zCor = 0;
            break;
        case 2:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 1;
            yCor = 1;
            zCor = 1;
            break;
        case 3:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 0;
            yCor = 1;
            zCor = 0;
            break;
        case 4:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 0;
            yCor = 1;
            zCor = 1;
            break;
        case 5:
            /*--------------------------------------------------------------
             
             
             1.
             
             
             --------------------------------------------------------------*/
            angle = angle + 2;
            if(angle%360 == 0) angle = 0;
            xCor = 0;
            yCor = 0;
            zCor = 1;
            break;
        case 6:
            if(angle != 180){
                if(angle > 180){
                    angle = angle - 1;
                }else if(angle < 180){
                    angle = angle + 1;
                }
            }
            xCor = 0;
            yCor = 0;
            zCor = 1;
        default:
            break;
    }
}
void Line::draw(float *soundL, float *soundR, float avg_L, float avg_R, float max_L, float max_R){
    if (displayFlag == false) return;
    
    //printf("pattern: %i, cellHeight: %f, barNum: %i \n", pattern, cellHeight, barNum);
    //printf("avg_L: %f, avg_R: %f \n", avg_L, avg_R);
    //printf("max_L: %f max_R: %f \n", max_L, max_R);
    
    if(pattern==0){
        /*--------------------------------------------------------------
         
         
         AVERAGE VERTICAL
         
         
         --------------------------------------------------------------*/
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        //ofRotate(angle - 180, xCor, yCor, zCor);
        
        for (int i = 0; i < fft_size; i++){
            
            //float randomSp = ofRandom(10);
            
            if(colorFlag == false){
                /*--------------------------------------------------------------
                 
                 
                 MONO
                 
                 
                 --------------------------------------------------------------*/
                if (soundL[i] > (float)VOLUMETHRESHOLD/(float)10) { colL.set(255); }
                else{ colL.set(0); }
                if (soundR[i] > (float)VOLUMETHRESHOLD/(float)10) { colR.set(255); }
                else{ colR.set(0); }
            }else{
                /*--------------------------------------------------------------
                 
                 
                 COLOR
                 
                 
                 --------------------------------------------------------------*/
                float valL = ofMap(soundL[i], 0.0f, VOLUMETHRESHOLD, 0, 255, true);
                colL.set(valL);
                float valR = ofMap(soundR[i], 0.0f, VOLUMETHRESHOLD, 0, 255, true);
                colR.set(valR);
                //printf("val: %f, max_L: %f soundL[i]: %f \n", val, VOLUMETHRESHOLD, soundL[i]);
            }
            
            if(colL.getBrightness() > 0.5 && colR.getBrightness() > 0.5){
                if (barNum == 2) {
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)2, cellHeight);
                        //Right
                        ofSetColor(colR);
                        ofRect(0, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)2, cellHeight);
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)2, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)2, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)2, cellHeight);
                        
                        ofTranslate(0, -framePhase*2);
                        //Right
                        ofSetColor(colR);
                        ofRect(0, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)2, cellHeight);
                        ofRect(0, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)2, cellHeight);
                        ofRect(0, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)2, cellHeight);
                        ofPopMatrix();
                    }
                }else if(barNum == 4){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)4, cellHeight);
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)4, cellHeight);
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - ofGetHeight() - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i + ofGetHeight() - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - ofGetHeight() - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect(0, cellHeight * i + ofGetHeight() - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)4, cellHeight);
                        
                        ofTranslate(0, -framePhase*2);
                        //Light
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)4, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)4, cellHeight);
                        ofRect((float)ofGetWidth()/(float)4, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)4, cellHeight);
                        ofPopMatrix();
                    }
                }else if(barNum == 8){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*1, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        ofTranslate(0, -framePhase*2);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*3, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        ofTranslate(0, framePhase*2);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8*2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        ofTranslate(0, -framePhase*2);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)8, cellHeight);
                        ofRect((float)ofGetWidth()/(float)8, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)8, cellHeight);
                        ofPopMatrix();
                    }
                }else if(barNum == 16){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                        for (int x=7; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)-ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)16, cellHeight);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                        for (int x=7; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)16, cellHeight);
                            }else{
                                ofRect((float)ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                        
                        for (int x=7; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(0, -framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)ofGetWidth()/(float)16*x, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                            }else{
                                ofTranslate(0, framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)16, cellHeight);
                                ofRect((float)ofGetWidth()/(float)16*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)16, cellHeight);
                            }
                        }
                        ofPopMatrix();
                    }
                }else if(barNum == 32){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                        for (int x=15; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)-ofGetWidth()/(float)32*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)32, cellHeight);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                        for (int x=15; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)32*x, ofGetHeight()/2 - cellHeight * i, (float)ofGetWidth()/(float)32, cellHeight);
                            }else{
                                ofRect((float)ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                        
                        for (int x=15; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(0, -framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)32*x, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)32*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)32*x, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)32*x, ofGetHeight()/2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)ofGetWidth()/(float)32*x, ofGetHeight()/2 - cellHeight * i, (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)ofGetWidth()/(float)32*x, ofGetHeight()/2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                            }else{
                                ofTranslate(0, framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)32, cellHeight);
                                ofRect((float)ofGetWidth()/(float)32*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)32, cellHeight);
                            }
                        }
                        ofPopMatrix();
                    }
                }else if (barNum == 64){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                        for (int x=31; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)-ofGetWidth()/(float)64*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)64, cellHeight);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                        for (int x=31; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)64*x, ofGetHeight()/2 - cellHeight * i, (float)ofGetWidth()/(float)64, cellHeight);
                            }else{
                                ofRect((float)ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(0, framePhase);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                        ofRect((float)-ofGetWidth()/(float)2, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                        ofRect(0, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                        
                        for (int x=31; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(0, -framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)64*x, (float)ofGetHeight()/(float)2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)64*x, (float)ofGetHeight()/(float)2 - cellHeight * i, (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)64*x, (float)ofGetHeight()/(float)2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)64*x, ofGetHeight()/2 - cellHeight * i - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)ofGetWidth()/(float)64*x, ofGetHeight()/2 - cellHeight * i, (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)ofGetWidth()/(float)64*x, ofGetHeight()/2 - cellHeight * i + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                            }else{
                                ofTranslate(0, framePhase*2);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)-ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2 - ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2, (float)ofGetWidth()/(float)64, cellHeight);
                                ofRect((float)ofGetWidth()/(float)64*x, cellHeight * i - (float)ofGetHeight()/(float)2 + ofGetHeight(), (float)ofGetWidth()/(float)64, cellHeight);
                            }
                        }
                        ofPopMatrix();
                    }
                }//IF
            }
        }//for
        ofPopMatrix();
    }else if(pattern==1){
        /*--------------------------------------------------------------
         
         
         AVERAGE HORIZONTAL
         
         
         --------------------------------------------------------------*/
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        //ofRotate(angle - 180, xCor, yCor, zCor);
        
        for (int i = 0; i < fft_size; i++){
            if(colorFlag == false){
                /*--------------------------------------------------------------
                 
                 
                 MONO
                 
                 
                 --------------------------------------------------------------*/
                if (soundL[i] > (float)VOLUMETHRESHOLD/(float)2) { colL.set(255); }
                else{ colL.set(0); }
                if (soundR[i] > (float)VOLUMETHRESHOLD/(float)2) { colR.set(255); }
                else{ colR.set(0); }
            }else{
                /*--------------------------------------------------------------
                 
                 
                 COLOR
                 
                 
                 --------------------------------------------------------------*/
                float valL = ofMap(soundL[i], 0.0f, VOLUMETHRESHOLD, 0, 255, true);
                colL.set(valL);
                float valR = ofMap(soundR[i], 0.0f, VOLUMETHRESHOLD, 0, 255, true);
                colR.set(valR);
                //printf("getBrightness: %f, getLightness: %f \n", colL.getBrightness(), colL.getLightness());
                //cout << "colL.getClamped()" << colL.getClamped() << "\n";
            }
            
            if(colL.getBrightness() > 125.0f && colR.getBrightness() > 125.0f){
                if (barNum == 2) {
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)2);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)2);
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)2);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)2);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)2);
                        
                        ofTranslate(framePhase*2, 0);
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)2);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)2);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)2);
                        ofPopMatrix();
                    }
                }else if(barNum == 4){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)4);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)4);
                        
                        ofTranslate(framePhase*2, 0);
                        //Light
                        ofSetColor(colL);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)4, cellWidth, (float)ofGetHeight()/(float)4);
                        
                        ofPopMatrix();
                    }
                }else if(barNum == 8){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        ofTranslate(framePhase*2, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        ofTranslate(-framePhase*2, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)8*2, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        
                        ofTranslate(framePhase*2, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)8, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)8*3, cellWidth, (float)ofGetHeight()/(float)8);
                        
                        ofPopMatrix();
                    }
                }else if(barNum == 16){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)16);
                        for (int x=7; x>0; x--) {
                            if(x%2!=0){
                                ofRect(ofGetWidth()/2 - cellWidth * i, (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }else{
                                ofRect(-ofGetWidth()/2 + cellWidth * i, (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)16);
                        for (int x=1; x<8; x++) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)16);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)16);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)16);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)16);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)16);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)16);
                        
                        for (int x=7; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect(ofGetWidth()/2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect(ofGetWidth()/2 - cellWidth * i, (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect(ofGetWidth()/2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }else{
                                ofTranslate(-framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect(-ofGetWidth()/2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect(-ofGetWidth()/2 + cellWidth * i, (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect(-ofGetWidth()/2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)16*x, cellWidth, (float)ofGetHeight()/(float)16);
                            }
                        }
                        ofPopMatrix();
                    }
                }else if(barNum == 32){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)32);
                        for (int x=15; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)32);
                        for (int x=1; x<16; x++) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)32);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)32);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)32);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)32);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)32);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)32);
                        
                        
                        for (int x=15; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }else{
                                ofTranslate(-framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)32*x, cellWidth, (float)ofGetHeight()/(float)32);
                            }
                        }
                        ofPopMatrix();
                    }
                }else if(barNum == 64){
                    if (frameFlag == false) {
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)64);
                        for (int x=31; x>0; x--) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }
                        }
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)64);
                        for (int x=1; x<32; x++) {
                            if(x%2!=0){
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }else{
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }
                        }
                    }else{
                        ofPushMatrix();
                        ofTranslate(-framePhase, 0);
                        //Left
                        ofSetColor(colL);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)64);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)64);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)2, cellWidth, (float)ofGetHeight()/(float)64);
                        
                        //Right
                        ofSetColor(colR);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)64);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, 0, cellWidth, (float)ofGetHeight()/(float)64);
                        ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), 0, cellWidth, (float)ofGetHeight()/(float)64);
                        
                        
                        for (int x=31; x>0; x--) {
                            if(x%2!=0){
                                ofTranslate(framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i, (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)ofGetWidth()/(float)2 - cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }else{
                                ofTranslate(-framePhase*2, 0);
                                //Left
                                ofSetColor(colL);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)-ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                
                                //Right
                                ofSetColor(colR);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i - ofGetWidth(), (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i, (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                                ofRect((float)-ofGetWidth()/(float)2 + cellWidth * i + ofGetWidth(), (float)ofGetHeight()/(float)64*x, cellWidth, (float)ofGetHeight()/(float)64);
                            }
                        }
                        ofPopMatrix();
                    }
                }//IF
            }
        }//for
        ofPopMatrix();
    }else if(pattern==2){
        
        
        
        
        
    }else if(pattern == 2){//Volume2 Random
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotate(angle - 180, xCor, yCor, zCor);
        for (int i = 0; i < fft_size; i++){
            int random = ofRandom(fft_size);
            
            if (soundL[random] > 0.5) {
                colL.set(255.0, 255.0, 255.0);
            }else{
                colL.set(0.0, 0.0, 0.0);
            }
            ofSetColor(colL);
            ofRect(-ofGetWidth()/2, cellHeight * i - ofGetHeight()/2, ofGetWidth()/2, cellHeight);
        }
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofRotate(angle, xCor, yCor, zCor);
        
        for (int i = 0; i < fft_size; i++){
            int random = ofRandom(fft_size);
            
            if (soundR[random] > 0.5) {
                colL.set(255.0, 255.0, 255.0);
            }else{
                colL.set(0.0, 0.0, 0.0);
            }
            ofSetColor(colL);
            ofRect(-ofGetWidth()/2, cellHeight * i - ofGetHeight()/2, ofGetWidth()/2, cellHeight);
        }
        ofPopMatrix();
    }
}

void Line::setDirection(bool _direction) {
    if(_direction == true){
        if(directionMode+1 > 10){
            directionMode = 10;
        }else{
            directionMode+=1;
        }
        printf("directionMode: %i \n", directionMode);
    }else{
        if(directionMode-1 < 0){
            directionMode = 0;
        }else{
            directionMode-=1;
        }
        printf("directionMode: %i \n", directionMode);
    }
}

void Line::setNumber(bool _direction) {
    
    if(_direction == true){
        if(barNum*2 > 64){
            barNum = 64;
        }else{
            barNum*=2;
        }
        printf("barNum: %i \n", barNum);
    }else{
        if(barNum/2 < 2){
            barNum = 2;
        }else{
            barNum/=2;
        }
        printf("barNum: %i \n", barNum);
    }
}

void Line::setPattern(int _pattern){
    pattern = _pattern;
}
void Line::setDraw(){
    displayFlag = !displayFlag;
}

void Line::changeColor(){
    colorFlag = !colorFlag;
}

void Line::changeFrame(){
    frameFlag = !frameFlag;
}

