/*
 *  delay.h
 *  openFrameworks
 *
 *  Created by ecila on 9/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef ifndef DELAY_H
#define DELAY_H

class Delayline {
public:
	Delayline(float sampleRate, float time, float feedback, float wetMix, float dryMix);
	void initDelayBuffer(float * lIn, float * lOut);
	void writeToDelay(float *lIn, float frameSize);
	void Cleanup(void);
	float *outputSignal, *inputSignal;
	~Delayline();

//private:
	float sampleRate, delayTime, feedbackGain, wetLevel, dryLevel;
private:
	float * buffer, delayLineOutput;
	float * delayLineStart, * delayLineEnd, * readPtr;

};

#endif