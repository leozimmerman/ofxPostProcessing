#include "ofMain.h"
#include "ofApp.h"

int main( ){
    
    ofGLFWWindowSettings windowSettings;
    windowSettings.setGLVersion(3, 3);
    windowSettings.width = 1024;
    windowSettings.height = 768;
    windowSettings.windowMode = OF_WINDOW;
    ofCreateWindow(windowSettings);
    
    ofRunApp(new ofApp());
    
}
