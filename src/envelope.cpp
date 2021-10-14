/*
 *  envelope.cpp
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "envelope.h"

envelope::envelope(int samRate, int fSize, float envStart, float envEnd, float envCurrent, int envTime) {
	start = start;
	destination = envEnd;
	current = envCurrent;
	time = envTime;
	sampleRate = samRate;
	frameSize = fSize;	
	buffer = new float[frameSize];
	envGenerate(current);
	return;
	}

//--------------------------------------------------------------
// initialise frame of audio with constant val
void envelope::envGenerate (float val)
{
	for(int i = 0; i < frameSize; i ++)
		buffer[i] = val;
			
} 

//--------------------------------------------------------------
// updates
void envelope::setEnvelope (){

	float inc;												// amount each sample changes
	int rampTimeInSamples = time * (sampleRate * 0.001);		// ramp time in samples

	//check if new val differs from current val
	if(destination != current){
		inc = (destination - current)/ rampTimeInSamples;
		
		for(int i = 0; i < frameSize; i ++){
			current += inc;
			buffer[i] = fmax(current, 0.0);
		}	
	}	

}


//--------------------------------------------------------------
// set destination sample value of envelope
void envelope::setTarget(float target, float max) {

	destination = target;
//	wrap
	if(destination < 0.0)
		destination = 50.0f + destination;
	if(destination > 50.0f)
		destination = destination - 50.0f;
/*
	//constrain
	destination = fmax(destination, 0.0);		
	destination = fmin(destination, 100.0);
*/	
}

//--------------------------------------------------------------
float envelope::getCurrent()
{
	return current;
}

//--------------------------------------------------------------
void envelope::setCurrent(float val)
{
	current = val;
}

