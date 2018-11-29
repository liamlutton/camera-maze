#include "pen-viewer.h"

void PenViewer::setup() {
    setupCamera();
    current_image_.allocate(kCameraWidth, kCameraHeight);
}

void PenViewer::setupCamera() {
    camera_.setup(kCameraWidth, kCameraHeight);
}

void PenViewer::loadColorPixelImages(const ofPixels &image_pixels) {

    // Move this
    if (!red_blob_image_.bAllocated || !green_blob_image_.bAllocated || !blue_blob_image_.bAllocated) {
        red_blob_image_.allocate(kCameraWidth, kCameraHeight);
        green_blob_image_.allocate(kCameraWidth, kCameraHeight);
        blue_blob_image_.allocate(kCameraWidth, kCameraHeight);
    }

    int added_value = 50;

    ofPixels red_blob_pixels = image_pixels;
    ofPixels green_blob_pixels = image_pixels;
    ofPixels blue_blob_pixels = image_pixels;

    ofColor black;
    black.set(0, 0, 0);

    red_blob_pixels.setColor(black);
    green_blob_pixels.setColor(black);
    blue_blob_pixels.setColor(black);

    for (int x = 0; x < kCameraWidth; x++) {
        for (int y = 0; y < kCameraHeight; y++) {
            ofColor color = image_pixels.getColor(x, y);

            // Possibly clean this code up
            if (color.r > color.b + color.g + added_value) {
                color.set(255, 255, 255, 0);
                red_blob_pixels.setColor(x, y, color);
            } else if (color.b > color.r + color.g + added_value) {
                color.set(255, 255, 255, 0);
                blue_blob_pixels.setColor(x, y, color);
            } else if (color.g > color.b + color.r) {
                color.set(255, 255, 255, 0);
                green_blob_pixels.setColor(x, y, color);
            }
        }
    }

    red_blob_image_.setFromPixels(red_blob_pixels);
    green_blob_image_.setFromPixels(green_blob_pixels);
    blue_blob_image_.setFromPixels(blue_blob_pixels);
}

void PenViewer::update() {
    camera_.update();

    if (camera_.isFrameNew()) {
        // Sets current image
        ofPixels image_pixels;
        camera_.getTexture().readToPixels(image_pixels);

        if (image_pixels.size() == 0) {
            return;
        }

        // Blur pixels to remove noise
        ofxCvColorImage current_frame_image;
        current_frame_image.allocate(kCameraWidth, kCameraHeight);
        current_frame_image.setFromPixels(image_pixels);
        current_frame_image.blurGaussian(7);

        image_pixels = current_frame_image.getPixels();

        loadColorPixelImages(image_pixels);

        // All for testing
        current_image_ = red_blob_image_;
        // current_image_ = current_frame_image;

        processImage();
    }
}

void PenViewer::processImage() {
    // Both current and previous image must be allocated
    if (!current_image_.bAllocated) {
        return;
    }
    
    // Ensure that the colored blob images are allocated
    if (!red_blob_image_.bAllocated || !green_blob_image_.bAllocated || !blue_blob_image_.bAllocated) {
        return;
    }

    ofxCvGrayscaleImage red_binary;
    red_binary.allocate(red_blob_image_.width, red_blob_image_.height);
    red_binary.setFromColorImage(red_blob_image_);
    red_binary.threshold(40);

    display_image_ = current_image_;
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}

ofxCvColorImage PenViewer::getDisplayImage() const {
    // return red_blob_image_;
    return display_image_;
}

ofxCvColorImage PenViewer::getCurrentImage() const {
    return current_image_;
}