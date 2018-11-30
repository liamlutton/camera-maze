#include "canvas.h"

void Canvas::setup() {
    pixels.allocate(kCameraWidth, kCameraHeight, OF_IMAGE_COLOR);
}

void Canvas::draw(const ofPoint &point, const ofColor &color) {
    pixels.setColor(point.x, point.y, color);
}

void Canvas::display(ofxCvColorImage &image) {
    image.setFromPixels(pixels);
}