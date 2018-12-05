#include "maze.h"

Maze::Maze() {
    fov_ = kDefaultFov;

    // Temporary maze
    for (int r = 0; r < 50; r++) {
        for (int c = 0; c < 20; c++) {
            if (r == 15 && c != 12) {
                maze_board_[r][c] = MazePiece::kMazeWall;
            } else {
                maze_board_[r][c] = MazePiece::kMazeEmpty;
            }
        }
    }
}

int Maze::getItemAt(int row, int column) {
    return maze_board_[row][column];
}

int Maze::getWidth() {
    return sizeof(maze_board_)/sizeof(*maze_board_);
}

int Maze::getHeight() {
    return sizeof(maze_board_[0])/sizeof(*maze_board_[0]);
}

// Maze::move(int r, i) {

// }
