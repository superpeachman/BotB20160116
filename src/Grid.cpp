//
//  Grid.cpp
//  
//
//  Created by 桃田稔也 on 1/2/16.
//
//

#include "Grid.h"
void Grid::init(int _paneSize, ofImage &_image){
    paneSize = _paneSize;
    panes.clear();
    
    float imgHeight = (float)_image.getHeight()/(float)paneSize;
    float imgWidth = (float)_image.getWidth()/(float)paneSize;

    for(int h=0;h<imgHeight;h++){
        for(int w=0;w<imgWidth;w++){
            ofColor c = _image.getColor(w*paneSize, h*paneSize);
            
            //If there is nothing, add panel
            if(org.a != c.a){
                //printf("c.r:%i, c.g:%i, c.b:%i, c.a:%i \n",c.r,c.g,c.b,c.a);
                //cout << "w:" << w << " h:" << h << " c.r:"<< c.r << " c.g:" << c.g << " c.b:"<< c.b << "\n";
                pane.init(w*paneSize, h*paneSize, paneSize, c);
                panes.push_back(pane);
            }
        }
    }
    /*
    //Swap Panels
    int randomNum = ofRandom(panes.size());
    for(int i = 0; i < panes.size(); i++){
        Pane temp = panes[i];
        panes[i] = panes[randomNum];
        panes[randomNum] = temp;
    }
     */
}
void Grid::draw(){
    for(int i=0;i<panes.size();i++){
        panes[i].draw();
    }
}
void Grid::drawByIndex(int index){
    //panes.get(index).draw();
}
int Grid::getIndex(int _x,int _y){
    //return (width/pSize)*(_y/pSize) + (_x/pSize);
}
int Grid::getXByIndex(int index){
    return panes[index]._x;
}
int Grid::getYByIndex(int index){
    return panes[index]._y;
}
ofColor Grid::getPanelColor(int index){
    return panes[index]._c;
}
int Grid::getPanelNumber(){
    return panes.size();
}
int Grid::getPanelSize(){
    return paneSize;
}