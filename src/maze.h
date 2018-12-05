#pragma once

#include "ofMain.h"

enum MazePiece {
    kMazeEmpty,
    kMazeWall,
    kMazeFruit
};

class Maze {

    private:
        int maze_board_[80][45]; // Size is maze width and maze height
        int fov_;

    public:
        Maze();
        void move();
        int getItemAt(int row, int column);
        int getWidth();
        int getHeight();

        static const int kEmptySpaceId = 0;
        static const int kWallId = 1;
        static const int kFruitId = 2;

        static const int kDefaultFov = 80;

};