/*
 *  wattGain.h
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// extends variable delay to include watt govenor riding input amplitude
#ifndef WATTGAIN_H
#define WATTGAIN_H


class wattGain{
public:
	wattGain(int fSize,  float target, float rate); 
	float getNewGain(float *input);
	float getNewDelayTime(float *input);	
	float getAmpDeviationFromTarget (float *input);

	float getPeak(float *input);
	float getPeak(void);
	

	float gain;
	float peak;					// peak amp of each signal vector
	float target;				// target output amp (ie this will be the average over the vector)
	
private:
	float rate;					// amount incremented/ decremented each time
	int frameSize;

};

#endif