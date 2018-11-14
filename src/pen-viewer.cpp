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
        image_loaded_ = true;

        // Process image for display
        ofPixels pixels;
        camera_.getTexture().readToPixels(pixels);
        current_image_.setFromPixels(pixels);
    }
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}

ofImage PenViewer::getCurrentImage() const {
    return current_image_;
}

bool PenViewer::isImageLoaded() {
    return image_loaded_;
}