#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(){
	ofSetupOpenGL(1280 + 100, 720, OF_WINDOW);

	ofRunApp(new ofFingerPaint());
}
