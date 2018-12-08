#include "maze.h"

void Maze::setup() {
    fov_ = kDefaultFov;

    // Temporary maze

    maze_start_row_ = 4;
    maze_start_column_ = 10;
    for (int r = 0; r < 45; r++) {
        for (int c = 0; c < 80; c++) {
            if (r == 15 && c != 12) {
                maze_board_[r][c] = MazePiece::kMazeWall;
            } else {
                maze_board_[r][c] = MazePiece::kMazeEmpty;
            }
        }
    }
}

void Maze::move(const MazePosition &position) {
    int current_piece = maze_board_[position.row][position.column];

    // Bring user to life from starting screen
    if (!user_alive_) {
        if (position.row == maze_start_row_ && position.column == maze_start_column_) {
            user_alive_ = true;
        }
        return;
    }

    switch(current_piece) {
        case kMazeWall:
            user_alive_ = false;
            break;
        case kMazeFruit:
            fov_ = kDefaultFov;
            maze_board_[position.row][position.column] = kMazeEmpty;
            break;
    }
}

bool Maze::isUserAlive() {
    return user_alive_;
}

int Maze::getItemAt(const MazePosition &position) {
    return maze_board_[position.row][position.column];
}

int Maze::getFov() {
    return fov_;
}

int Maze::getWidth() {
    int width = sizeof(maze_board_[0])/sizeof(*maze_board_[0]);
    return width;
}

int Maze::getHeight() {
    int height = sizeof(maze_board_)/sizeof(*maze_board_);
    return height;
}

int Maze::getStartRow() {
    return maze_start_row_;
}

int Maze::getStartColumn() {
    return maze_start_column_;
}