#include "canvas.h"
#include <math.h>

void Canvas::setup() {
    image_pixels_.allocate(kCameraWidth, kCameraHeight, OF_IMAGE_COLOR);

    setBrushSize(1);

    // Sets background color
    ofColor background_color(255, 255, 255, 1);
    image_pixels_.setColor(background_color);
}

void Canvas::setBrushSize(int brush_size) {
    // Set smallest brush size
    if (brush_size < kSmallestBrushSize) {
        brush_size = kSmallestBrushSize;
    }

    brush_size_ = brush_size;
    brush_rel_points_.clear();

    // Edge where size of brush is only 1
    if (brush_size == 1) {
        ofPoint rel_point(0, 0);
        brush_rel_points_.push_back(rel_point);
        return;
    }

    // Reduce size by 1 for circle process (brush_size of 1 should yield single point)
    brush_size -= 1;

    // Fill brush relative points
    for (int rel_x = -1 * brush_size; rel_x <= brush_size; rel_x++) {
        int y_width = sqrt(pow(brush_size, 2) - pow(rel_x, 2));
        for (int rel_y = -1 * y_width; rel_y <= y_width; rel_y++) {
            ofPoint rel_point(rel_x, rel_y);
            brush_rel_points_.push_back(rel_point);
        }
    }
}

// Draw at a specified point
void Canvas::draw(const ofPoint &point, const ofColor &color) {
    for (ofPoint rel_point : brush_rel_points_) {
        int pos_x = rel_point.x + point.x;
        int pos_y = rel_point.y + point.y;

        // Make sure point is on screen
        if (pos_x < 0 || pos_x >= kCameraWidth || pos_y < 0 || pos_y >= kCameraHeight) {
            continue;
        }

        image_pixels_.setColor(pos_x, pos_y, color);
    }
}

void Canvas::display(ofxCvColorImage &image) {
    image.setFromPixels(image_pixels_);
}