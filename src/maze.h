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

        MazePosition last_position_;
        bool user_alive_ = false;

    public:
        bool Load(std::string maze_name);
        bool Move(const MazePosition &position);

        bool IsUserAlive();
        int GetItemAt(const MazePosition &position);
        int GetWidth();
        int GetHeight();
        int GetCurrentMaze();
        MazePosition GetStartPosition();
        int GetFov();

        static const char kStartSymbol = 'S';
        static const char kEmptySymbol = '0';
        static const char kWallSymbol = '1';
        static const char kEndSymbol = 'E';
        static const char kFruitSymbol = 'F';

        static const int kDefaultFov = 80;
        static const int kMinFov = 40;
        static constexpr double kFovLossValue = 0.025;

};