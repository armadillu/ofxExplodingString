#include "testApp.h"

int x = 100;
int y = 100;
string text = "exploding text";

void testApp::setup(){
	
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
	ofEnableAlphaBlending();
	ofBackground(0);
	
	font.loadFont("CPMono_v07 ExtraLight_uri.ttf", 50, true, true, true);
	xplodingString = new ofxExplodingString( &font, ofColor(255) );
}


void testApp::update(){
	xplodingString->update(0.01666);
}


void testApp::draw(){

	ofSetColor(255, 64);
	font.drawString(text, x, y);
	xplodingString->draw();
}


void testApp::touchDown(ofTouchEventArgs & touch){
	x = touch.x;
	y = touch.y;
	xplodingString->explode(text, x, y);
}


