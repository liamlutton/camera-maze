#include "pen-viewer.h"

void PenViewer::setup() {
    setupCamera();
}

void PenViewer::setupCamera() {
    camera_.setup(kCameraWidth, kCameraHeight);
}

void PenViewer::update() {
    camera_.update();
    if (camera_.isFrameNew()) {
        // Process image for display
    }
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}