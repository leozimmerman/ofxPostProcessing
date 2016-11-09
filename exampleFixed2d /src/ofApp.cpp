#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(0);
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    
    post.init(ofGetWidth(), ofGetHeight());

    
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    
    post.createPass<ContrastPass>()->setEnabled(false);
    post.createPass<ConvolutionPass>()->setEnabled(false);
    post.createPass<DofAltPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    //post.createPass<HsbShiftPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<LimbDarkeningPass>()->setEnabled(false);
    post.createPass<LUTPass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(false);
    post.createPass<SSAOPass>()->setEnabled(false);
    post.createPass<ToonPass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    
    
    setupGui();
    
    
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
    
   // post.debugDraw();
    
//    glPopAttrib();
    
    drawHelp();
    gui.draw();
    
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
    
    idx += offset;
    
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
}
//--------------------------------------
void ofApp::setupGui(){

    gui.setup();
    gui.add( offset.set("key offset", 0, 0, 20));


}
