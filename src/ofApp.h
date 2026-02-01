#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
	void setupGUI();

	int _X = 256;
	int _Z = 256;
	std::vector<float> heights;
	std::vector <float> interHeights;
	std::vector <float> resultHeights;

	ofMesh dunes;
	glm::vec3 normal;
	ofFloatImage normalMap;
	std::vector<ofFloatImage> textureMaps;
	ofShader shader;

	ofEasyCam cam;

	ofxPanel gui;
	ofParameterGroup duneParams;
	ofParameter<float> windVelocityParam;
	ofParameter<float> maxHeightParam;
	ofParameter<float> velocityHeightParam;
	ofParameter<float> sandTransportRateParam;
	ofParameter<float> diffusionCoeffParam;
};