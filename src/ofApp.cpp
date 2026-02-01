#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
	setupGUI();
	ofDisableArbTex();
	if (shader.load("shader.vert", "shader.frag")) {
		ofLogNotice() << "Shader loaded successfully";
	}
	else {
		ofLogError() << "Shader failed to load";
	}
	heights.resize(_X * _Z);
	for (int i = 0; i < _X; i++) {
		for (int j = 0; j < _Z; j++) {
			heights[i + j * _X] = ofNoise(i * 0.05, j * 0.05) * maxHeightParam.get();
			glm::vec3 vertex(i, heights[i + j * _X], j);
			dunes.addVertex(vertex);

			// UV座標の追加（0.0 〜 1.0 の範囲に正規化する）
			float u = (float)i / (_X - 1);
			float v = (float)j / (_Z - 1);
			dunes.addTexCoord(glm::vec2(u, v));
		}
	}

	dunes.setMode(OF_PRIMITIVE_TRIANGLES);
	for (int i = 0; i < _X - 1; i++) {
		for (int j = 0; j < _Z - 1; j++) {
			dunes.addIndex(i + j * _X);
			dunes.addIndex((i + 1) + j * _X);
			dunes.addIndex(i + (j + 1) * _X);

			dunes.addIndex(i + (j + 1) * _X);
			dunes.addIndex((i + 1) + j * _X);
			dunes.addIndex((i + 1) + (j + 1) * _X);
		}
	}

	normalMap.allocate(_X, _Z, OF_IMAGE_COLOR);
}
void ofApp::setupGUI() {
	gui.setup();
	gui.setName("Dune Simulation");
	duneParams.setName("Dune Parameters");
	duneParams.add(windVelocityParam.set("Wind Velocity", 3.3, 0.0, 10.0));
	duneParams.add(maxHeightParam.set("Max Height", 8.7, 0.0, 20.0));
	duneParams.add(velocityHeightParam.set("Velocity Height Factor", 1.8, 0.0, 5.0));
	duneParams.add(sandTransportRateParam.set("Sand Transport Rate", 0.01, 0.0, 0.1));
	duneParams.add(diffusionCoeffParam.set("Diffusion Coefficient", 0.05, 0.0, 0.2));
	gui.add(duneParams);
}
//--------------------------------------------------------------
void ofApp::update() {
	interHeights = heights;
	resultHeights = heights;
	for (int i = 0; i < _X; i++) {
		for (int j = 0; j < _Z; j++) {
			int Idx = i + j * _X;
			float L = windVelocityParam.get() + velocityHeightParam.get() * heights[i + j * _X];

			int offset = static_cast<int>(std::round(L));
			int nextX = (i + offset) % _X;
			if (nextX < 0) {
				nextX += _X;
			}
			int nextIdx = nextX + j * _X;

			interHeights[Idx] -= sandTransportRateParam.get();
			interHeights[nextIdx] += sandTransportRateParam.get();
		}
	}
	resultHeights = interHeights;
	for (int i = 0; i < _X; i++) {
		for (int j = 0; j < _Z; j++) {
			int Idx = i + j * _X;
			// 平滑化
			float sum_NN = 0;
			float sum_NNN = 0;

			// 上下左右 (NN)
			int left = (i - 1 + _X) % _X;
			int right = (i + 1) % _X;
			int up = (j - 1 + _Z) % _Z;
			int down = (j + 1) % _Z;

			sum_NN += interHeights[left + j * _X];
			sum_NN += interHeights[right + j * _X];
			sum_NN += interHeights[i + up * _X];
			sum_NN += interHeights[i + down * _X];

			// 斜め 4点 (NNN)
			sum_NNN += interHeights[left + up * _X];   // 左上
			sum_NNN += interHeights[right + up * _X];  // 右上
			sum_NNN += interHeights[left + down * _X]; // 左下
			sum_NNN += interHeights[right + down * _X];// 右下

			float delta = diffusionCoeffParam.get() * ((1.0 / 6.0) * sum_NN + (1.0 / 12.0) * sum_NNN - interHeights[Idx]);
			resultHeights[Idx] = interHeights[Idx] + delta;
		}
	}
	heights = resultHeights;

	updateNormalMap();

	for (int i = 0; i < _X; i++) {
		for (int j = 0; j < _Z; j++) {
			int idx = i + j * _X;
			glm::vec3 vertex = dunes.getVertex(idx);
			vertex.y = heights[idx];
			dunes.setVertex(idx, vertex);
		}
	}
}

void ofApp::updateNormalMap() {
	ofFloatPixels& pix = normalMap.getPixels();

	for (int j = 0; j < _Z; j++) {
		for (int i = 0; i < _X; i++) {
			// 境界条件（周期境界）を考慮したインデックス取得
			int left = (i - 1 + _X) % _X;
			int right = (i + 1) % _X;
			int up = (j - 1 + _Z) % _Z;
			int down = (j + 1) % _Z;

			// 勾配の計算
			float nx = heights[left + j * _X] - heights[right + j * _X]; // X方向の勾配
			float nz = heights[i + up * _X] - heights[i + down * _X]; // Z方向の勾配
			float ny = 2.0f; // ★ここを '2.0' にすると、グリッド間隔(1.0)と計算が合います（重要）

			// ベクトルの成分順序を (X, Y, Z) = (nx, ny, nz) に固定
			glm::vec3 n = glm::normalize(glm::vec3(nx, ny, nz));

			pix.setColor(i, j, ofFloatColor(
				(n.x + 1.0f) * 0.5f, // R = X
				(n.y + 1.0f) * 0.5f, // G = Y (Up)
				(n.z + 1.0f) * 0.5f  // B = Z
			));
		}
	}
	normalMap.update(); // GPUにデータを転送
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(30);
	cam.begin();

	shader.begin();
	// 太陽を円を描くように動かす（夕方〜昼をシミュレート）
	float time = ofGetElapsedTimef() * 0.5;
	glm::vec3 sunPos(cos(time), 0.2f, sin(time)); // 低い太陽

	shader.setUniform3f("lightDir", sunPos.x, sunPos.y, sunPos.z);
	shader.setUniformTexture("normalMap", normalMap.getTexture(), 0);

	ofSetColor(255);
	dunes.draw(); // 陰影がついた砂紋が動き出すはずです！
	shader.end();

	cam.end();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}