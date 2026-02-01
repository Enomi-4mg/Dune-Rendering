#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void updateNormalMap();

	int _X = 256;
	int _Z = 256;
	std::vector<float> heights;
	std::vector <float> interHeights;
	std::vector <float> resultHeights;
	float H = 8.7;
	float v_h = 1.8;
	float q = 0.01;
	float windVelocity = 3.3;
	float D = 0.05;

	ofMesh dunes;
	glm::vec3 normal;
	ofFloatImage normalMap;
	std::vector<ofFloatImage> textureMaps;
	ofShader shader;

	ofEasyCam cam;
};