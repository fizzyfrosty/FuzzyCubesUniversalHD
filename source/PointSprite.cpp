#include "PointSprite.h"


PointSprite::PointSprite(void)
{
	type = NONE;
}


PointSprite::~PointSprite(void)
{
}

void PointSprite::setType( int16 t )
{
	type = t;
}

void PointSprite::Render()
{
	if( playAnimation == true )
	{
		// SET THE IMAGE - specific to POINT SPRITE
		switch( type )
		{
		case FIFTY:
			image = pointsImage50;
			uWidth = 64;
			uHeight = 64;
			size.x = 64;
			size.y = 64;
			break;
		case ONE_HUNDRED:
			image = pointsImage100;
			uWidth = 64;
			uHeight = 64;
			size.x = 64;
			size.y = 64;
			break;
		case FIVE_HUNDRED:
			image = pointsImage500;
			uWidth = 64;
			uHeight = 64;
			size.x = 128;
			size.y = 128;
			break;
		case ONE_THOUSAND:
			image = pointsImage1000;
			uWidth = 64;
			uHeight = 64;
			size.x = 128;
			size.y = 128;
			break;
		case FIVE_THOUSAND:
			image = pointsImage5000;
			uWidth = 64;
			uHeight = 64;
			size.x = 128;
			size.y = 128;
			break;
		case TEN_THOUSAND:
			image = pointsImage10000;
			uWidth = 64;
			uHeight = 64;
			size.x = 128;
			size.y = 128;
			break;
		}

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
} // end of Render()

void PointSprite::set100PointsImage( CIw2DImage* i )
{
	pointsImage100 = i;
}

void PointSprite::set1000PointsImage( CIw2DImage* i )
{
	pointsImage1000 = i;
}

void PointSprite::set10000PointsImage( CIw2DImage* i )
{
	pointsImage10000 = i;
}

void PointSprite::set50PointsImage( CIw2DImage* i )
{
	pointsImage50 = i;
}

void PointSprite::set500PointsImage( CIw2DImage* i )
{
	pointsImage500 = i;
}

void PointSprite::set5000PointsImage( CIw2DImage* i )
{
	pointsImage5000 = i;
}

bool PointSprite::finishedRendering()
{
	if( loopCount >= repeatCount )
	{
		return true;
	}
	else
	{
		return false;
	}
}