#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class PenViewer {

    private:
        void processImage();
        void setupCamera();
        void loadColorPixelImages(const ofPixels &image_pixels);

        ofVideoGrabber camera_;
        ofxCvColorImage current_image_;
        ofxCvColorImage prev_image_;

        ofxCvColorImage display_image_;

        ofxCvColorImage red_blob_image_;
        ofxCvColorImage green_blob_image_;
        ofxCvColorImage blue_blob_image_;

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