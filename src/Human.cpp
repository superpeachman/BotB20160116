//
//  Human.cpp
//  
//
//  Created by 桃田稔也 on 11/9/15.
//
//

#include "Human.h"

void Human::setup(int _fft_size){
    fft_size = _fft_size;

    openNIDevice.setup();
    //openNIDevice.setResolution(640, 480, 30);
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    //openNIDevice.addUserGenerator();
    
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    //openNIDevice.setUseDepthRawPixels(true);
    //openNIDevice.setUseMaskPixelsAllUsers(true);
    //openNIDevice.setMaxNumUsers(3);
    
    openNIDevice.start();
    //openNIDevice.getDepthGenerator().GetAlternativeViewPointCap().SetViewPoint(openNIDevice.getImageGenerator());
    
    mode = 1;
    
    width = ofGetWidth();
    height = ofGetHeight();
    //kinectW = openNIDevice.getWidth();
    //kinectH = openNIDevice.getHeight();
    kinectW = 640;
    kinectH = 480;
    
    currentRow = 0;
    minDis = 500;
    maxDis = 3000;
    depthRate = 0.5f;
    
    numberOfLine = 48;
    meshes.resize(numberOfLine);
    pathes.resize(numberOfLine);
    
    grayImage.allocate(kinectW, kinectH);
    maskImage.allocate(kinectW, kinectH, OF_IMAGE_GRAYSCALE);
    
    if(ofGetWidth() < ofGetHeight()) displayRateFlag = true;
    if(displayRateFlag==false){
        //---->Normal Window
        if(ofGetWidth()>640){
            displayRate=(float)ofGetWidth()/(float)640;
        }else{
            displayRate=(float)640/(float)ofGetWidth();
        }
    }else{
        //---->Vertically Window
        if(ofGetHeight()>480){
            displayRate=(float)ofGetHeight()/(float)480;
        }else{
            displayRate=(float)480/(float)ofGetHeight();
        }
    }
}

void Human::update(float _min, float _max, float _depth){
    /*--------------------------------------------------------------
     
     
     Update Kinect Distance & Depth Rate
     
     
     --------------------------------------------------------------*/
    minDis = _min;
    maxDis = _max;
    depthRate = _depth;
    
    /*--------------------------------------------------------------
     
     
     Check Display Size
     
     
     --------------------------------------------------------------*/
    width = ofGetWidth();
    height = ofGetHeight();
    
    
    if (mode == 1) {
        /*--------------------------------------------------------------
         
         
         Resize Vector
         
         
         --------------------------------------------------------------*/
        meshes.resize(numberOfLine);
        pathes.resize(numberOfLine);
        
        openNIDevice.update();
        
        //if(openNIDevice.isNewFrame()){
            ofPixels openNIDevicePixel = openNIDevice.getImagePixels();
            unsigned short *depthData = openNIDevice.getDepthRawPixels().getPixels();
            
            /*--------------------------------------------------------------
             
             
             Clear Vector
             
             
             --------------------------------------------------------------*/
            for (int i=0; i<meshes.size(); i++) { meshes[i].clear(); }
            for (int i=0; i<pathes.size(); i++) { pathes[i].clear(); }
            
            /*--------------------------------------------------------------
             
             
             Check Display Size
             
             
             --------------------------------------------------------------*/
            //Gap of Line
            float targetY = (float)kinectH/(float)numberOfLine;
            
            //Line's Height Positon
            int tempY = 0;
            
            //printf("numberOfLine: %i targetY: %f \n", numberOfLine, targetY);
            
            for (int y=0; y<numberOfLine; y++) {
                tempY = targetY*y;
                
                for (int x=0; x<kinectW; x++) {
                    
                    //Target Depth
                    int tempVal = round(x+kinectW*tempY);
                    
                    if(tempVal < openNIDevicePixel.size()){
                        float r = openNIDevicePixel.getColor(x, tempY).r;
                        float g = openNIDevicePixel.getColor(x, tempY).g;
                        float b = openNIDevicePixel.getColor(x, tempY).b;
                        r = ofMap(r, 0, 255, 0.0, 1.0);
                        g = ofMap(g, 0, 255, 0.0, 1.0);
                        b = ofMap(b, 0, 255, 0.0, 1.0);
                        
                        float depthVal = depthData[tempVal];
                        
                        if (depthData[tempVal]<maxDis && depthData[tempVal]>minDis) { depthVal = maxDis - depthVal; }
                        else{ depthVal = 0; }
                        
                        depthVal *= depthRate;
                        
                        if (tempY<kinectH) {
                            meshes[y].addVertex(ofPoint(x,tempY,depthVal));
                            //meshes[y].addColor(ofFloatColor(1.0,0.0,0.0));
                            meshes[y].addColor(ofFloatColor(r,g,b));
                        }else{
                            meshes[y].addVertex(ofPoint(x,kinectH,depthVal));
                            //meshes[y].addColor(ofFloatColor(1.0,0.0,0.0));
                            meshes[y].addColor(ofFloatColor(r,g,b));
                        }
                    }
                }//Detect Each Depth
            }//Each Line
        //}
    }else if(mode == 2){
        openNIDevice.update();
        
        //if(openNIDevice.isNewFrame()){
            /*--------------------------------------------------------------
             
             
             Clear Images
             
             
             --------------------------------------------------------------*/
            maskImage.clear();
            grayImage.clear();
            
            maskImage.allocate(kinectW, kinectH, OF_IMAGE_COLOR_ALPHA);
            grayImage.allocate(kinectW, kinectH);
            
            ofPixels openNIDevicePixel = openNIDevice.getImagePixels();
            unsigned short *depthData = openNIDevice.getDepthRawPixels().getPixels();
            
            //Make Mask Image
            for (int i = 0; i<kinectW*kinectH; i++) {
                int x = i % kinectW;
                int y = i / kinectW;
                
                //printf("i: %i, openNIDevicePixel.size(): %i,  depthData[i]: %f \n", i, openNIDevicePixel.size(), depthData[i]);
                
                
                if (minDis <= depthData[i] && depthData[i] < maxDis){
                    maskImage.setColor(x, y, ofColor(255,0));
                }else{
                    maskImage.setColor(x, y, ofColor(0,255));
                }
            }
            maskImage.update();
        //}
        
    }else if(mode == 3){
        openNIDevice.update();
        
        //if(openNIDevice.isNewFrame()){
            /*--------------------------------------------------------------
             
             
             Clear Images
             
             
             --------------------------------------------------------------*/
            maskImage.clear();
            grayImage.clear();

            maskImage.allocate(kinectW, kinectH, OF_IMAGE_GRAYSCALE);
            grayImage.allocate(kinectW, kinectH);
            
            ofPixels openNIDevicePixel = openNIDevice.getImagePixels();
            unsigned short *depthData = openNIDevice.getDepthRawPixels().getPixels();
            
            //Make Mask Image
            for (int i = 0; i<kinectW*kinectH; i++) {
                int x = i % kinectW;
                int y = i / kinectW;
                
                //printf("i: %i, openNIDevicePixel.size(): %i,  depthData[i]: %f \n", i, openNIDevicePixel.size(), depthData[i]);

                
                if (minDis <= depthData[i] && depthData[i] < maxDis){
                    maskImage.setColor(x, y, ofColor(255));
                }else{
                    maskImage.setColor(x, y, ofColor(0));
                }
            }
            maskImage.update();
            maskImage.mirror(false, true);
            
            grayImage.setFromPixels(maskImage);
            grayImage.threshold(20);
            grayImage.flagImageChanged();
            contourFinder.findContours(grayImage, 25, (kinectW*kinectH), 10, false, false);
            
            ofPoint center = ofPoint(ofGetWidth()/2, ofGetHeight());
            
            if(contourFinder.blobs.size()>0){
                //cout << contourFinder.blobs.size() << "\n";
                humanShapes.clear();
                humanShapes.resize(contourFinder.blobs.size());
                
                for (int i = 0; i < contourFinder.blobs.size(); i++){
                    bool even = false;
                    
                    //cout << contourFinder.blobs[0].nPts << "\n";
                    
                    for (int j = 0; j < contourFinder.blobs[0].nPts; j+=15){
                        float tempY=0;
                        float tempX=0;
                        
                        if(displayRateFlag==false){
                            //---->Normal Window
                            tempY=ofMap(contourFinder.blobs[0].pts[j].y, 0, 480, -100, ofGetHeight()+100);
                            tempX=ofGetWidth() - ofMap(contourFinder.blobs[0].pts[j].x, 0, 640, -100, ofGetWidth()+100);
                        }else{
                            //---->Vertically Window
                            tempX=ofMap(contourFinder.blobs[0].pts[j].x, 0, 640, -100, ofGetWidth()+100);
                            tempY=ofMap(contourFinder.blobs[0].pts[j].y, 0, 480, -100, ofGetHeight()*displayRate+100);
                        }
                        
                        if(musicFlag == false){
                            //tempX = abs(floor(tempX));
                            //tempY = abs(floor(tempY));
                            
                            //cout << tempX << " " << tempY << "\n";
                            
                            //pts.push_back(ofPoint(tempX, tempY));
                            humanShapes[0].addVertex(tempX, tempY);
                        }else{
                            //even=false;
                            ofPoint target = ofPoint(tempX, tempY);
                            ofPoint current = target;
                            humanShapes[0].addVertex(tempX, tempY);
                            
                            /*
                            if(tempX<center.x){
                                if(tempY<center.y){
                                    if(even){
                                        target=(target-center).normalize()*_soundL*figureAffect;
                                        target=target+current;
                                        //target=-target;
                                        even=!even;
                                    }else{
                                        target=(target-center).normalize()*-_soundR*figureAffect;
                                        //target=-target;
                                        target=target+current;
                                        even=!even;
                                    }
                                }else{
                                    if(even){
                                        target=(target-center).normalize()*_soundL*figureAffect;
                                        //target.x=-target.x;
                                        target=target+current;
                                        even=!even;
                                    }else{
                                        target=(target-center).normalize()*-_soundR*figureAffect;
                                        //target.x=-target.x;
                                        target=target+current;
                                        even=!even;
                                    }
                                }
                            }else{
                                if(tempY<center.y){
                                    if(even){
                                        target=(target-center).normalize()*_soundL*figureAffect;
                                        //target.y=-target.y;
                                        target=target+current;
                                        even=!even;
                                    }else{
                                        target=(target-center).normalize()*-_soundR*figureAffect;
                                        //target.y=-target.y;
                                        target=target+current;
                                        even=!even;
                                    }
                                }else{
                                    if(even){
                                        target=(target-center).normalize()*_soundL*figureAffect;
                                        target=target+current;
                                        even=!even;
                                    }else{
                                        target=(target-center).normalize()*-_soundR*figureAffect;
                                        target=target+current;
                                        even=!even;
                                    }
                                }
                            }
                            shapes[0].addVertex(target);
                             */
                        }
                    }
                }
                /*
                shared_ptr<ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
                edge->addVertices(shapes[0].getVertices());
                edge->setPhysics(5.0, 0.1, 0.3);
                edge->create(box2d.getWorld());
                edge->updateShape();
                polyEdges.push_back(edge);
                 */
            }
        //}
        

    
    }
}

void Human::draw(){
    
    if(displayFlag == false) return;
    
    if(mode == 1){
        ofEnableDepthTest();
        ofEnableSmoothing();
        
        //ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
        
        ofPushMatrix();
        ofPushStyle();
        
        ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
        float tempScale = (float)width/(float)kinectW*1.2;
        ofScale(tempScale, tempScale);
        float time = ofGetElapsedTimef();
        float angle = time * 20;
        //ofRotate( angle, 0, 1, 0 );
        
        int centerMesh = round((float)numberOfLine/(float)2);
        ofTranslate((meshes[centerMesh].getCentroid())*-1);
        
        //printf("numberOfLine: %i centerMesh: %i \n", numberOfLine, centerMesh);
        
        //mesh.draw();
        for (int i=0; i<numberOfLine; i++) {
            pathes[i].setStrokeColor(ofColor(255, 0, 0));
            pathes[i].setFillColor(ofColor(255, 0, 0));
            pathes[i].setFilled(fillType);
            pathes[i].setStrokeWidth(1);
            pathes[i].moveTo(meshes[i].getVertex(0));
            
            //printf("1 i: %i \n", i);
            
            for (int j=1; j<meshes[i].getNumVertices(); j++) { pathes[i].lineTo(meshes[i].getVertex(j)); }
            pathes[i].draw();
            pathes[i].close();
        }
        
        ofPopStyle();
        ofPopMatrix();
        
        ofDisableSmoothing();
        ofDisableDepthTest();
    }else if(mode == 2){
        ofPushStyle();
        ofSetColor(255);
        maskImage.draw(ofPoint(0,0), width, height);
        ofPopStyle();
    }else if(mode == 3){
        //contourFinder.ofBaseDraws::draw(ofPoint(0,0), kinectW, kinectH);
        
        for (int k = 0; k < humanShapes.size(); k++){
            ofPolyline poly = humanShapes[k];
            
            poly = poly.getResampledByCount(100);
            
            ofSetColor(255, 100, 100);
            
            poly.setClosed(true);
            poly.draw();
        }
    
    }
}
void Human::debugDraw(){
    openNIDevice.drawDebug(10, ofGetHeight() - 320, 640, 240);
    /*
    cout << "openNIDevice.isContextReady()" << openNIDevice.isContextReady() << '\n';
    cout << "openNIDevice.isImageOn()" << openNIDevice.isImageOn() << '\n';
    cout << "openNIDevice.isPaused()" << openNIDevice.isPaused() << '\n';
    cout << "openNIDevice.isDepthOn()" << openNIDevice.isDepthOn() << '\n';
    cout << "openNIDevice.isNewFrame()" << openNIDevice.isNewFrame() << '\n';
    cout << "openNIDevice.isThreadRunning()" << openNIDevice.isThreadRunning() << '\n';
    cout << "openNIDevice.isMainThread()" << openNIDevice.isMainThread() << '\n';
    cout << "openNIDevice.getThreadId()" << openNIDevice.getThreadId() << '\n';
    cout << "openNIDevice.getIsONIDone()" << openNIDevice.getIsONIDone() << '\n';
     */
}
//--------------------------------------------------------------
void Human::userEvent(ofxOpenNIUserEvent & event){
// show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void Human::handEvent(ofxOpenNIHandEvent & event){
// show hand event messages in the console
    ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;
}
void Human::setNumberOfLine(bool _dir){
    if (_dir == true) {
        numberOfLine += 1;
    }else{
        numberOfLine -= 1;
        if (numberOfLine<1) numberOfLine = 1;
    }
}

void Human::setFillType(){
    fillType = !fillType;
}

void Human::setDraw(){
    displayFlag = !displayFlag;
}

void Human::setMode(int _mode){
    mode = _mode;
}

void Human::stop(){
    openNIDevice.waitForThread();
    //openNIDevice.stop();
}

void Human::play(){
    if(!openNIDevice.isThreadRunning()){
        openNIDevice.setup();
        openNIDevice.addImageGenerator();
        openNIDevice.addDepthGenerator();
        //openNIDevice.addUserGenerator();
        
        openNIDevice.setRegister(true);
        openNIDevice.setMirror(true);
        openNIDevice.setUseDepthRawPixels(true);
        //openNIDevice.setUseMaskPixelsAllUsers(true);
        //openNIDevice.setMaxNumUsers(3);
        
        //openNIDevice.waitForThread();
        //openNIDevice.start();
        openNIDevice.startThread();
    }else{
        //openNIDevice.startThread();
        //openNIDevice.start();
        openNIDevice.startThread();
    }
}

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void setNormals( ofMesh &mesh ){
    
    int nV = mesh.getNumVertices();//640
    int nT = mesh.getNumIndices() / 3;//213
    
    vector<ofPoint> norm( nV );
    
    for (int t=0; t<nT; t++) {
        
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 641 );
        
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}