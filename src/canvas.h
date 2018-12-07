#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "maze.h"
#include <vector>

class Canvas {

    private:
        ofPixels image_pixels_;
        ofColor background_color_;
        Maze maze_;

        double fov_;
        std::vector<ofPoint> fov_rel_points_;

        ofPoint pen_position_;

    public:
        void setup();
        void draw(const ofPoint &point, const ofColor &color);
        void updatePosition(ofPoint new_position);
        void display(ofxCvColorImage &image);
        void setFieldOfView(double fov);

        static const int kSmallestFov = 1;
        static const int kTileSpacingPx = 30;

        static const int kCameraWidth = 1280;
        static const int kCameraHeight = 720;

        static const ofColor kStartBlockColor(200, 0, 100); // Start block color
        static const ofColor kTileColor(120, 0, 25, 0.5);
        static const ofColor kWallColor(100, 100, 100, 1);
        static const ofColor kEmptySpaceColor(255, 255, 255, 1);
        static const ofColor kPlayerColor(0, 100, 255, 1);

};