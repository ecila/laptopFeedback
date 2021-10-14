/*
 *  vdelay.h
 *  openFrameworks
 *
 *  Created by ecila on 9/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 /*********************************************************

Vdelay.h - A variable delay unit with linear interpolation

Copyright (c) 1998, Scott Lehman, slehman@harmony-central.com
This code may be used and modified freely provided that credit
is given to the author in any public release. Any derivative
programs must be distributed freely and/or the modified source
code made publicly available.  All code is provided AS IS and
without warranty of any kind.
*********************************************************/

#include "envelope.h"
#include "wattGain.h"

#ifndef VDELAY_H
#define VDELAY_H

class Vdelay {
public:
	Vdelay(int sampleRate, int fSize, float maxDelay, float initDelay, float feedback, float wetMix, float dryMix);
	void initDelayBuffer(float * In, float * Out);
	void writeToDelay(float *lIn, float frameSize);
	void Clear(void);					// *** TO DO fix this !
	void Cleanup(void);
	float *outputSignal, *inputSignal;			// pointers for reading/writing to delay line
	int maxDelay, currentFixedDelay;			// variable delay length
	float wattGovernedGain;						// controlled by watt govenor
	envelope *env;								// envelope (line~) for controlling delay line length
	wattGain *watt;								// watt govenor
	float deviation;							// diff twix target and actual (should be in watt)
	~Vdelay();

private:
	float feedbackGain, wetLevel, dryLevel;		// currently not used
	float * currentDelay ;						// pointer to variable signal for controlling delay time

	float  delayLineOutput;								// holds sample val for loc in delayline
	float * delayLineStart, * delayLineEnd,  * writePtr;
	int s, delayLineLength, sampleRate;
};

#endif