#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
    
    //------------------------------
    
//    ofGLWindowSettings settings;
//    settings.setGLVersion(3, 3);
//    ofCreateWindow(settings);
//    ofRunApp(new ofApp());

}
