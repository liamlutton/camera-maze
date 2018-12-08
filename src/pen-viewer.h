#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "canvas.h"

class PenViewer {

    private:
        void processImage();
        void setupCamera();
        void loadColorPixelImages(const ofPixels &image_pixels);
        bool isPixelRed(int r, int g, int b);

        Canvas canvas_;
        ofVideoGrabber camera_;        
        ofxCvContourFinder contour_finder_;

        ofxCvColorImage display_image_;
        ofxCvColorImage red_blob_image_;
        ofPoint center_red_;

        ofColor current_color_;

        static const int kGaussianBlur = 7; // How much pre-blob image is blurred
        static const int kColorVibrancyConstant = 50;

        static const int kSmallestBlobSize = 200;
        static const int kLargestBlobSize = 4000;

    public:
        ofVideoGrabber getCamera() const;
        ofxCvColorImage getDisplayImage() const;
        Canvas getCanvas() const;
        bool isImageLoaded();

        void update();
        void setup();

};