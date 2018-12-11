#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "maze.h"
#include <vector>

class Canvas {

    private:
        void SetPixelColor(int x, int y, const ofColor &color);

        // Drawing screen for entering maze and playing maze respectively
        void DrawInGameScreen(const ofPoint &point, int maze_block_width, int maze_block_height);
        void DrawPreGameScreen(const ofPoint &point, int maze_block_width, int maze_block_height);

        void LoadMazes(int maze_index); // Recursively load all mazes from files

        ofPixels image_pixels_;
        ofColor background_color_;

        std::vector<Maze> mazes_;
        int current_maze_index_ = 0;
        double fov_;
        std::vector<ofPoint> fov_rel_points_;
        ofPoint pen_position_;

        static const std::string kMazeFilePrefix;

        static const ofColor kEmptyColor;
        static const ofColor kWallColor;
        static const ofColor kFruitColor;
        static const ofColor kEndColor;
        static const ofColor kStartColor;
        static const ofColor kPlayerColor;
        static const ofColor kTileColor;

    public:
        void Setup();
        void UpdatePosition(const ofPoint &point); // Called to update position on canvas
        void Display(ofxCvColorImage &image); // Displays the canvas onto an image
        void SetFieldOfView(double fov);
        std::vector<Maze> GetMazes();
        int GetCurrentMazeIndex(); // Returns index of current maze

        static const int kSmallestFov = 1;

        static const int kCameraWidth = 1280;
        static const int kCameraHeight = 720;

};