#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp
{
public:
    
    
    void setup();
    void update();
    void draw();

    void drawScene();
    void drawHelp();
    
    void keyPressed(int key);
    
    // scene stuff
    ofxPostProcessing post;

    
};
