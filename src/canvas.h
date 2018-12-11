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

        ofPixels image_pixels_;
        ofColor background_color_;

        std::vector<Maze> mazes_;
        int current_maze_index_ = 0;

        double fov_;
        std::vector<ofPoint> fov_rel_points_;

        ofPoint pen_position_;

        static const ofColor kEmptyColor;
        static const ofColor kWallColor;
        static const ofColor kFruitColor;
        static const ofColor kEndColor;
        static const ofColor kStartColor;
        static const ofColor kPlayerColor;
        static const ofColor kTileColor;

    public:
        void Setup();
        void LoadMazes(int maze_index);
        void UpdatePosition(const ofPoint &point);
        void Display(ofxCvColorImage &image);
        void SetFieldOfView(double fov);

        static const int kSmallestFov = 1;

        static const int kCameraWidth = 1280;
        static const int kCameraHeight = 720;

};