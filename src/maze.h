#pragma once

#include "ofMain.h"
#include <vector>

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
        void KillUser();

        int maze_board_[45][80]; // Size is height and width of maze
        double fov_; // Double so that it can be reduced slower
        MazePosition maze_start_pos_;
        std::vector<MazePosition> fruit_positions_; // Used to save fruit for when map resets

        bool user_alive_ = false;

    public:
        void Load(std::string maze_name);
        void Move(const MazePosition &position);

        bool IsUserAlive();
        int GetItemAt(const MazePosition &position);
        int GetWidth();
        int GetHeight();
        MazePosition GetStartPosition();
        int GetFov();

        static const int kDefaultFov = 80;
        static constexpr double kFovLossValue = 0.025;

};