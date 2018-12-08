#include "pen-viewer.h"

void PenViewer::setup() {
    setupCamera();
    display_image_.allocate(Canvas::kCameraWidth, Canvas::kCameraHeight);
    canvas_.setup();
}

void PenViewer::setupCamera() {
    camera_.setup(Canvas::kCameraWidth, Canvas::kCameraHeight);
}

void PenViewer::loadColorPixelImages(const ofPixels &image_pixels) {
    if (!red_blob_image_.bAllocated) {
        red_blob_image_.allocate(Canvas::kCameraWidth, Canvas::kCameraHeight);
    }

    ofPixels red_blob_pixels;
    red_blob_pixels.allocate(image_pixels.getWidth(), image_pixels.getHeight(), OF_IMAGE_COLOR);
    red_blob_pixels.setColor(ofColor(0, 0, 0, 0));

    // Apply threshold to image for red pixels
    for (int x = 0; x < Canvas::kCameraWidth; x++) {
        for (int y = 0; y < Canvas::kCameraHeight; y++) {
            ofColor color = image_pixels.getColor(x, y);
            if (isPixelRed(color.r, color.g, color.b)) {
                red_blob_pixels.setColor(x, y, ofColor(255, 255, 255, 1));
            }
        }
    }
    red_blob_image_.setFromPixels(red_blob_pixels);
}

bool PenViewer::isPixelRed(int r, int g, int b) {
    // Red must be greater than both blue and green.
    // More selective based on color vibrancy constant.
    return r > g + b + kColorVibrancyConstant;
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
        current_frame_image.allocate(Canvas::kCameraWidth, Canvas::kCameraHeight);
        current_frame_image.setFromPixels(image_pixels);
        current_frame_image.blurGaussian(kGaussianBlur);

        image_pixels = current_frame_image.getPixels();

        loadColorPixelImages(image_pixels);
        processImage();
    }
}

void PenViewer::processImage() {
    // Ensure that the colored blob images are allocated
    if (!red_blob_image_.bAllocated) {
        return;
    }

    ofxCvGrayscaleImage red_binary;
    red_binary.allocate(red_blob_image_.width, red_blob_image_.height);
    red_binary.setFromColorImage(red_blob_image_);

    contour_finder_.findContours(red_binary, kSmallestBlobSize, kLargestBlobSize, 1, false);

    if (contour_finder_.blobs.size() == 1) {
        center_red_ = contour_finder_.blobs[0].centroid;
        canvas_.updatePosition(center_red_);
    }

    canvas_.display(display_image_);
}

Canvas PenViewer::getCanvas() const {
    return canvas_;
}

ofVideoGrabber PenViewer::getCamera() const {
    return camera_;
}

ofxCvColorImage PenViewer::getDisplayImage() const {
    return display_image_;
}