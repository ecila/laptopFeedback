#ifndef _TEST_APP
#define _TEST_APP
// alice 090908
// v1: hack together of openframeworks input and output audio examples with Scott Lehman's
// simple delay line
// v2: creates a separate C++ class from delay and adds variable delay line with mouse controlled delay time
// wattDelay: uses watt govenor or delay time movement to maintain balance
// wattdelay version 2: 2 units of delay, adjust amp or delay time according to peak in delay line

#include "ofMain.h"
#include "ofAddons.h"
#include "vdelay.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		void audioReceived 	(float * input, int bufferSize, int nChannels); 
		void audioRequested (float * output, int bufferSize, int nChannels);
		void initAudio();
		
		Vdelay *vdeL;			// pointer to delay object on left channel
		Vdelay *vdeR;			// pointer to delay object on right channel	

		float 			* fftSmoothed;		// copy their method for smoothing fft
		// audio global
		int		sampleRate;
		int		frameSize;
		
		int mouseX, mouseY;
		bool display;
		
		//-------- audio in
		float * lIn;
		float * rIn;
		int 	bufferCounter;
		int 	drawCounter;
		
		//-------- audio out
		float 	volume;		
		float 	* lOut;
		float   * rOut;		
	
};

#endif	

