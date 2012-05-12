#include "Sprite.h"


Sprite::Sprite(void)
{
	image = NULL;
	uWidth = 0;
	uHeight = 0;
	frameCounter = 0;

	fpsDelayCounter= 0;
	fpsDelayTime = 0;
	totalFrames = 0;

	loopCount = 0;
	repeatCount = 0;

	playAnimation = true;

	interpolateTranslation = false;

	velocity = CIwSVec2(0, 0);
	acceleration = CIwSVec2(0, 0);

	mode = DECELERATING;

	interpolateAlpha = false;
	startingAlpha = 0;
	endingAlpha = 0;
}

// destructor
Sprite::~Sprite(void)
{
}

Sprite& Sprite::operator=(const Sprite &s)
{
	this->position = s.position;
	this->topLeft = s.topLeft;
	this->size = s.size;
	this->regionOffset = s.regionOffset;
	this->regionSize = s.regionSize;
	this->image = s.image;
	this->uWidth = s.uWidth;
	this->uHeight = s.uHeight;

	this->playAnimation = s.playAnimation; // controls whether or not it is animating

	this->totalFrames = s.totalFrames; // if the user has specified an amount of frames to loop
	this->loopCount = s.loopCount; // the amount of times the animation has looped. used for repeating a limited number of times
	this->repeatCount = s.repeatCount; // repeatCount to be used in conjunction with loopCount externally.

	this->frameCounter = s.frameCounter; // keeps track of which frame animation is on	
	// these 2 may not be used
	this->fpsDelayCounter = s.fpsDelayCounter;
	this->fpsDelayTime = s.fpsDelayTime;

	this->interpolateTranslation = s.interpolateTranslation;
	this->velocity = s.velocity;
	this->acceleration = s.acceleration;
	this->endingPosition = s.endingPosition;
	this->a = s.a;
	this->v = s.v;
	this->mode = s.mode;

	this->interpolateAlpha = s.interpolateAlpha;
	this->startingAlpha = s.startingAlpha;
	this->endingAlpha = s.endingAlpha;
	this->deltaAlpha = s.deltaAlpha;

	return *this;
}


void Sprite::Render()
{
	// set the values for interpolating translation
	if( interpolateTranslation == true )
	{
		// debug
		// printf("interpolating...\n");
		bool interpolateX = true;
		bool interpolateY = true;

		
		// increment position
		if( position != endingPosition )
		{			
			position += velocity;

			/* debug
			printf("position is %d, %d \n", position.x, position.y );
			printf("velocity is %d, %d \n", velocity.x, velocity.y );
			printf("acceleration is %d, %d \n", acceleration.x, acceleration.y );
			*/

			if( mode == DECELERATING )
			{
				if( interpolateX == true && (sqrt( pow( endingPosition.x-position.x, 2) + pow( endingPosition.y-position.y, 2)) < decelerationLimit ) )
				{				
					velocity.x += acceleration.x;
				}

				if( interpolateY == true && (sqrt( pow( endingPosition.x-position.x, 2) + pow( endingPosition.y-position.y, 2)) < decelerationLimit ) )
				{
					velocity.y += acceleration.y;
				}
			}
			else if( mode == ACCELERATING )
			{
				velocity += acceleration;
				/*
				if( sqrt( pow( endingPosition.x-position.x, 2) + pow( endingPosition.y-position.y, 2)) < accelerationLimit  )
				{
					// do nothing if limit is reached
				}
				else
				{
					velocity += acceleration;
				}*/
			}
		}

		// Clamp position if endingPosition reached
		if( velocity.x <= 0 )
		{
			if( position.x <= endingPosition.x ) // if final x position reached
			{
				position.x = endingPosition.x;
				interpolateX = false;
			}
		}
		else if( velocity.x > 0 )
		{
			if( position.x >= endingPosition.x )
			{
				position.x = endingPosition.x;
				interpolateX = false;
			}
		}

		if( velocity.y <= 0 )
		{
			if( position.y <= endingPosition.y ) // if final y position reached
			{
				position.y = endingPosition.y;
				interpolateY = false;
			}
		}
		else if( velocity.y > 0 )
		{
			if( position.y >= endingPosition.y )
			{
				position.y = endingPosition.y;
				interpolateY = false;
			}
		}

		// shuts off interpolation
		if( interpolateX == false && interpolateY == false )
		{
			interpolateTranslation = false;
			// debug
			// printf("done interpolating. \n");
		}
	}

	if( interpolateAlpha == true )
	{
		// do nothing if alpha limit reached
		currentAlpha += deltaAlpha;
		if( endingAlpha > startingAlpha )
		{
			if( currentAlpha >= endingAlpha )
			{
				currentAlpha = endingAlpha;
			}
		}
		else if( startingAlpha > endingAlpha )
		{
			if( currentAlpha <= endingAlpha )
			{
				currentAlpha = endingAlpha;
			}
		}

		externalColor = Iw2DGetColour();
		CIwColour color = { 255, 255, 255, currentAlpha };
		Iw2DSetColour( color );
	}


	if( playAnimation == true )
	{
		// Set the topleft coordinate based on Sprite's center position and size to be drawn
		topLeft.x = position.x - size.x / 2;
		topLeft.y = position.y - size.y / 2;

		// just in case uHeight was not set, it means it's a square
		if( uHeight == 0 )
			uHeight = uWidth;

		// set the region size to be drawn on the screen. uWidth and uHeight are # of pixels
		regionSize.x = uWidth;
		regionSize.y = uHeight;

		// Calculate the pixel offset for region to be drawn
		int16 totalPixelWidth = image->GetWidth(); // the pixel width of the original image
		int16 totalPixelHeight = image->GetHeight(); // the pixel height of the original image
		int16 totalColumns = totalPixelWidth / uWidth; // the number of columns of entire image based on uwidth
		int16 totalRows = totalPixelHeight / uHeight; // the number of rows of entire image based on uheight

		int16 columnNumber = frameCounter % totalColumns; // column number is f % c. This works. Where framecounter starts at zero. x/y offsets also start at zero
		int16 rowNumber = frameCounter / totalColumns; // row number is f / c. This also works. Where frameCounter starts at zero. x/y offsets also start at zero 

		regionOffset.x = columnNumber * uWidth;
		regionOffset.y = rowNumber * uHeight;

		// DRAW THE IMAGE
		if( repeatCount != 0 ) // if there's a repeat count set
		{
			if( loopCount < repeatCount )
			{
				Iw2DDrawImageRegion( image, topLeft, size, regionOffset, regionSize );
			}
		}
		else // if no repeat count, render and animate indefinitely
		{
			Iw2DDrawImageRegion( image, topLeft, size, regionOffset, regionSize );
		}

		// allows for slowing fps.
		if( fpsDelayTime == 0 ) // if a delay time was not set, the frame does not increment and sprite does not animate
		{
			// no animation
			frameCounter = 0;
		}
		else if( fpsDelayTime == 1 ) // if delay time is 1, that means it animates at 1 frame per iteration. 
		{
			frameCounter++; // this is incrementing what frame is being rendered

			// WRAP the frame counter. END OF ANIMATION LOOP
			if( totalFrames != 0 )
			{
				if( frameCounter == totalFrames )
				{
					frameCounter = 0;
					loopCount++;
				}
			}		
			else if( frameCounter == totalColumns * totalRows ) // if frame counter reaches the lastFrame+1, set equal to first frame; lastFrame+1 = (totalC * totalR) because frameCounter starts at Zero													   
			{
				frameCounter = 0;
				loopCount++;
			}
			
		}
		else if( fpsDelayCounter % fpsDelayTime == 0 && fpsDelayCounter != 0 ) // if the loop has been delayed long enough to equal the delay time, increment frame
		{
			frameCounter++; // this is incrementing what frame is being rendered
		
			// WRAP the frame counter. END OF ANIMATION LOOP
			if( totalFrames != 0 )
			{
				if( frameCounter == totalFrames )
				{
					frameCounter = 0;
					loopCount++;
				}
			}		
			else if( frameCounter == totalColumns * totalRows ) // if frame counter reaches the lastFrame+1, set equal to first frame; lastFrame+1 = (totalC * totalR) because frameCounter starts at Zero													   
			{
				frameCounter = 0;
				loopCount++;
			}

			// WRAP the delay counter to prevent overflow
			fpsDelayCounter = 0;

			// CLAMP the loop count to prevent overflow
			if( loopCount >= 15000 )
			{
				loopCount = 15000;
			}

		}

		// SKIP A FRAME
		fpsDelayCounter++; // this ONLY affects the 3rd condition of the above if-statement
	} // end of if playAnimation == true

	if( interpolateAlpha == true )
	{
		Iw2DSetColour( externalColor );
	}
}

void Sprite::setPosition( int16 x, int16 y )
{
	position.x = x;
	position.y = y;
}

void Sprite::setSize( int16 w, int16 h )
{
	size.x = w;
	size.y = h;
}

void Sprite::setUWidth( int16 u )
{
	uWidth = u;
}

void Sprite::setUHeight( int16 h )
{
	uHeight = h;
}

void Sprite::setImage( CIw2DImage* i )
{
	image = i;
}

void Sprite::setDelayTime( int16 t )
{
	fpsDelayTime = t;
}

void Sprite::setTotalFrames( int16 f )
{
	totalFrames = f;
}

void Sprite::setRepeatCount( int16 n )
{
	repeatCount = n;
}

void Sprite::resetAndPlayAnimation()
{
	frameCounter = 0;
	fpsDelayCounter= 0;
	loopCount = 0;
}

void Sprite::setStartingPosition( int16 x, int16 y )
{
	position.x = x;
	position.y = y;

	interpolateTranslation = true;
}

void Sprite::setEndingPosition( int16 x, int16 y )
{
	endingPosition.x = x;
	endingPosition.y = y;
}

void Sprite::setInterpolationTime( uint64 ms )
{
	// calculates the velocity for translation
	if( interpolateTranslation == true )
	{
		// (displacement)/(X ms) * (1000ms)/(30f) = is the deltaValue per frame
		CIwSVec2 displacement = endingPosition - position;
		velocity = displacement*1000 / (ms*30);
	}

	/*
	if( interpolateTranslation == true )
	{
		// (displacement)/(X ms) * (1000ms)/(30f) = is the deltaValue per frame
		CIwSVec2 displacement = endingPosition - position;

		double t = ms / 1000.0;

		double d = sqrt( pow(displacement.x, 2) + pow(displacement.y, 2 ) );
		a = -2*d / (t*t); // acceleration
		v = -a*t; // initial velocity
		
		velocity.y = v/30;
		acceleration.y = a/30;

		printf("d is %f, v0 is %f, a is %f \n", d, v, a );
	}
	*/
}

void Sprite::setAcceleration( int16 accelLimit, int16 a )
{
	if( interpolateTranslation == true )
	{
		accelerationLimit = accelLimit;

		double theta = atan( (double)velocity.y / (double)velocity.x ) ;
		double accelX = a * cos( theta );
		double accelY = a * sin( theta );

		acceleration.x = (int16)accelX;
		acceleration.y = (int16)accelY;
		
		// reset velocity
		velocity.x = 0;
		velocity.y = 0;

		mode = ACCELERATING;

	}
}

void Sprite::setDeceleration( int16 decelLimit, int16 a )
{
	if( interpolateTranslation == true )
	{
		decelerationLimit = decelLimit;

		double theta = atan( (double)velocity.y / (double)velocity.x ) ;
		double accelX = a * cos( theta );
		double accelY = a * sin( theta );

		acceleration.x = (int16)accelX;
		acceleration.y = (int16)accelY;

		mode = DECELERATING;
	}
}

void Sprite::setStartingAlpha( int16 a )
{
	startingAlpha = a;
	currentAlpha = a;

	interpolateAlpha = true;
}

void Sprite::setEndingAlpha( int16 a )
{
	endingAlpha = a;
}

void Sprite::setAlphaInterpolationTime( uint64 ms )
{
	if( interpolateAlpha == true )
	{
		deltaAlpha = ((double)endingAlpha - (double)startingAlpha);
		deltaAlpha = deltaAlpha*1000 / (ms*30);
	}
}