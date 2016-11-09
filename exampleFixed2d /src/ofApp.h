#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    
    
    void setup();
    void update();
    void draw();

    void setupGui();
    
    void drawScene();
    void drawHelp();
    
    void keyPressed(int key);
    
    // scene stuff
    ofxPostProcessing post;
    
    ofxPanel gui;
    ofParameter<int> offset;


    
};
