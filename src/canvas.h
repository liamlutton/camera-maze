#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <vector>

class Canvas {

    private:
        ofPixels image_pixels_;

        int brush_size_;
        std::vector<ofPoint> brush_rel_points_;

    public:
        void setup();
        void draw(const ofPoint &point, const ofColor &color);
        void display(ofxCvColorImage &image);
        void setBrushSize(int brush_size);

        static const int kSmallestBrushSize = 1;

        static const int kCameraWidth = 640;
        static const int kCameraHeight = 480;

};