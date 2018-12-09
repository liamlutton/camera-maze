#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "canvas.h"

class PenViewer {

    private:
        void ProcessImage();
        void SetupCamera();
        void LoadColorPixelImages(const ofPixels &image_pixels);
        bool IsPixelRed(int r, int g, int b);

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
        ofVideoGrabber GetCamera() const;
        ofxCvColorImage GetDisplayImage() const;
        Canvas GetCanvas() const;
        bool IsImageLoaded();

        void Update();
        void Setup();

};