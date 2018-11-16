#include "pen-viewer.h"

void PenViewer::setup() {
    setupCamera();
    current_image_.allocate(kCameraWidth, kCameraHeight);
}

void PenViewer::setupCamera() {
    camera_.setup(kCameraWidth, kCameraHeight);
}

void PenViewer::update() {
    camera_.update();

    if (camera_.isFrameNew()) {
        // If current is already set, setup previous
        if (current_image_.bAllocated) {
            prev_image_ = current_image_;
        }

        // Sets current image
        ofPixels pixels;
        camera_.getTexture().readToPixels(pixels);
        current_image_.setFromPixels(pixels);

        processImage();
    }
}

void PenViewer::processImage() {
    // Both current and previous image must be allocated
    if (!prev_image_.bAllocated || !current_image_.bAllocated) {
        return;
    }
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}

ofxCvColorImage PenViewer::getDisplayImage() const {
    return display_image_;
}

ofxCvColorImage PenViewer::getCurrentImage() const {
    return current_image_;
}