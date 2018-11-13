#pragma once

#include "ofMain.h"

class PenViewer {

    private:
        void setupCamera();
        ofVideoGrabber camera_;

    public:
        ofVideoGrabber getCamera() const;
        void update();
        void setup();

        static const int kCameraWidth = 320;
        static const int kCameraHeight = 240;
};