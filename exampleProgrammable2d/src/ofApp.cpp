#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(0);
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);///????
    
    post.init(ofGetWidth(), ofGetHeight());

    post.createPass<PixelatePass>()->setEnabled(false);
    
    
    
}
//--------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}
//--------------------------------------
void ofApp::draw(){
    
//    glPushAttrib(GL_ENABLE_BIT);
    
    
    post.begin();
    
    drawScene();

    post.end();
    
    post.debugDraw();
    
    
//    glPopAttrib();
    
    drawHelp();
    
}

//--------------------------------------
void ofApp::drawScene(){
    
    ofPushStyle();
    
    ofSetColor(ofColor::cyan);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 150);
    
    ofPopStyle();
    

}
//--------------------------------------
void ofApp::drawHelp(){
    
    ofPushStyle();
    
    ofSetColor(255);
    
    ofDrawBitmapString("Is Programmable: " + ofToString(ofIsGLProgrammableRenderer()), 10, 20);
    
    for (unsigned i = 0; i < post.size(); ++i){
        if (post[i]->getEnabled()) ofSetColor(0, 255, 255);
        else ofSetColor(255, 0, 0);
        ostringstream oss;
        oss << i << ": " << post[i]->getName() << (post[i]->getEnabled()?" (on)":" (off)");
        
        ofDrawBitmapString(oss.str(), 10, 30 * (i + 2));
    }
    
    
    ofPopStyle();
}
//--------------------------------------
void ofApp::keyPressed(int key){
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
}
