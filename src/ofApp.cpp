#include "ofApp.h"

//--------------------------------------------------------------
void ofFingerPaint::setup(){
    pen_viewer_.setup();
}

//--------------------------------------------------------------
void ofFingerPaint::update(){
    pen_viewer_.update();
}

//--------------------------------------------------------------
void ofFingerPaint::draw(){
    ofxCvColorImage image = pen_viewer_.getDisplayImage();
    if (image.bAllocated) {
        image.draw(image_x_ + image.getWidth(), image_y_, -1 * PenViewer::kCameraWidth, PenViewer::kCameraHeight);
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
