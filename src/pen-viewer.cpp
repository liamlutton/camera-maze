#include "pen-viewer.h"

void PenViewer::setup() {
    setupCamera();
    current_image_.allocate(kCameraWidth, kCameraHeight);

    red_image_.allocate(kCameraWidth, kCameraHeight);
    green_image_.allocate(kCameraWidth, kCameraHeight);
    blue_image_.allocate(kCameraWidth, kCameraHeight);

    red_image_.set(255, 0, 0);
    green_image_.set(0, 255, 0);
    blue_image_.set(0, 0, 255);
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

        // Only accepts red pixels for testing
        for (int x = 0; x < kCameraWidth; x++) {
            for (int y = 0; y < kCameraHeight; y++) {
                ofColor color = pixels.getColor(x, y);
                if (color.r > color.b + color.g) {
                    color.set(255, 0, 0, 0);
                    pixels.setColor(x, y, color);
                }
            }
        }

        current_image_.setFromPixels(pixels);

        processImage();
    }
}

void PenViewer::processImage() {
    // Both current and previous image must be allocated
    if (!prev_image_.bAllocated || !current_image_.bAllocated) {
        return;
    }

    // current_image_ -= blue_image_;
    // current_image_ -= green_image_;

    // display_image_ = current_image_;

    // prev_image_ -= blue_image_;
    // prev_image_ -= green_image_;

    // Set display to change between iamges
    display_image_ = current_image_;
    // display_image_ -= prev_image_;

    // gray_product_ = display_image_;
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}

ofxCvColorImage PenViewer::getDisplayImage() const {
    return display_image_;
    // return d;
}

ofxCvColorImage PenViewer::getCurrentImage() const {
    return current_image_;
}