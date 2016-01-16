#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "fft.h"
#include "ofxGui.h"
#include "ofxGifDecoder.h"
#include "ofxPostGlitch.h"
#include "MSABPMTapper.h"

#include "Line.h"
#include "Human.h"
#include "Gifs.h"
#include "TracingParticle.h"
#include "Locus.h"
#include "PDF.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
    bool debugFlag = false;
    int bgMode = 0;
    
    /*--------------------------------------------------------------
     
     
     FFT
     
     
     --------------------------------------------------------------*/
    static const int fft_size = 2048;
    ofSoundStream soundStream;
    void audioIn(float* input, int bufferSize, int nChannels);
    
    float *left, *right;
    float *magnitudeL, *phaseL, *powerL, *tempL;
    float *magnitudeR, *phaseR, *powerR, *tempR;
    float max_tempL, max_tempR, max_magL, max_magR, avg_powerL, avg_powerR;
    int buffer_size;
    class fft myfft;
    
    float preTime, curTime, gapTime;
    
    /*--------------------------------------------------------------
     
     
     GUI
     
     
     --------------------------------------------------------------*/
    ofxPanel gui;
    ofxSlider<float> VOLUMETHRESHOLD;
    ofxSlider<float> KINECTMINIMUMDISTANCE;
    ofxSlider<float> KINECTMAXMUMDISTANCE;
    ofxSlider<float> KINECTDEPTHRATE;
    
    /*--------------------------------------------------------------
     
     
     BPM
     
     
     --------------------------------------------------------------*/
    msa::BPMTapper  bpmTapper;
    

    /*--------------------------------------------------------------
     
     
     Human
     
     
     --------------------------------------------------------------*/
    Human human;
    bool humanFlag;

    
    /*--------------------------------------------------------------
     
     
     LINE
     
     
     --------------------------------------------------------------*/
    Line line;
    bool lineFlag;

    /*--------------------------------------------------------------
     
     
     Gif
     
     
     --------------------------------------------------------------*/
    Gifs gifs;
    bool gifFlag;

    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    TracingParticle tp;
    bool tpFlag;

    /*--------------------------------------------------------------
     
     
     Locus
     
     
     --------------------------------------------------------------*/
    Locus locus;
    
    /*--------------------------------------------------------------
     
     
     Shader
     
     
     --------------------------------------------------------------*/
    ofShader shader;
    ofFbo myFbo;
    ofxPostGlitch myGlitch;
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    PDF pdf;
    bool pdfFlag = false;
    
    
};
