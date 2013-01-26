#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	
	ofBackground(0);
	ofSetColor(255);
	
	svg.load("trumpetflower.svg");
    cout << "numPath " << svg.getNumPath() << endl;
    
    image.loadImage("trumphetflover13.jpg");
    
    audio.loadSound("01 Cake & Eat It Too.aif");
    audio.play();
    
    fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 602;
    
}

float step;

//--------------------------------------------------------------
void testApp::update()
{
	step += 0.0001;
	if (step > 1) {
        
		step -= 1;
	}
    
    ofSoundUpdate();
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}

}

//--------------------------------------------------------------
void testApp::draw()
{
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofScale(3.0, 3.0, 1.0);
	//ofRotateZ(step * 360);
    ofTranslate(-svg.getWidth()/2, -svg.getHeight()/2);
    ofSetColor(255, 255, 255, 255);
    image.draw(0, -1, svg.getWidth(), svg.getHeight());

    ofSetColor(255, 255, 255, 150);
    for (int i = 0; i < svg.getNumPath(); i++)
    {
        ofPath &p = svg.getPathAt(i);
        
        vector<ofPolyline>& lines = p.getOutline();
        
        for (int k = 0; k < lines.size(); k++)
        {
            ofPolyline line = lines[k].getResampledBySpacing(1);
            
            int num = fftSmoothed[i] * line.size();
            
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < num; j++)
            {
                ofVec3f &vv = line[j];
                glVertex3f(vv.x, vv.y, vv.z);
            }
            glEnd();
        }
    }

	
	ofPopMatrix();
    
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	
}
