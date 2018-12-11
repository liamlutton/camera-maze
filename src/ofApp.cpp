#include "ofApp.h"

//--------------------------------------------------------------
void ofFingerPaint::setup(){
    pen_viewer_.Setup();
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

    ofDrawBitmapString("Maps:", 10, 10);
    
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
