#pragma once
#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include "math.h"

class Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	// overloaded assignment operator
	Sprite & operator=(const Sprite & s ); 

	void Render();
	// functions that MUST be set:
	void setPosition( int16 x, int16 y ); // this is set in Update() continuously
	void setSize( int16 w, int16 h ); // the size of the actual image rendered on the screen
	void setUWidth( int16 u );
	void setUHeight( int16 h ); // these are the amount of image that is rendered
	void setImage( CIw2DImage* i );

	// functions that are optional:
	void setDelayTime( int16 t );
	void setTotalFrames( int16 f );
	void setRepeatCount( int16 n ); // default is infinite
	void setPlayAnimation( bool start ); // default is true. acts as pause/resume
	void resetAndPlayAnimation(); // resets animation

	// functions for translation interpolation
	void setStartingPosition( int16 x, int16 y );
	void setEndingPosition( int16 x, int16 y );
	void setInterpolationTime( uint64 ms );
	void setAcceleration( int16 accelLimit, int16 a );
	void setDeceleration( int16 decelLimit, int16 a );
	bool interpolateTranslation;
	double a;
	double v;
	CIwSVec2 velocity;
	CIwSVec2 acceleration;
	CIwSVec2 endingPosition;
	int16 accelerationLimit; // the point at which acceleration should start to take place
	int16 decelerationLimit; // the point at which acceleration should start to take place
	int16 mode;
	enum{ ACCELERATING, DECELERATING };

	// functions for opacity interpolation
	void setStartingAlpha( int16 a );
	void setEndingAlpha( int16 a );
	void setAlphaInterpolationTime( uint64 ms );
	bool interpolateAlpha;
	int16 startingAlpha;
	int16 endingAlpha;
	int16 currentAlpha;
	double deltaAlpha;
	CIwColour externalColor;

	CIwSVec2 position;
	CIwSVec2 topLeft;
	CIwSVec2 size;
	CIwSVec2 regionOffset;
	CIwSVec2 regionSize;
	CIw2DImage* image;
	int16 uWidth;
	int16 uHeight;

	bool playAnimation; // controls whether or not it is animating

	int16 totalFrames; // if the user has specified an amount of frames to loop
	int16 loopCount; // the amount of times the animation has looped. used for repeating a limited number of times
	int16 repeatCount; // repeatCount to be used in conjunction with loopCount externally.

	int16 frameCounter; // keeps track of which frame animation is on	
	// these 2 may not be used
	int16 fpsDelayCounter;
	int16 fpsDelayTime;
};

