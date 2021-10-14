/*
 *  feeder.cpp
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __alice__. All rights reserved.
 *
 */

#include "wattGain.h"

wattGain::wattGain(int fSize, float initTarget, float initRate) {
	gain = 1.0;
	peak = 0.0;
	rate = initRate;
	target = initTarget;
	frameSize = fSize;
}


//--------------------------------------------------------------
// calculate new gain to maintain constant peak amp
float wattGain::getNewGain (float *input)
{
	peak = getPeak(input);
	
	if((peak) < target)
		gain += rate;
	else if(peak > target){
		gain -= (rate * 10.0);		
	}
	
//	gain = fmax(gain, 0.0);
	if(gain < 0.0f)
		gain = 0.0f;
	
	return gain;
}



//--------------------------------------------------------------
// return deviations above target with random sign
float wattGain::getNewDelayTime(float *input)
{
	double r = 0.0;
	float diff = 0.0;
	
	if(getPeak(input) > target){
		r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
		r-= 0.5;
		r < 0 ? r = -1.0 : r = 1.0;
		diff = (peak - target) * (float)r;
	}
	
	return diff;
	
}

//--------------------------------------------------------------
float wattGain::getAmpDeviationFromTarget (float *input)
{
	peak = 0.0;
		
	for(int i=0; i < frameSize; i ++){
		if(fabs(input[i] > peak))
			peak = fabs(input[i]);
	}
	
	return (peak - target);
}

//--------------------------------------------------------------
float wattGain::getPeak(float *input)		
{
	peak = 0.0;
		
	for(int i=0; i < frameSize; i ++){
		if(fabs(input[i] > peak))
			peak = fabs(input[i]);
	}
	return peak;
}

//--------------------------------------------------------------
float wattGain::getPeak()		
{

	return peak;
}
			
