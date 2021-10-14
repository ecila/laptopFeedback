/*
 *  feeder.cpp
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "feeder.h"

feeder::feeder(float *inSig, float initTarget, float initRate,  float fSize) {
	gain = 0.0;
	peak = 0.0;
	rate = initRate;
	target = initTarget;
	frameSize = fSize;
}

float feeder::adjustGain (float *input)
{
	for(int i=0; i < frameSize; i ++){
		if(fabs(input[i] > peak))
			peak = fabs(input[i]);
	}
	if(peak * gain < target)
		gain += rate;
	else{
		gain -= (rate * 10.0);		
	}
	gain = fmin(gain, 0.0);	
	return gain;
}

/*
_peak = 0.0f;

		//first find peak amp in vector
		for(i = 0; i < in.length;i++)
			if(Math.abs(in[i]) > _peak)
				_peak = Math.abs(in[i]);
		_diff = Math.abs(_peak - _target);

		//then adjust gain according to current peak
		if((_peak*_gain) < _target){
			_gain += (_rate);
		}
		else{
			_gain -= (_rate * 10.0);
			if(_gain < 0.0f )		// prevent gain going negative
				_gain = 0.0f;
		}

		// then increase input by gain
		for(i = 0; i < in.length;i++)
			out[i] = in[i] * _gain;  
*/			
			