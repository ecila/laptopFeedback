/*
 *  envelope.h
 *  openFrameworks
 *
 *  Created by ecila on 10/09/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ENVELOPE_H
#define ENVELOPE_H

class envelope {
public:
	envelope(int sampleRate, int frameSize, float envStart, float envEnd, float envCurrent, int envTime);
	float start;
	float *buffer;
	int time;
	void envGenerate(float envCurrent);
	void setEnvelope();
	void setTarget(float target, float max);
	float getCurrent();
	void setCurrent(float val);

	~envelope();
	
private:	
	int sampleRate;
	int frameSize;
	float current, destination;	
	
};
#endif

