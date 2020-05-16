#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	this->noise_seed = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->frame.clear();

	for (int deg = 0; deg < 360; deg += 15) {
		
		for (int z = 0; z < 450; z += 1) {

			auto tmp_deg = deg + ofMap(ofNoise(this->noise_seed, (ofGetFrameNum() + 600 - z) * 0.01), 0, 1, -60, 60);
			auto location = glm::vec3(250 * cos(tmp_deg * DEG_TO_RAD), 250 * sin(tmp_deg * DEG_TO_RAD), z);
			this->frame.addVertex(location);
			this->frame.addColor(ofColor(255, ofMap(z, 0, 450, 255, 0)));

			int index = this->frame.getNumVertices() - 1;
			if (z > 0) {

				this->frame.addIndex(index); this->frame.addIndex(index - 1);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int deg = 0; deg < 360; deg += 15) {

		auto tmp_deg = deg + ofMap(ofNoise(this->noise_seed, (ofGetFrameNum() + 600) * 0.01), 0, 1, -60, 60);
		auto location = glm::vec3(250 * cos(tmp_deg * DEG_TO_RAD), 250 * sin(tmp_deg * DEG_TO_RAD), 0);

		ofDrawCircle(location, 8);
		ofDrawSphere(location, 2);
	}

	this->frame.drawWireframe();



	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}