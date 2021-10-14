/*
 *  feeder.h
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// extends variable delay to include watt govenor riding input amplitude
#ifndef FEEDER_H
#define FEEDER_H

#include "vdelay.h"


class feeder{
public:
	feeder(float *inputSignal, float target, float rate, float fSize); 
	float adjustGain(float *input);

private:
	float gain;
	float peak;					// peak amp of each signal vector
	float rate;					// amount incremented/ decremented each time
	float target;				// target output amp (ie this will be the average over the vector)
	float frameSize;

};

#endif