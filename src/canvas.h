#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "maze.h"
#include <vector>

class Canvas {

    private:
        void setPixelColor(int x, int y, const ofColor &color);

        ofPixels image_pixels_;
        ofColor background_color_;
        Maze maze_;

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
        void setup();
        void updatePosition(const ofPoint &point);
        void display(ofxCvColorImage &image);
        void setFieldOfView(double fov);

        static const int kSmallestFov = 1;
        static const int kTileSpacingPx = 30;

        static const int kCameraWidth = 1280;
        static const int kCameraHeight = 720;

};