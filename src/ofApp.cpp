#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /*--------------------------------------------------------------
     
     
     BASE
     
     
     --------------------------------------------------------------*/
    ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    
    /*--------------------------------------------------------------
     
     
     FFT
     
     
     --------------------------------------------------------------*/
    buffer_size = fft_size * 2;
    left = new float[buffer_size];
    magnitudeL = new float[fft_size];
    phaseL = new float[fft_size];
    powerL = new float[fft_size];
    right = new float[buffer_size];
    magnitudeR = new float[fft_size];
    phaseR = new float[fft_size];
    powerR = new float[fft_size];
    ofSoundStreamSetup(0, 2, this, 44100, buffer_size, 4);
    tempL = new float[fft_size];
    tempR = new float[fft_size];
    for (int i = 0; i < fft_size; i++) {
        tempL[i] = 0.0f;
        tempR[i] = 0.0f;
    }
    
    gapTime = 0;
    curTime = 0;
    preTime = 0;

    /*--------------------------------------------------------------
     
     
     GUI
     
     
     --------------------------------------------------------------*/
    gui.setup();
    gui.add(VOLUMETHRESHOLD.setup("VOL THRESHOLD", 5.0f, 0.5f, 30.0f));
    gui.add(KINECTMINIMUMDISTANCE.setup("MIN DISTANCE", 500.0f, 300.0f, 1000.0f));
    gui.add(KINECTMAXMUMDISTANCE.setup("MAX DISTANCE", 3000.0f, 2000.0f, 5000.0f));
    gui.add(KINECTDEPTHRATE.setup("DEPTH RATE", 0.5f, 0.1f, 1.0f));

    /*--------------------------------------------------------------
     
     
     LINE
     
     
     --------------------------------------------------------------*/
    line = *new Line();
    line.setup(fft_size);
    lineFlag = false;

    
    /*--------------------------------------------------------------
     
     
     Human
     
     
     --------------------------------------------------------------*/
    human.setup(fft_size);
    humanFlag = false;
    
    /*--------------------------------------------------------------
     
     
     Gif
     
     
     --------------------------------------------------------------*/
    gifs.init();
    gifFlag = false;

    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    tp.init();
    tpFlag = false;

    /*--------------------------------------------------------------
     
     
     Locus
     
     
     --------------------------------------------------------------*/
    locus.init();
    
    /*--------------------------------------------------------------
     
     
     Shader
     
     
     --------------------------------------------------------------*/
    myFbo.allocate(ofGetWidth()*2,ofGetHeight()*2);
    myGlitch.setup(&myFbo);
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    pdf = *new PDF();
    pdf.setup(fft_size);
}

//--------------------------------------------------------------
void ofApp::update(){
    bpmTapper.update();
    
    /*--------------------------------------------------------------
     
     
     Locus
     
     
     --------------------------------------------------------------*/
    if (bgMode == 3) {
        locus.setColor(tp.getBackgroundColor());
    }else{
        locus.setColor(ofColor(0));
    }
    
    //Audio In
    curTime = ofGetElapsedTimef();
    gapTime = curTime - preTime;
    gapTime = ofClamp(gapTime, 0.0f, 1.0f);
    preTime = curTime;
    avg_powerL = 0.0;
    avg_powerR = 0.0;
    max_tempL = 0.0;
    max_tempR = 0.0;
    myfft.powerSpectrum(0, fft_size, left, buffer_size,	magnitudeL, phaseL, powerL, &max_magL, &avg_powerL);
    myfft.powerSpectrum(0, fft_size, right, buffer_size, magnitudeR, phaseR, powerR, &max_magR, &avg_powerR);
    
    for (int i = 0; i < fft_size; i++) {
        tempL[i] *= 0.97f;
        tempR[i] *= 0.97f;
        tempL[i] = max(magnitudeL[i], tempL[i])*gapTime;
        tempR[i] = max(magnitudeR[i], tempR[i])*gapTime;
        if(max_tempL < tempL[i]) max_tempL = tempL[i];
        if(max_tempR < tempR[i]) max_tempR = tempR[i];
        //printf("tempL %f \n", tempL[i]);
        //printf("tempR %f \n", tempR[i]);
    }
    /*--------------------------------------------------------------
     
     
     Line
     
     
     --------------------------------------------------------------*/
    if(bgMode == 0){ line.update(VOLUMETHRESHOLD); }
    
    /*--------------------------------------------------------------
     
     
     Human
     
     
     --------------------------------------------------------------*/
    if(bgMode == 1){ human.update(KINECTMINIMUMDISTANCE, KINECTMAXMUMDISTANCE, KINECTDEPTHRATE); }
    
    /*--------------------------------------------------------------
     
     
     Gif
     
     
     --------------------------------------------------------------*/
    if(bgMode == 2){ gifs.update(abs(bpmTapper.beatPerc())); }
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    if(bgMode == 3){ tp.update(VOLUMETHRESHOLD, avg_powerL, avg_powerR); }
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    if(pdfFlag){ pdf.update();}
    
    
    /* ---------------------------------------------------------------------------------------------------------------------------------- */
    
    
    
    /*--------------------------------------------------------------
     
     
     Shader
     
     
     --------------------------------------------------------------*/
    myFbo.begin();

    /*--------------------------------------------------------------
     
     
     Locus
     
     
     --------------------------------------------------------------*/
    locus.draw();
    
    ofPushStyle();
    ofSetColor(255);
    
    /*--------------------------------------------------------------
     
     
     Line
     
     
     --------------------------------------------------------------*/
    if(bgMode == 0){ line.draw(tempL, tempR, avg_powerL, avg_powerR, max_tempL, max_tempR); }
    
    /*--------------------------------------------------------------
     
     
     Human
     
     
     --------------------------------------------------------------*/
    if(bgMode == 1){ human.draw(); }

    /*--------------------------------------------------------------
     
     
     Gif
     
     
     --------------------------------------------------------------*/
    if(bgMode == 2){ gifs.draw(); }
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    if(bgMode == 3){ tp.draw(); }
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    if(pdfFlag){ pdf.draw(tempL, tempR, avg_powerL, avg_powerR); }

    ofPopStyle();
    myFbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    //printf("avg_power: %f %f \n", avg_powerL, avg_powerR);
    
    /*--------------------------------------------------------------
     
     
     shader
     
     
     --------------------------------------------------------------*/
    int value = ofGetElapsedTimef()*1000;
    float a;
    a = (value % 255);
    a = ofMap(a, 0, 255, 0.0, 1.0);
    value -= a;
    //printf("value: %i, a: %f \n", value, a);
    
    myGlitch.setCustomTimer(a);
    myGlitch.generateFx();
    myFbo.draw(0,0, ofGetWidth(), ofGetHeight());
    

    if(debugFlag){
        ofPushStyle();
        ofSetColor(255);
        human.debugDraw();

        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        gui.draw();
        
        ofDrawBitmapString("FPS: "+ofToString(ofGetFrameRate(), 2)+
                           " BPM: " + ofToString(bpmTapper.bpm()) +
                           " bgMode =" + ofToString(bgMode) +
                           " 1:LINE 2:HUMAN 3:GIF 4:PARTICLE" +
                           " pdfFlag:" + ofToString(pdfFlag) +
                           " Particle Num: " + ofToString(tp.getParticleNum()), 10, ofGetHeight()-10);
        bpmTapper.draw(ofGetWidth()-100, ofGetHeight()-20, 5);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2];
        right[i] = input[i*2+1];
    }
}

//--------------------------------------------------------------
/*void ofApp::userEvent(ofxOpenNIUserEvent & event){
 // show user event messages in the console
 ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
 }*/

//--------------------------------------------------------------
/*void ofApp::handEvent(ofxOpenNIHandEvent & event){
 // show hand event messages in the console
 ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;
 }*/

//--------------------------------------------------------------
void ofApp::exit(){
    human.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //# define OF_KEY_CTRL 0x0200
    //# define OF_KEY_TAB 0x09
    //# define OF_KEY_ALT 0x0300
    //# define OF_KEY_SHIFT 0x0400
    //# define OF_KEY_SHIFT 0x0400
    
    /*--------------------------------------------------------------
     
     
     Mutual
     
     
     --------------------------------------------------------------*/
    
    //TAP --------------------------------------------------------------
    if(key == OF_KEY_RETURN){
        bpmTapper.tap();
        bpmTapper.startFresh();
    }

    //DEBUG --------------------------------------------------------------
    if(key == OF_KEY_SHIFT){ debugFlag = !debugFlag; }
    
    //FULL SCREEN --------------------------------------------------------------
    if(key == OF_KEY_ALT){
        ofToggleFullscreen();
        myFbo.allocate(ofGetWidth(),ofGetHeight());
    }
    
    if(key == 'z'){
        bgMode = 0;//LINE
    }else if(key == 'x'){
        bgMode = 1;//HUMAN
    }else if(key == 'c'){
        bgMode = 2;//GIF
    }else if(key == 'v'){
        bgMode = 3;//PARTICLE
    }
    
    /*--------------------------------------------------------------
     
     
     LINE
     
     
     --------------------------------------------------------------*/
    if(!pdfFlag && bgMode==0
       && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
        
        if( key == '1' ){ line.setPattern(1); }
        else if( key == '2'){ line.setPattern(2); }
        else if( key == '3'){ line.setPattern(3); }
        else if( key == '4'){ line.setPattern(4); }
        else if( key == '5'){ line.setPattern(5); }
        else if( key == '6'){ line.setPattern(6); }
        else if( key == '7'){ line.setPattern(7); }
        else if( key == '8'){ line.setPattern(8); }
        else if( key == '9'){ line.setPattern(9); }
        else if( key == '0'){ line.setPattern(0); }
    }
    
    if(!pdfFlag && bgMode==0 && key == OF_KEY_LEFT){
        line.setDirection(false);
    }else if(!pdfFlag && bgMode==0 && key == OF_KEY_RIGHT){
        line.setDirection(true);
    }
    
    if(!pdfFlag && bgMode==0 && key == OF_KEY_UP){
        line.setNumber(true);
    }else if(!pdfFlag && bgMode==0 && key == OF_KEY_DOWN){
        line.setNumber(false);
    }
    if(!pdfFlag && bgMode==0 && key == 'q'){
        line.setDraw();
    }
    if(!pdfFlag && bgMode==0 && key == 'e'){
        line.changeColor();
    }
    
    if(!pdfFlag && bgMode==0 && key == 'w'){
        line.changeFrame();
    }
    
    /*--------------------------------------------------------------
     
     
     Human
     
     
     --------------------------------------------------------------*/
    if(!pdfFlag && bgMode==1 && key == 'q'){
        human.setDraw();
    }
    
    if(!pdfFlag && bgMode==1
       && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
        
        if( key == '1' ){ human.setMode(1); } // LINE
        else if( key == '2'){ human.setMode(2); } //MASK
        else if( key == '3'){ human.setMode(3); }
        else if( key == '4'){ human.setMode(4); }
        else if( key == '5'){ human.setMode(5); }
        else if( key == '6'){ human.setMode(6); }
        else if( key == '7'){ human.setMode(7); }
        else if( key == '8'){ human.setMode(8); }
        else if( key == '9'){ human.setMode(9); }
        else if( key == '0'){ human.setMode(0); }
    }
    
    if(!pdfFlag && bgMode==1 && key == OF_KEY_LEFT){
    }else if(!pdfFlag && bgMode==1 && key == OF_KEY_RIGHT){
    }
    
    if(!pdfFlag && bgMode==1 && key == OF_KEY_UP){
        human.setNumberOfLine(true);
    }else if(!pdfFlag && bgMode==1 && key == OF_KEY_DOWN){
        human.setNumberOfLine(false);
    }
    
    if(!pdfFlag && bgMode==1 && key == 'w'){
        human.setFillType();
    }
    if(!pdfFlag && bgMode==1 && key == 'e'){
        human.stop();
    }
    if(!pdfFlag && bgMode==1 && key == 'r'){
        human.play();
    }
    
    /*--------------------------------------------------------------
     
     
     Gif
     
     
     --------------------------------------------------------------*/
    if(!pdfFlag && bgMode==2 && key == 'q') { gifs.setDraw(); }
    if(!pdfFlag && bgMode==2 && key == 'w') { gifs.stop(); }
    
    if(!pdfFlag && bgMode==2
       && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
        if( key == '1' ){ gifs.setPattern(1); }
        else if( key == '2'){ gifs.setPattern(2); }
        else if( key == '3'){ gifs.setPattern(3); }
        else if( key == '4'){ gifs.setPattern(4); }
        else if( key == '5'){ gifs.setPattern(5); }
        else if( key == '6'){ gifs.setPattern(6); }
        else if( key == '7'){ gifs.setPattern(7); }
        else if( key == '8'){ gifs.setPattern(8); }
        else if( key == '9'){ gifs.setPattern(9); }
        else if( key == '0'){ gifs.setPattern(0); }
    }
    
    if(!pdfFlag && bgMode==2 && key == OF_KEY_LEFT){
        gifs.addColumn(false);
    }else if(!pdfFlag && bgMode==2 && key == OF_KEY_RIGHT){
        gifs.addColumn(true);
    }
    
    if(!pdfFlag && bgMode==2 && key == OF_KEY_UP){
        gifs.addRow(true);
    }else if(!pdfFlag && bgMode==2 && key == OF_KEY_DOWN){
        gifs.addRow(false);
    }
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    if(!pdfFlag && bgMode==3
       && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
        if( key == '1' ){ tp.setImage(0); }
        else if( key == '2'){ tp.setImage(1); }
        else if( key == '3'){ tp.setImage(2); }
        else if( key == '4'){ tp.setImage(3); }
        else if( key == '5'){ tp.setImage(4); }
        else if( key == '6'){ tp.setImage(5); }
        else if( key == '7'){ tp.setImage(6); }
        else if( key == '8'){ tp.setImage(7); }
        else if( key == '9'){ tp.setImage(8); }
        else if( key == '0'){ tp.setImage(9); }
    }
    if(!pdfFlag && bgMode==3 && key == 'q'){
        tp.setMaxScale(false);
    }else if(!pdfFlag && bgMode==3 && key == 'w'){
        tp.setMaxScale(true);
    }else if(!pdfFlag && bgMode==3 && key == 'e'){
        tp.changeBackground();
    }else if(!pdfFlag && bgMode==3 && key == 'r'){
        tp.changeSoundEffect();
    }
    if(!pdfFlag && bgMode==3 && key == OF_KEY_LEFT){
        tp.setSpeed(true);
    }else if(!pdfFlag && bgMode==3 && key == OF_KEY_RIGHT){
        tp.setSpeed(false);
    }
    if(!pdfFlag && bgMode==3 && key == OF_KEY_UP){
        tp.setRange(true);
    }else if(!pdfFlag && bgMode==3 && key == OF_KEY_DOWN){
        tp.setRange(false);
    }
    
    /*--------------------------------------------------------------
     
     
     Locus
     
     
     --------------------------------------------------------------*/
    if(key == '-') locus.setAlpha(false);
    if(key == '=') locus.setAlpha(true);

    /*--------------------------------------------------------------
     
     
     Shader
     
     
     --------------------------------------------------------------*/
    if (key == 'a') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
    if (key == 's') myGlitch.setFx(OFXPOSTGLITCH_GLOW, true);
    if (key == 'd') myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
    if (key == 'f') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
    if (key == 'g') myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
    if (key == 'h') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, true);
    if (key == 'j') myGlitch.setFx(OFXPOSTGLITCH_NOISE, true);
    if (key == 'k') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
    if (key == 'l') myGlitch.setFx(OFXPOSTGLITCH_SWELL, true);
    if (key == ';') myGlitch.setFx(OFXPOSTGLITCH_INVERT, true);
    if (key == '\'') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == '\\') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, true);
    if (key == ']') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, true);
    if (key == '[') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, true);
    if (key == 'p') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, true);
    if (key == 'o') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, true);
    if (key == 'i') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, true);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_KIRAKIRA, true);
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    if(key == ' '){ pdfFlag = true; }
    
    if(pdfFlag && key == '`' ){ pdf.setPdfNum(1, true); }
    else if(pdfFlag && key == '1'){ pdf.setPdfNum(2, true); }
    else if(pdfFlag && key == '2'){ pdf.setPdfNum(3, true); }
    else if(pdfFlag && key == '3'){ pdf.setPdfNum(4, true); }
    else if(pdfFlag && key == '4'){ pdf.setPdfNum(5, true); }
    else if(pdfFlag && key == '5'){ pdf.setPdfNum(6, true); }
    else if(pdfFlag && key == '6'){ pdf.setPdfNum(7, true); }
    else if(pdfFlag && key == '7'){ pdf.setPdfNum(8, true); }
    else if(pdfFlag && key == '8'){ pdf.setPdfNum(9, true); }
    
    //pdfMode
    if(pdfFlag && key == '9' ){pdf.setDisplayOriginal();}
    if(pdfFlag && key == '0' ){pdf.setDisplayOutline();}
    if(pdfFlag && key == '-' ){pdf.setDisplayStep();}
    if(pdfFlag && key == '=' ){pdf.setRotatePattern();}
    
    //PDF Sound Limitation
    if(pdfFlag && key == OF_KEY_LEFT){
        pdf.setMaxSound(false);
    }else if(pdfFlag && key == OF_KEY_RIGHT){
        pdf.setMaxSound(true);
    }
    
    //PDF Max Expand Rate
    if(pdfFlag && key == OF_KEY_UP){
        pdf.setMaxSize(true);
    }else if(pdfFlag && key == OF_KEY_DOWN){
        pdf.setMaxSize(false);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    /*--------------------------------------------------------------
     
     
     Shader
     
     
     --------------------------------------------------------------*/
    if (key == 'a') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
    if (key == 's') myGlitch.setFx(OFXPOSTGLITCH_GLOW, false);
    if (key == 'd') myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
    if (key == 'f') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
    if (key == 'g') myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
    if (key == 'h') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, false);
    if (key == 'j') myGlitch.setFx(OFXPOSTGLITCH_NOISE, false);
    if (key == 'k') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
    if (key == 'l') myGlitch.setFx(OFXPOSTGLITCH_SWELL, false);
    if (key == ';') myGlitch.setFx(OFXPOSTGLITCH_INVERT, false);
    if (key == '\'') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == '\\') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, false);
    if (key == ']') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, false);
    if (key == '[') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, false);
    if (key == 'p') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, false);
    if (key == 'o') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, false);
    if (key == 'i') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, false);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_KIRAKIRA, false);
    
    /*--------------------------------------------------------------
     
     
     PDF
     
     
     --------------------------------------------------------------*/
    if(key == ' '){ pdfFlag = false; }
    if(pdfFlag && key == '`' ){ pdf.setPdfNum(1, false); }
    else if(pdfFlag && key == '1'){ pdf.setPdfNum(2, false); }
    else if(pdfFlag && key == '2'){ pdf.setPdfNum(3, false); }
    else if(pdfFlag && key == '3'){ pdf.setPdfNum(4, false); }
    else if(pdfFlag && key == '4'){ pdf.setPdfNum(5, false); }
    else if(pdfFlag && key == '5'){ pdf.setPdfNum(6, false); }
    else if(pdfFlag && key == '6'){ pdf.setPdfNum(7, false); }
    else if(pdfFlag && key == '7'){ pdf.setPdfNum(8, false); }
    else if(pdfFlag && key == '8'){ pdf.setPdfNum(9, false); }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}