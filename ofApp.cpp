#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
	this->word = "0123456789";
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_step += 0.02;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());
	ofRotateX(215);

	int size = 35;
	for (int base_deg = 0; base_deg < 330; base_deg += 5) {

		ofPushMatrix();
		ofRotateY(base_deg);

		int deg_span = 36;
		int deg_start = (int)ofMap(ofNoise(base_deg * 0.005 + this->noise_step), 0, 1, -360, 360);
		int word_index = 0;
		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index++], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofPushMatrix();
			ofTranslate(0, 0, -300);
			ofRotateX(deg);

			ofFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 60);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 60);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 680;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}