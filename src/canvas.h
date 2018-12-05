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

};