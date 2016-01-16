//
//  PDF.cpp
//  monsterMachine20150116
//
//  Created by 桃田稔也 on 6/21/15.
//
//

#include "PDF.h"

PDF::PDF(){    
    resampleNum = 200;
    pdfNum = 1;
    polyMode = 1;
    step = 0.0;
    defaultSize = 1.0;
    currentScale = 1.0;
    
    fft_size = 0;
    avg_powerL = 0;
    avg_powerR = 0;
    audioValue = 0.0f;
    rotateAngle = 0.0f;
    
    position = ofPoint(0,0);
    
    pdf1.loadPDF("DJ/Akihito.pdf");//BotB
    pdf2.loadPDF("DJ/Nori.pdf");//Event Name
    pdf3.loadPDF("DJ/Slowbirds.pdf");//DJ
    pdf4.loadPDF("DJ/Morgan.pdf");//DJ
    pdf5.loadPDF("Sponsor/sponsors.pdf");//DJ
    pdf6.loadPDF("Comment/Tet.pdf");
    pdf7.loadPDF("Comment/Den-roi.pdf");
    pdf8.loadPDF("DJ/logo.pdf");
    pdf9.loadPDF("DJ/base.pdf");
    getPdfOutline(pdf1, outlines1, resampleNum);
    getPdfOutline(pdf2, outlines2, resampleNum);
    getPdfOutline(pdf3, outlines3, resampleNum);
    getPdfOutline(pdf4, outlines4, resampleNum);
    getPdfOutline(pdf5, outlines5, resampleNum);
    getPdfOutline(pdf6, outlines6, resampleNum);
    getPdfOutline(pdf7, outlines7, resampleNum);
    getPdfOutline(pdf8, outlines8, resampleNum);
    getPdfOutline(pdf9, outlines9, resampleNum);
}

void PDF::getPdfOutline(ofxPDF pdf_, vector<ofPolyline>& outlines_, int resample_){
    for (int i = 0; i < pdf_.getNumPath(); i++){//Each Chara
        ofPath p = pdf_.getPathAt(i);
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& polys = p.getOutline();
        for(int j=0;j<polys.size();j++){//Each Path
            outlines_.push_back(polys[j].getResampledByCount(resample_));
        }
    }
}

void PDF::setup(int _fft_size) {
    fft_size = _fft_size;
}

void PDF::update(){
    if (forwardFlag == false) {
        step += 0.005;
        if (step > 1.0) {
            step = 1.0;
            forwardFlag = true;
        }
    }else{
        step -= 0.005;
        if (step < 0.0) {
            step = 0.0;
            forwardFlag = false;
        }
    }

    if(rotatePattern==0){
        rotateAngle += 2;
        position = ofPoint(ofGetWidth()/2, 0);
    }else if(rotatePattern==1){
        rotateAngle += 2;
        position = ofPoint(0, ofGetHeight()/2);
    }else if(rotatePattern==2){
        rotateAngle=rotateAngle/1.5;
        position = position/4;
    }else if(rotatePattern==3){
        rotateAngle += 2;
        position = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    }else if(rotatePattern==4){
        rotateAngle += 2;
        position = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    }
}
void PDF::setDisplayOriginal(){
    pdfOriginalFlag = !pdfOriginalFlag;
}
void PDF::setDisplayOutline(){
    pdfOutlineFlag = !pdfOutlineFlag;
}
void PDF::setDisplayStep(){
    pdfStepFlag = !pdfStepFlag;
}
void PDF::setPdfNum(int _pdfNum, bool _displayFlag){
    pdfNum = _pdfNum;
    displayFlag = _displayFlag;
}
void PDF::setSoundFlag(){
    soundFlag = !soundFlag;
}
void PDF::setRotateFlag(){
    rotateFlag = !rotateFlag;
}
void PDF::setRotatePattern(){
    rotatePattern += 1;
    //cout << rotatePattern << "\n";
    if(rotatePattern>4) rotatePattern=0;
}
void PDF::setMaxSound(bool direction){
    if (direction) {
        maxSoundVal -= 10.0;
        if(maxSoundVal < 10.0) maxSoundVal = 10.0;
    }else{
        maxSoundVal += 10.0;
        if(maxSoundVal > 1000.0) maxSoundVal = 1000.0;
    }
    cout << "PDF - maxSoundVal:" << maxSoundVal << "\n";

};
void PDF::setMaxSize(bool direction){
    if (!direction) {
        maxSize -= 0.25;
        if(maxSize < -15.0) maxSize = -15.0;
    }else{
        maxSize += 0.25;
        if(maxSize > 15.0) maxSize = 15.0;
    }
    cout << "PDF - maxSize:" << maxSize << "\n";
};
void PDF::draw(float _soundL[], float _soundR[], float _avg_powerL, float _avg_powerR){
    
    if (!displayFlag) {
        return;
    }
    
    avg_powerL = _avg_powerL;
    avg_powerR = _avg_powerR;
    //ofEnableDepthTest();
    ofPushMatrix();
    
    if(rotatePattern==0){
        ofTranslate(position.x, position.y);
        ofRotate(rotateAngle, 0, 1, 0);
        /*
        ofPushStyle();
        ofSetColor(255);
        ofCircle(0, 0, 40);
        ofPopStyle();
        */
        ofTranslate(-pdf1.getWidth()/4, 0);
        
    }else if(rotatePattern==1){
        ofTranslate(position.x, position.y);
        ofRotate(rotateAngle, 1, 0, 0);
        /*
        ofPushStyle();
        ofSetColor(255);
        ofCircle(0, 0, 40);
        ofPopStyle();
         */

        ofTranslate(0, -pdf1.getHeight()/2);

    }else if(rotatePattern==2){
        ofTranslate(position.x, position.y);
        ofRotate(rotateAngle, 0, 1, 0);
        /*
        ofPushStyle();
        ofSetColor(255);
        ofCircle(0, 0, 40);
        ofPopStyle();
         */
    }else if(rotatePattern==3){
        ofTranslate(position.x, position.y);
        ofRotate(rotateAngle, 0, 0, 1);

        /*
        ofPushStyle();
        ofSetColor(255);
        ofCircle(0, 0, 40);
        ofPopStyle();
        */

        ofTranslate(ofPoint(-ofGetWidth()/2, -ofGetHeight()/2+200));

    }else if(rotatePattern==4){
        ofTranslate(position.x, position.y, 0);
        ofRotate(rotateAngle, 1, 1, 1);

        /*
         ofPushStyle();
         ofSetColor(255);
         ofCircle(0, 0, 40);
         ofPopStyle();
         */

        ofTranslate(ofPoint(-ofGetWidth()/2, -ofGetHeight()/2));

    }


    //Sound Affect
    if (soundFlag == true) {
        if(avg_powerL > avg_powerR) {
            avg_powerL = ofMap(avg_powerL, 0.0, maxSoundVal, defaultSize, maxSize, true);
            currentScale = avg_powerL;
        }else{
            avg_powerR = ofMap(avg_powerR, 0.0, maxSoundVal, defaultSize, maxSize, true);
            currentScale = avg_powerR;
        }
        //printf("avg_powerL %f, avg_powerR %f, currentScale: %f \n", avg_powerL, avg_powerR, currentScale);

    }else{currentScale = 1.0;}
    
    if (pdfOriginalFlag == true) {
        //Show Original PDF --------------------------------------------------------------
        ofPushMatrix();
        if(pdfNum == 1){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf1.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf1.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf1.draw();
        }else if(pdfNum == 2){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf2.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf2.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf2.draw();
        }else if(pdfNum == 3){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf3.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf3.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf3.draw();
        }else if(pdfNum == 4){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf4.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf4.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf4.draw();
        }else if(pdfNum == 5){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf5.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf5.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf5.draw();
        }else if(pdfNum == 6){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf6.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf6.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf6.draw();
        }else if(pdfNum == 7){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf7.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf7.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf7.draw();
        }else if(pdfNum == 8){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf8.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf8.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf8.draw();
        }else if(pdfNum == 9){
            ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf9.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf9.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
            ofScale(currentScale, currentScale);
            pdf9.draw();
        }
        
        ofPopMatrix();
    }
    
    if (pdfOutlineFlag == true) {
        //Show Outline --------------------------------------------------------------
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofSetColor(ofColor(100,100,100,255));
        ofScale(currentScale, currentScale);
        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        //ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        //ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        //ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        //ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnableAlphaBlending();
        
        //Fill
        ofNoFill();
        
        if(pdfNum == 1){
            for (int i = 0; i < outlines1.size(); i++){//Each Path
                ofPolyline & line = outlines1[i];
                //line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf1.getWidth()/2, pdf1.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 2){
            for (int i = 0; i < outlines2.size(); i++){//Each Path
                ofPolyline & line = outlines2[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf2.getWidth()/2, pdf2.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 3){
            for (int i = 0; i < outlines3.size(); i++){//Each Path
                ofPolyline & line = outlines3[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf3.getWidth()/2, pdf3.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 4){
            for (int i = 0; i < outlines4.size(); i++){//Each Path
                ofPolyline & line = outlines4[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf4.getWidth()/2, pdf4.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 5){
            for (int i = 0; i < outlines5.size(); i++){//Each Path
                ofPolyline & line = outlines5[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf5.getWidth()/2, pdf5.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);

                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 6){
            for (int i = 0; i < outlines6.size(); i++){//Each Path
                ofPolyline & line = outlines6[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf6.getWidth()/2, pdf6.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);

                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 7){
            for (int i = 0; i < outlines7.size(); i++){//Each Path
                ofPolyline & line = outlines7[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf7.getWidth()/2, pdf7.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);

                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 8){
            for (int i = 0; i < outlines8.size(); i++){//Each Path
                ofPolyline & line = outlines8[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf8.getWidth()/2, pdf8.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }else if(pdfNum == 9){
            for (int i = 0; i < outlines9.size(); i++){//Each Path
                ofPolyline & line = outlines9[i];
                line = line.getResampledByCount(resampleNum);
                ofBeginShape();
                
                for (int j = 0; j < line.size(); j++){//Each Point
                    ofPoint a = ofPoint(line[j].x, line[j].y);
                    ofPoint b = ofPoint(pdf9.getWidth()/2, pdf9.getHeight()/2);
                    a = a - b;
                    
                    int count = (fft_size * 0.6) / line.size() * j;
                    if (count > fft_size * 0.6) count = 0;
                    
                    audioValue = 0.0;
                    if (_soundL[count] > _soundR[count]) {
                        audioValue = _soundL[count];
                    }else{
                        audioValue = _soundR[count];
                    }
                    
                    audioValue = ofClamp(audioValue, 0, 80.0f);
                    //audioValue = ofMap(audioValue, 0.0, 180.0, 1.0, maxSize);
                    audioValue = ofMap(audioValue, 0.0f, 80.0f, 1.0f, 15.0f);
                    
                    a = a * audioValue;
                    ofVertex(a);
                    //ofCircle(a);
                }
                ofEndShape();
            }
        }
        ofPopMatrix();
        ofPopStyle();
    }
    
    if (pdfStepFlag == true) {
        //PATH STEP --------------------------------------------------------------
        ofPushMatrix();
        ofFill();
        ofSetColor(ofColor::white);
        
        //Sound Affect
        if (soundFlag == true) {
            if (pdfNum == 1) {
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf1.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf1.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 2){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf2.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf2.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 3){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf3.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf3.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 4){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf4.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf4.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 5){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf5.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf5.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 6){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf6.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf6.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 7){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf7.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf7.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 8){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf8.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf8.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 9){
                ofTranslate(-ofGetWidth()/2 * (currentScale - defaultSize)-pdf9.getWidth()*currentScale/2 + ofGetWidth()*currentScale/2, -ofGetHeight()/2 * (currentScale - defaultSize)-pdf9.getHeight()*currentScale/2 + ofGetHeight()*currentScale/2);
                ofScale(currentScale, currentScale);
            }
            
        }else{
            if (pdfNum == 1) {
                ofTranslate(ofGetWidth()/2 - pdf1.getWidth()/2, ofGetHeight()/2 - pdf1.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 2){
                ofTranslate(ofGetWidth()/2 - pdf2.getWidth()/2, ofGetHeight()/2 - pdf2.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 3){
                ofTranslate(ofGetWidth()/2 - pdf3.getWidth()/2, ofGetHeight()/2 - pdf3.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 4){
                ofTranslate(ofGetWidth()/2 - pdf4.getWidth()/2, ofGetHeight()/2 - pdf4.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 5){
                ofTranslate(ofGetWidth()/2 - pdf5.getWidth()/2, ofGetHeight()/2 - pdf5.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 6){
                ofTranslate(ofGetWidth()/2 - pdf6.getWidth()/2, ofGetHeight()/2 - pdf6.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 7){
                ofTranslate(ofGetWidth()/2 - pdf7.getWidth()/2, ofGetHeight()/2 - pdf7.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 8){
                ofTranslate(ofGetWidth()/2 - pdf8.getWidth()/2, ofGetHeight()/2 - pdf8.getHeight()/2);
                ofScale(currentScale, currentScale);
            }else if(pdfNum == 9){
                ofTranslate(ofGetWidth()/2 - pdf9.getWidth()/2, ofGetHeight()/2 - pdf9.getHeight()/2);
                ofScale(currentScale, currentScale);
            }
        }
        
        if (pdfNum == 1) {
            for (int i = 0; i < pdf1.getNumPath(); i++){
                ofPath& path = pdf1.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 2){
            for (int i = 0; i < pdf2.getNumPath(); i++){
                ofPath& path = pdf2.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 3){
            for (int i = 0; i < pdf3.getNumPath(); i++){
                ofPath& path = pdf3.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 4){
            for (int i = 0; i < pdf4.getNumPath(); i++){
                ofPath& path = pdf4.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 5){
            for (int i = 0; i < pdf5.getNumPath(); i++){
                ofPath& path = pdf5.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 6){
            for (int i = 0; i < pdf6.getNumPath(); i++){
                ofPath& path = pdf6.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 7){
            for (int i = 0; i < pdf7.getNumPath(); i++){
                ofPath& path = pdf7.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 8){
            for (int i = 0; i < pdf8.getNumPath(); i++){
                ofPath& path = pdf8.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }else if(pdfNum == 9){
            for (int i = 0; i < pdf9.getNumPath(); i++){
                ofPath& path = pdf9.getPathAt(i);
                vector<ofPolyline>& polys = path.getOutline();
                for (int k = 0; k < polys.size(); k++){
                    ofPolyline poly = polys[k];
                    poly = poly.getResampledByCount(100);
                    int target_size = poly.size() * step;
                    poly.resize(target_size);
                    poly.draw();
                }
            }
        }
        ofPopMatrix();
    }
    
    ofPopMatrix();
    //ofDisableDepthTest();
}
