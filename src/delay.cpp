/*
 *  delay.cpp
 *  openFrameworks
 *
 *  Created by ecila on 9/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "delay.h"

Delayline :: Delayline (float samRate, float time, float feedback, float wetMix, float dryMix) {
  delayTime = time;
  feedbackGain = feedback;
  wetLevel = wetMix;
  dryLevel = dryMix;
  sampleRate = samRate;

  return;
}


//--------------------------------------------------------------
void Delayline::initDelayBuffer (float * lIn, float * lOut) {
	

	int delBuffLen = (int)(delayTime * sampleRate/1000);
		
	if(delBuffLen <= 0)
		printf(" DELAY BUFFER LENGTH IS NON_POSITIVE ");
		
	delayLineStart = new float [delBuffLen];			// for now make set length delay
		
	// set up pointers for the delay line
	delayLineEnd = delayLineStart + delBuffLen;
	readPtr = delayLineStart;	
	
	//zero out the buffer (silence)
	do {
		*readPtr = (float)0.0;
	}
	while (++readPtr < delayLineEnd);
	
	//reset read pointer to start of delayline
	readPtr = delayLineStart;
	
	// assign to left channel only for now - not sure this works !!	
	outputSignal = lOut;
	inputSignal = lIn;
	
	
	return;	
}


//--------------------------------------------------------------
void Delayline::writeToDelay (float *inL, float frameSize) {
	int s;
	for(s = 0; s < frameSize; s ++){
		 //get delayed sample
		delayLineOutput = *readPtr;

		//weight the delayed sample and the current input to create the output
		outputSignal[s] = dryLevel * inputSignal[s] + wetLevel * delayLineOutput;

		//write the input sample and any feedback to delayline
		*readPtr = inputSignal[s]  + feedbackGain * delayLineOutput;
	
		//increment buffer index and wrap if necesary
		if (++readPtr >= delayLineEnd)
			readPtr = delayLineStart;		
	}
	
	return;
}

//--------------------------------------------------------------
void Delayline::Cleanup(void)
{
  //Free memory allocated during initialization
  delete [] delayLineStart;
}

