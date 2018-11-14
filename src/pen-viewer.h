#pragma once

#include "ofMain.h"

class PenViewer {

    private:
        void setupCamera();
        ofVideoGrabber camera_;
        ofImage current_image_;
        bool image_loaded_ = false; // Determines if image is loaded

    public:
        ofVideoGrabber getCamera() const;
        ofImage getCurrentImage() const;
        bool isImageLoaded();

        void update();
        void setup();

        static const int kCameraWidth = 1280;
        static const int kCameraHeight = 720;
};