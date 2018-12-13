#include "canvas.h"
#include <math.h>

const std::string Canvas::kMazeFilePrefix = "mazes/maze_";

const std::string Canvas::kMusicFruitFile = "music/music_fruit.mp3";
const std::string Canvas::kMusicVictoryFile = "music/music_victory.mp3";
const std::string Canvas::kMusicBackgroundFile = "music/music_background.mp3";

// Initialize all constant colors
const ofColor Canvas::kEmptyColor = ofColor(220, 220, 220, 0.8); // Empty space color, green
const ofColor Canvas::kWallColor = ofColor(50, 50, 50, 1); // Wall color, gray
const ofColor Canvas::kFruitColor = ofColor(255, 0, 0, 1); // Fruit color, bright red
const ofColor Canvas::kEndColor = ofColor(0, 255, 0, 1); // End color, bright green
const ofColor Canvas::kStartColor = ofColor(0, 255, 100); // Start color, dark red
const ofColor Canvas::kPlayerColor = ofColor(0, 100, 255, 1); // Player color, cyan
const ofColor Canvas::kTileColor = ofColor(120, 0, 25, 0.5); // Tiling color, brown

void Canvas::Setup() {
    // Setting up music players
    fruit_eat_player_.load(kMusicFruitFile);
    victory_noise_player_.load(kMusicVictoryFile);
    background_music_player_.load(kMusicBackgroundFile);
    background_music_player_.play();

    LoadMazes(0);
    image_pixels_.allocate(kCameraWidth, kCameraHeight, OF_IMAGE_COLOR);
    background_color_.set(0, 0, 0, 1);

    SetFieldOfView(mazes_[current_maze_index_].GetFov());

    // Sets background color
    image_pixels_.setColor(background_color_);
}

void Canvas::LoadMazes(int maze_index) {
    Maze maze;
    // If maze loads
    if (maze.Load(kMazeFilePrefix + std::to_string(maze_index))) {
        mazes_.push_back(maze);
        LoadMazes(maze_index + 1);
    }
}

void Canvas::SetFieldOfView(double fov) {
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

void Canvas::DrawInGameScreen(const ofPoint &point, int maze_block_width, int maze_block_height) {
    // Update field of view
    SetFieldOfView(mazes_[current_maze_index_].GetFov());

    image_pixels_.setColor(background_color_);

    for (ofPoint rel_point : fov_rel_points_) {
        int pos_x = rel_point.x + point.x;
        int pos_y = rel_point.y + point.y;

        // Make sure point is on screen
        if (pos_x < 0 || pos_x >= kCameraWidth || pos_y < 0 || pos_y >= kCameraHeight) {
            continue;
        }

        // Determining the position on the maze which the pixel maps to
        int maze_column = (kCameraWidth - pos_x) / maze_block_width;
        int maze_row = pos_y / maze_block_height;

        // Drawing player
        if (fabs(pos_x - point.x) <= 3 && fabs(pos_y - point.y) <= 3) {
            SetPixelColor(pos_x, pos_y, kPlayerColor);
            continue;
        }

        // Drawing maze tiles
        if (pos_x % maze_block_width == 0 || pos_y % maze_block_height == 0) {
            SetPixelColor(pos_x, pos_y, kTileColor);
            continue;
        }

        // Drawing maze pieces
        switch (mazes_[current_maze_index_].GetItemAt({maze_row, maze_column})) {
            case MazePiece::kMazeWall:
                SetPixelColor(pos_x, pos_y, kWallColor);
                continue;
            case MazePiece::kMazeFruit:
                SetPixelColor(pos_x, pos_y, kFruitColor);
                continue;
            case MazePiece::kMazeEnd:
                SetPixelColor(pos_x, pos_y, kEndColor);
                continue;
        }

        // Draw empty space
        SetPixelColor(pos_x, pos_y, kEmptyColor);
    }
}

void Canvas::DrawPreGameScreen(const ofPoint &point, int maze_block_width, int maze_block_height) {
    image_pixels_.setColor(kEmptyColor);
    MazePosition start_position = mazes_[current_maze_index_].GetStartPosition();

    int start_x_pos = (mazes_[current_maze_index_].GetWidth() - start_position.column - 1) * maze_block_width;
    int start_y_pos = start_position.row * maze_block_height;

    // Drawing start box
    for (int xi = 0; xi < maze_block_width; xi++) {
        for (int yi = 0; yi < maze_block_height; yi++) {
            SetPixelColor(xi + start_x_pos, yi + start_y_pos, kStartColor);
        }
    }

    // Drawing player
    for (int rel_x = -3; rel_x <= 3; rel_x++) {
        for (int rel_y = -3; rel_y <= 3; rel_y++) {
            SetPixelColor(point.x + rel_x, point.y + rel_y, kPlayerColor);
        }
    }
}

// Draw at a specified point
void Canvas::UpdatePosition(const ofPoint &point) {
    int maze_block_width = kCameraWidth / mazes_[current_maze_index_].GetWidth();
    int maze_block_height = kCameraHeight / mazes_[current_maze_index_].GetHeight();

    int row = point.y / maze_block_width;
    int col = mazes_[current_maze_index_].GetWidth() - point.x / maze_block_width;

    // Play sounds (and increment map if won)
    MazePiece moved_to_piece = mazes_[current_maze_index_].Move(MazePosition{row, col});
    if (moved_to_piece == kMazeEnd) {
        current_maze_index_++;
        victory_noise_player_.play();
    } else if (moved_to_piece == kMazeFruit) {
        fruit_eat_player_.play();
    }

    // Draw screen for game based on whether user is alive
    if (mazes_[current_maze_index_].IsUserAlive()) {
        DrawInGameScreen(point, maze_block_width, maze_block_height);
    } else {
        DrawPreGameScreen(point, maze_block_width, maze_block_height);
    }
}

// Allows setting a pixel color from a constant color object. Sets to canvas pixels.
void Canvas::SetPixelColor(int x, int y, const ofColor &color) {
    image_pixels_.setColor(x, y, ofColor(color.r, color.g, color.b, color.a));
}

void Canvas::Display(ofxCvColorImage &image) {
    image.setFromPixels(image_pixels_);
}

std::vector<Maze> Canvas::GetMazes() {
    return mazes_;
}

int Canvas::GetCurrentMazeIndex() {
    return current_maze_index_;
}