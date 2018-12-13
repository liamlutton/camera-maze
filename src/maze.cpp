#include "maze.h"
#include <fstream>

// Returns true if loaded properly
bool Maze::Load(std::string maze_name) {
    fov_ = kDefaultFov;
    last_position_ = MazePosition{-1, -1};

    std::ifstream input_file;
    input_file.open(ofToDataPath(maze_name));

    if (!input_file.is_open()) {
        return false;
    }

    // Read file line by line, load to maze
    std::string line;
    int row = 0;
    while (input_file >> line) {
        for (int col = 0; col < line.size(); col++) {
            MazePiece maze_piece;
            char id = line[col];

            switch (id) {
                case kStartSymbol:
                    maze_start_pos_ = {row, col};
                case kEmptySymbol:
                    maze_piece = kMazeEmpty;
                    break;
                case kWallSymbol:
                    maze_piece = kMazeWall;
                    break;
                case kEndSymbol:
                    maze_piece = kMazeEnd;
                    break;
                case kFruitSymbol:
                    fruit_positions_.push_back({row, col});
                    fov_ = kDefaultFov;
                    maze_piece = kMazeFruit;
                    break;
            }

            maze_board_[row][col] = maze_piece;
        }
        row++;
    }
    input_file.close();
    return true;
}

// Returns place moved to
MazePiece Maze::Move(const MazePosition &position) {
    fov_ -= kFovLossValue;
    if (fov_ < kMinFov) {
        fov_ = kMinFov;
    }
    int current_piece = maze_board_[position.row][position.column];

    // Bring user to life from starting screen
    if (!user_alive_) {
        if (position.row == maze_start_pos_.row && position.column == maze_start_pos_.column) {
            user_alive_ = true;
        }
        return kMazeEmpty;
    }

    // Make sure user is not teleporting
    if (last_position_.row != -1 && last_position_.column != -1) {
        if (fabs(position.row - last_position_.row) > 1 || fabs(position.column - last_position_.column) > 1) {
            KillUser();
            return kMazeEmpty;
        }
    }

    last_position_ = position;

    switch (current_piece) {
        case kMazeWall:
            KillUser();
            return kMazeWall;
        case kMazeFruit:
            fov_ = kDefaultFov;
            maze_board_[position.row][position.column] = kMazeEmpty;
            return kMazeFruit;
        case kMazeEnd:
            return kMazeEnd;
    }
    return kMazeEmpty;
}

void Maze::KillUser() {
    last_position_ = MazePosition{-1, -1};
    fov_ = kDefaultFov;
    // Refill fruit
    for (MazePosition fruit_position : fruit_positions_) {
        maze_board_[fruit_position.row][fruit_position.column] = kMazeFruit;
    }
    user_alive_ = false;
}

bool Maze::IsUserAlive() {
    return user_alive_;
}

int Maze::GetItemAt(const MazePosition &position) {
    return maze_board_[position.row][position.column];
}

int Maze::GetFov() {
    return fov_;
}

int Maze::GetWidth() {
    int width = sizeof(maze_board_[0])/sizeof(*maze_board_[0]);
    return width;
}

int Maze::GetHeight() {
    int height = sizeof(maze_board_)/sizeof(*maze_board_);
    return height;
}

MazePosition Maze::GetStartPosition() {
    return maze_start_pos_;
}