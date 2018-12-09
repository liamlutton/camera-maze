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
        MazePosition maze_start_pos_;

        bool user_alive_ = false;

    public:
        void Load(std::string maze_name);
        void move(const MazePosition &position);

        bool isUserAlive();
        int getItemAt(const MazePosition &position);
        int getWidth();
        int getHeight();
        MazePosition getStartPosition();
        int getFov();

        static const int kDefaultFov = 50;

};