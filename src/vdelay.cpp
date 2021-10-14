/*
 *  delay.cpp
 *  openFrameworks
 * c
 *  Created by ecila on 9/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vdelay.h"

Vdelay::Vdelay(int samRate, int fSize, float maxLen, float initDelay, float feedback, float wetMix, float dryMix){
  maxDelay = maxLen;
  currentFixedDelay = initDelay;		// initialise to max - used for constant float version
  feedbackGain = feedback;
  wetLevel = wetMix;
  dryLevel = dryMix;
  sampleRate = samRate;
  wattGovernedGain = 0.0;
  env = new envelope(samRate, fSize, initDelay, initDelay, initDelay, 100);
  watt = new wattGain(fSize, 0.05, 0.0005);
  deviation = 0.0;
 
  return;
}


//--------------------------------------------------------------
void Vdelay::initDelayBuffer (float * in, float * out) {
	
	// TODO add some error checking to make sure lIn and lOut are initialised
	
	// calc max buffer size and allocate, with extra point for interpolation			
	delayLineLength = (int)(maxDelay*sampleRate*0.001) + 1;
	if(delayLineLength <= 0)
		printf(" DELAY BUFFER LENGTH IS NON_POSITIVE ");
	
	// allocate buffer
	delayLineStart = new float[delayLineLength];
				
	// set up pointers for the delay line
	delayLineEnd = delayLineStart + delayLineLength;
	writePtr = delayLineStart;	
	
	//zero out the buffer (silence)
	do {
		*writePtr = (float)0.0;
	}
	while (++writePtr < delayLineEnd);
	
	//set read pointer to end of delayline. Setting it to the end
	//ensures the interpolation below works correctly to produce
	//the first non-zero sample.
	writePtr = delayLineStart + delayLineLength -1;
	
	// assign to left channel only for now - not sure this works !!	
	outputSignal = out;
	inputSignal = in;
	currentDelay = env->buffer;	
	return;	
}


//--------------------------------------------------------------
void Vdelay::writeToDelay (float *inL, float frameSize) {

	float offset, *ptr, diff, frac;		
		
	// adjust gain and/or delay time according to current peak in delay buffer
// 	wattGovernedGain = watt->getNewGain(outputSignal);
 	wattGovernedGain = 1.0;//watt->getNewGain(inL);

	//adjust delay time according to deviation from input buffer
	
	deviation = watt->getNewDelayTime(outputSignal);	
 	env->setTarget(env->getCurrent() + deviation, maxDelay);
	env->setEnvelope();
	
	for(s = 0; s < frameSize; s ++){
		
		// calc no samples needed for desired delay time
		offset = currentDelay[s] * sampleRate * 0.001;
//		offset = currentFixedDelay * sampleRate * 0.001;
		
		
		//compute the largest read pointer based on the offset.  If ptr
		//is before the first delayline location, wrap around end point
		ptr = writePtr - (int)(ceil(offset));
		if (ptr < delayLineStart)
			ptr += delayLineLength - 1;
		
		//compute distance from ptr and slope to the next sample
		diff = *(ptr+1) - *ptr;
		frac =  1 - (offset - (int)offset);

		//calculate the delayline output value and scale by wattGovernedGain
		delayLineOutput = (*ptr + diff*frac) * wattGovernedGain;
//		delayLineOutput = (*ptr + diff*frac);

		outputSignal[s] = delayLineOutput;

		//write the input sample and any feedback to delayline
		*writePtr = inputSignal[s]  +  delayLineOutput ;
	
		//increment buffer index and wrap if necesary
		if (++writePtr >= delayLineEnd){
			*delayLineStart = *(delayLineEnd-1);
			writePtr = delayLineStart + 1;		
			}
	}
	

	return;
}


//--------------------------------------------------------------
void Vdelay::Clear(void)
{
	// HELP !
	for (int i = 0; i < delayLineLength + 1; i ++){
		outputSignal[i] = inputSignal[i] = 0.0;
	}
}

//--------------------------------------------------------------
void Vdelay::Cleanup(void)
{
	//Free memory allocated during initialization
	delete [] delayLineStart;
}

