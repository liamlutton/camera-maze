#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class Canvas {

    private:
        ofPixels pixels;

    public:
        void setup();
        void draw(const ofPoint &point, const ofColor &color);
        void display(ofxCvColorImage &image);

        static const int kCameraWidth = 640;
        static const int kCameraHeight = 480;

};