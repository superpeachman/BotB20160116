//
//  Human.h
//  
//
//  Created by 桃田稔也 on 11/9/15.
//
//

#pragma once
#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxOpenCv.h"

class Human {
public:
    void setup(int fft_size);
    void update(float min, float max, float depth);
    void draw();
    void debugDraw();
    void setNumberOfLine(bool direction);
    void setFillType();
    void setDraw();
    void setMode(int mode);
    void stop();
    void play();
private:
    //vector<ofxOpenNI> openNIDevices;
    //ofxOpenNI openNIDevices[1];
    ofxOpenNI openNIDevice;
    
    void handEvent(ofxOpenNIHandEvent & event);
    void userEvent(ofxOpenNIUserEvent & event);
    
    ofMesh mesh;
    
    vector<ofMesh> meshes;
    vector<ofPath> pathes;

    ofLight light;
    ofLight directionalLight;
    
    /*--------------------------------------------------------------
     
     
     Mode 2
     
     
     --------------------------------------------------------------*/
    
    /*--------------------------------------------------------------
     
     
     Mode 3 LINE
     
     
     --------------------------------------------------------------*/
    ofImage maskImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvContourFinder contourFinder;
    vector <ofPolyline> humanShapes;

    int fft_size;
    int mode;
    int width, height, kinectW, kinectH, currentRow;
    int numberOfLine;
    float minDis, maxDis, depthRate;
    bool detectFigure = false;
    bool fillType = false;
    bool displayFlag = true;
    bool displayRateFlag = false;
    bool musicFlag = true;
    float displayRate;//width is bigger or height is bigger
    float figureAffect = 1.0f;
};

//Universal function which sets normals
//for the triangle mesh
void setNormals( ofMesh &mesh );