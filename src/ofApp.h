#pragma once

// #include "ofMain.h"
#include "pen-viewer.h"

class ofFingerPaint : public ofBaseApp {

	private:
		static const int image_x_ = 0;
		static const int image_y_ = 0;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		PenViewer pen_viewer_;
		
};
