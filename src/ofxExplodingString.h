//
//  ofxExplodingString.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 05/09/12.
//
//

#ifndef __emptyExample__ofxExplodingString__
#define __emptyExample__ofxExplodingString__

#include <iostream>
#include "ofMain.h"

class ofxExplodingString{

	public:

		struct textParticle{
			ofVec2f p;
			ofVec2f p2;
			ofVec2f speed;
			ofVec2f speed2;
			float life;
		};

		//font MUST have been created with makeContours == true
		ofxExplodingString( ofTrueTypeFont * font, ofColor color );
		~ofxExplodingString();
		
		void update(float dt);
		void draw();
		void explode(string text,
					 float x, float y,
					 float duration = 0.75f,
					 float force = 150.0f,
					 float gravity = 250.0f,
					 float friction = 0.98f
					 );
		void reset();

	private:
		
		bool firstFrame;
		ofVec2f pos;
		ofTrueTypeFont * font;
		vector<textParticle*> xploding;
		ofColor color;
		float force;
		float duration;
		float friction;
		float acceleration;
};

#endif /* defined(__emptyExample__ofxExplodingString__) */
