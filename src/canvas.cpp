#include "canvas.h"
#include <math.h>

const ofColor Canvas::kEmptyColor = ofColor(255, 255, 255, 1); // Empty space color, white
const ofColor Canvas::kWallColor = ofColor(100, 100, 100, 1); // Wall color, gray
const ofColor Canvas::kFruitColor = ofColor(255, 0, 0, 1); // Fruit color, bright red
const ofColor Canvas::kEndColor = ofColor(0, 255, 0, 1); // End color, bright green
const ofColor Canvas::kStartColor = ofColor(200, 0, 100); // Start color, dark red
const ofColor Canvas::kPlayerColor = ofColor(0, 100, 255, 1); // Player color, cyan
const ofColor Canvas::kTileColor = ofColor(120, 0, 25, 0.5); // Tiling color, brown

void Canvas::setup() {
    maze_.setup();
    image_pixels_.allocate(kCameraWidth, kCameraHeight, OF_IMAGE_COLOR);
    background_color_.set(0, 0, 0, 1);

    setFieldOfView(maze_.getFov());

    // Sets background color
    image_pixels_.setColor(background_color_);
}

void Canvas::setFieldOfView(double fov) {
    // Set smallest fov size
    if (fov < kSmallestFov) {
        fov = kSmallestFov;
    }

    fov_ = fov;
    fov_rel_points_.clear();

    // Edge where size of fov is only 1
    if (fov == 1) {
        ofPoint rel_point(0, 0);
        fov_rel_points_.push_back(rel_point);
        return;
    }

    // Reduce size by 1 for circle process (fov of 1 should yield single point)
    fov -= 1;

    // Fill FOV relative points
    for (int rel_x = -1 * fov; rel_x <= fov; rel_x++) {
        int y_width = sqrt(pow(fov, 2) - pow(rel_x, 2));
        for (int rel_y = -1 * y_width; rel_y <= y_width; rel_y++) {
            ofPoint rel_point(rel_x, rel_y);
            fov_rel_points_.push_back(rel_point);
        }
    }
}

// Draw at a specified point
void Canvas::updatePosition(const ofPoint &point) {
    int maze_block_width = kCameraWidth / maze_.getWidth();
    int maze_block_height = kCameraHeight / maze_.getHeight();

    maze_.move(point.y / maze_block_width, point.x / maze_block_width);

    if (!maze_.isUserAlive()) {
        image_pixels_.setColor(kEmptyColor);

        // Drawing start box
        for (int start_x = 0; start_x < maze_block_width; start_x++) {
            for (int start_y = 0; start_y < maze_block_height; start_y++) {
                int x_pixel_pos = start_x + maze_.getStartColumn() * maze_block_width;
                int y_pixel_pos = start_y + maze_.getStartRow() * maze_block_height;
                setPixelColor(x_pixel_pos, y_pixel_pos, kStartColor);
            }
        }

        // Drawing player
        for (int rel_x = -3; rel_x <= 3; rel_x++) {
            for (int rel_y = -3; rel_y <= 3; rel_y++) {
                setPixelColor(point.x + rel_x, point.y + rel_y, kPlayerColor);
            }
        }
        return;
    }

    image_pixels_.setColor(background_color_);

    for (ofPoint rel_point : fov_rel_points_) {
        int pos_x = rel_point.x + point.x;
        int pos_y = rel_point.y + point.y;

        // Make sure point is on screen
        if (pos_x < 0 || pos_x >= kCameraWidth || pos_y < 0 || pos_y >= kCameraHeight) {
            continue;
        }

        // Determining the position on the maze which the pixel maps to
        int maze_column = pos_x / maze_block_width;
        int maze_row = pos_y / maze_block_height;

        // Drawing maze walls
        if (maze_.getItemAt(maze_row, maze_column) == MazePiece::kMazeWall) {
            setPixelColor(pos_x, pos_y, kWallColor);
            continue;
        }

        // Drawing player
        if (fabs(pos_x - point.x) <= 3 && fabs(pos_y - point.y) <= 3) {
            setPixelColor(pos_x, pos_y, kPlayerColor);
            continue;
        }

        // Drawing maze tiles
        if (pos_x % kTileSpacingPx == 0 || pos_y % kTileSpacingPx == 0) {
            setPixelColor(pos_x, pos_y, kTileColor);
            continue;
        }

        // Draw empty space
        setPixelColor(pos_x, pos_y, kEmptyColor);
    }
}

// Allows setting a pixel color from a constant color object. Sets to canvas pixels.
void Canvas::setPixelColor(int x, int y, const ofColor &color) {
    image_pixels_.setColor(x, y, ofColor(color.r, color.g, color.b, color.a));
}

void Canvas::display(ofxCvColorImage &image) {
    image.setFromPixels(image_pixels_);
}