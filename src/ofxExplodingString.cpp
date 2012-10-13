//
//  ofxExplodingString.cpp
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 05/09/12.
//
//

#include "ofxExplodingString.h"

ofxExplodingString::ofxExplodingString( ofTrueTypeFont * font, ofColor color ){
	this->font = font;
	this->color = color;
	firstFrame = false;
}

ofxExplodingString::~ofxExplodingString(){
	reset();
}

void ofxExplodingString::reset(){

	for(int i = xploding.size() - 1; i >= 0 ; i--){
		delete xploding[i];
	}
	xploding.clear();
}


void ofxExplodingString::update(float dt){

	if (firstFrame){	//skip the first update so that the first draw shows all vectors in place
		firstFrame = false;
	}else{
		for(int i = xploding.size() - 1; i >= 0 ; i--){
			
			xploding[i]->life -= dt / duration;
			if ( xploding[i]->life <= 0.0f ){
				delete xploding[i];
				xploding.erase( xploding.begin() + i );
			}else{
				xploding[i]->p += xploding[i]->speed * dt;
				xploding[i]->p2 += xploding[i]->speed2 * dt;
				xploding[i]->speed *= friction;
				xploding[i]->speed.y += acceleration * dt;
				xploding[i]->speed2 *= friction;
				xploding[i]->speed2.y += acceleration * dt;
			}
		}
	}
}

void ofxExplodingString::draw(){
	
	ofMesh m;
	m.setMode(OF_PRIMITIVE_LINES);
	for(int i = 0; i < xploding.size(); i++){
		m.addVertex(xploding[i]->p);
		m.addVertex(xploding[i]->p2);
		ofColor c = color;
		c.a = ( xploding[i]->life  ) * 255;
		m.addColor( c );
		m.addColor( c );
	}
	
	ofPushMatrix();
		ofTranslate(pos);
		m.draw();
	ofPopMatrix();
	
	//maybe do it with triangles also?
	//	ofSetColor(255);
	//	vector<ofTTFCharacter> paths = font.getStringAsPoints(string);
	//	paths[0].simplify(0.95);
	//	ofMesh mm = paths[0].getTessellation();
	//	mm.draw();
	//	ofSetColor(0,255,0);
	//	mm.drawWireframe();
}


void ofxExplodingString::explode(string text, float x, float y, float duration_, float force_, float gravity , float friction_ ){
	
	firstFrame = true;
	pos.x = x;
	pos.y = y;
	force = force_;
	duration = duration_;
	acceleration = gravity;
	friction = friction_;
	
	reset();
	
	vector<ofTTFCharacter> paths = font->getStringAsPoints(text);
	
	for(int i = 0; i < paths.size(); i++){
		
		vector<ofPolyline> outlines = paths[i].getOutline();
		
		for(int j = 0; j < outlines.size(); j++){
			
			ofPolyline poly = outlines[j];
			poly.simplify( 1.0f );
			
			for(int k = 0; k < poly.size() - 1; k++){
				textParticle *a = new textParticle;
				a->p = poly[k];
				ofVec2f vel = ofVec2f( ofRandom(0.5f, 2.0f), ofRandom(0.5f, 2.0f)) * ( a->p - poly.getCentroid2D() ) / font->getSize();
				a->speed = force * vel;
				a->p2 = poly[k+1];
				a->speed2 = a->speed * ofRandom(0.75f, 1.5); //+ force * ofVec2f(ofRandom(-1,1), ofRandom(-1,1));
				a->life = ofRandom(0.9f, 1.0f);
				xploding.push_back(a);
			}
		}
	}
}
