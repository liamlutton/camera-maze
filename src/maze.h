#pragma once

#include "ofMain.h"

enum MazePiece {
    kMazeEmpty,
    kMazeWall,
    kMazeFruit,
    kMazeEnd
};

struct MazePosition {
    int row;
    int column;
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
        void move(const MazePosition &position);

        bool isUserAlive();
        int getItemAt(const MazePosition &position);
        int getWidth();
        int getHeight();
        int getStartRow();
        int getStartColumn();
        int getFov();

        static const int kDefaultFov = 50;

};