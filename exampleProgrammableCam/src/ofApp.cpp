#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(0);
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<FxaaPass>()->setEnabled(false);
    
    
    
    for (unsigned i = 0; i < NUM_BOXES; ++i){
        posns.push_back(ofVec3f(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300)));
        cols.push_back(ofColor::fromHsb(255 * i / (float)NUM_BOXES, 255, 255, 255));
    }
    boxMesh = ofMesh::box(20, 20, 20);
	light.setPosition(1000, 1000, 2000);
    
    
    
}
//--------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}
//--------------------------------------
void ofApp::draw(){
    
//    glPushAttrib(GL_ENABLE_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    
//    light.enable();
    
    
    //cam.begin();
    post.begin(cam);
        drawScene();
    //cam.end();
    post.end();
    
    
//    glPopAttrib();
    
    //post.debugDraw();
    
    drawHelp();
}
//--------------------------------------
void ofApp::drawScene(){
    
    for (unsigned i = 0; i < posns.size(); ++i){
    
        ofSetColor(cols[i]);
        ofPushMatrix();
        ofTranslate(posns[i]);
            boxMesh.draw();
        ofPopMatrix();
        
    }
    
    //ofDrawAxis(100);

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

void ofApp::keyPressed(int key)
{
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
}
