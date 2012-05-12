#pragma once
#include "s3e.h"
#include "IwGx.h"

class Shadow;

class ShadowGroup
{
public:
	ShadowGroup(void);
	ShadowGroup( int16 dir );
	~ShadowGroup(void);

	// this boolean helps tell whether or not all cubes 
	// connected to the shadows connected to this 
	// shadow group should be dropped or not
	bool dropCubes; 
	bool dropCubesSlow;
	bool updatedBounds;
	bool moveable;
	bool startSlowingDown;
	bool landed;

	bool firstCubeLanded; // used for sound effect playback, just once per set
	bool scoredPoints;

	int16 direction;

	int16 topBound;
	int16 bottomBound;
	int16 leftBound;
	int16 rightBound;
	/*
	Shadow* topBound;
	Shadow* bottomBound;
	Shadow* leftBound;
	Shadow* rightBound;
	*/
};

