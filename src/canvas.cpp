#include "canvas.h"
#include <math.h>

void Canvas::setup() {
    maze_.setup();
    image_pixels_.allocate(kCameraWidth, kCameraHeight, OF_IMAGE_COLOR);
    background_color_.set(0, 0, 0, 1);

    setFieldOfView(1);

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
void Canvas::draw(const ofPoint &point, const ofColor &color) {
    int maze_block_width = kCameraWidth / maze_.getWidth();
    int maze_block_height = kCameraHeight / maze_.getHeight();

    maze_.move(point.y / maze_block_width, point.x / maze_block_width);

    // Make these constants
    ofColor start_color(200, 0, 100);
    ofColor tile_color(120, 0, 25, 0.5);
    ofColor wall_color(100, 100, 100, 1);
    ofColor empty_color(255, 255, 255, 1);
    ofColor player_color(0, 100, 255, 1);

    if (!maze_.isUserAlive()) {
        image_pixels_.setColor(empty_color);

        // Drawing start box
        for (int start_x = 0; start_x < maze_block_width; start_x++) {
            for (int start_y = 0; start_y < maze_block_height; start_y++) {
                int x_pixel_pos = start_x + maze_.getStartColumn() * maze_block_width;
                int y_pixel_pos = start_y + maze_.getStartRow() * maze_block_height;
                image_pixels_.setColor(x_pixel_pos, y_pixel_pos, start_color);
            }
        }

        // Drawing player
        for (int rel_x = -3; rel_x <= 3; rel_x++) {
            for (int rel_y = -3; rel_y <= 3; rel_y++) {
                image_pixels_.setColor(point.x + rel_x, point.y + rel_y, player_color);
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
            image_pixels_.setColor(pos_x, pos_y, wall_color);
            continue;
        }

        // Drawing player
        if (fabs(pos_x - point.x) <= 3 && fabs(pos_y - point.y) <= 3) {
            image_pixels_.setColor(pos_x, pos_y, player_color);
            continue;
        }

        // Drawing maze tiles
        if (pos_x % kTileSpacingPx == 0 || pos_y % kTileSpacingPx == 0) {
            image_pixels_.setColor(pos_x, pos_y, tile_color);
            continue;
        }

        // Draw empty space
        image_pixels_.setColor(pos_x, pos_y, empty_color);
    }
}

void Canvas::display(ofxCvColorImage &image) {
    image.setFromPixels(image_pixels_);
}