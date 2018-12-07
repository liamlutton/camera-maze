#pragma once

#include "ofMain.h"

enum MazePiece {
    kMazeEmpty,
    kMazeWall,
    kMazeFruit,
    kMazeEnd
};

class Maze {

    private:
        int maze_board_[45][80]; // Size is height and width of maze
        int fov_;
        int maze_start_row_;
        int maze_start_column_;

        bool user_alive_ = false;

    public:
        void setup();
        void move(int r, int c);

        bool isUserAlive();
        int getItemAt(int row, int column);
        int getWidth();
        int getHeight();
        int getStartRow();
        int getStartColumn();

        static const int kDefaultFov = 80;

};