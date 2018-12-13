#include "ofApp.h"


//--------------------------------------------------------------
void ofFingerPaint::setup(){
    pen_viewer_.Setup();
    ofSetBackgroundColor(ofColor(40, 40, 40));
}

//--------------------------------------------------------------
void ofFingerPaint::update(){
    pen_viewer_.Update();
}

//--------------------------------------------------------------
void ofFingerPaint::draw(){
    // Make sure display image is allocated
    if (!pen_viewer_.GetDisplayImage().bAllocated) {
        return;
    }

    ofxCvColorImage image = pen_viewer_.GetDisplayImage();
    image.draw(kImageX + image.getWidth(), kImageY, -1 * Canvas::kCameraWidth, Canvas::kCameraHeight);

    ofDrawBitmapString("Maps:", kMazeTextStartX, kMazeTextStartY);
    
    // Write in maps, completed ones colored special
    Canvas canvas = pen_viewer_.GetCanvas();
    int current_maze = canvas.GetCurrentMazeIndex();
    for (int i = 1; i <= canvas.GetMazes().size(); i++) {
        std::string text = std::to_string(i);
        if (i < current_maze + 1) {
            ofSetColor(ofColor(255, 255, 0)); // Sets to yellow
            text.append(" (COMPLETE)");
        }
        ofDrawBitmapString(text, kMazeTextStartX, kMazeTextStartY + kMazeTextSpacing * i);
        ofSetColor(ofColor(255, 255, 255)); // Resets color
    }
}

//--------------------------------------------------------------
void ofFingerPaint::keyPressed(int key){

}

//--------------------------------------------------------------
void ofFingerPaint::keyReleased(int key){

}

//--------------------------------------------------------------
void ofFingerPaint::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofFingerPaint::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofFingerPaint::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofFingerPaint::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofFingerPaint::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofFingerPaint::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofFingerPaint::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofFingerPaint::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofFingerPaint::dragEvent(ofDragInfo dragInfo){ 

}
