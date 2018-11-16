#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class PenViewer {

    private:
        void processImage();
        void setupCamera();

        ofVideoGrabber camera_;
        ofxCvColorImage current_image_;
        ofxCvColorImage prev_image_;

        ofxCvColorImage display_image_;

    public:
        ofVideoGrabber getCamera() const;
        ofxCvColorImage getCurrentImage() const;
        ofxCvColorImage getDisplayImage() const;
        bool isImageLoaded();

        void update();
        void setup();

        static const int kCameraWidth = 640;
        static const int kCameraHeight = 480;
};