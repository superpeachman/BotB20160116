//
//  PDF.h
//  monsterMachine20150116
//
//  Created by 桃田稔也 on 6/21/15.
//
//

#pragma once
#include "ofMain.h"
#include "ofxPDF.h"

class PDF {
    
public:
    PDF();
    
    int fft_size;
    int pdfNum;
    int polyMode;
    int rotatePattern = 0;
    float step;
    float defaultSize;
    float currentScale;
    float resampleNum;
    float rotateAngle;
    ofPoint position;
    
    bool pdfOriginalFlag = true; //Show Original PDF
    bool pdfOutlineFlag = true; //Show Outline PDF
    bool pdfStepFlag = true; //Show Step PDF
    
    bool forwardFlag = false;
    bool soundFlag = true;
    
    bool rotateFlag = true;
    
    float audioValue;
    float avg_powerL, avg_powerR;
    
    void setup(int fft_size);
    void setDisplayOriginal();
    void setDisplayOutline();
    void setDisplayStep();
    void setPdfNum(int pdfNum, bool displayFlag);
    void setSoundFlag();
    void setRotateFlag();
    void setRotatePattern();
    void setMaxSound(bool direction);
    void setMaxSize(bool direction);
    void update();
    void draw(float soundL[], float soundR[], float avg_powerL, float avg_powerR);

private:
    void getPdfOutline(ofxPDF pdf_, vector<ofPolyline>& outlines_, int resample_);
    ofxPDF pdf1;
    ofxPDF pdf2;
    ofxPDF pdf3;
    ofxPDF pdf4;
    ofxPDF pdf5;
    ofxPDF pdf6;
    ofxPDF pdf7;
    ofxPDF pdf8;
    ofxPDF pdf9;
    vector<ofPolyline> outlines1;
    vector<ofPolyline> outlines2;
    vector<ofPolyline> outlines3;
    vector<ofPolyline> outlines4;
    vector<ofPolyline> outlines5;
    vector<ofPolyline> outlines6;
    vector<ofPolyline> outlines7;
    vector<ofPolyline> outlines8;
    vector<ofPolyline> outlines9;
    float maxSoundVal = 200.0f;
    float maxSize = 2.0f;
    bool displayFlag = false;
};