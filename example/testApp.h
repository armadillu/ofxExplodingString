#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxExplodingString.h"


class testApp : public ofxiPhoneApp{
	
	
    public:
        void setup();
        void update();
        void draw();
        void touchDown(ofTouchEventArgs & touch);
	
		ofTrueTypeFont font;
		ofxExplodingString * xplodingString;
};


