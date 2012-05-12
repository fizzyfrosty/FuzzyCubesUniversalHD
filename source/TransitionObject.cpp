#include "TransitionObject.h"


TransitionObject::TransitionObject(void)
{
}


TransitionObject::~TransitionObject(void)
{
}

void TransitionObject::Initialize()
{
	color = WHITE;
	state = NO_TRANSITION;

	for( int i = 0; i < numOfOverlays; i++ )
	{
		
		transitionSprite[i].setUWidth( 480 );
		transitionSprite[i].setUHeight( 320 );
		transitionSprite[i].setSize( 480, 320 );

		switch( i )
		{
		case 0:
			transitionImage[i] = Iw2DCreateImage( "white.png" );
			break;
		case 1:
			transitionImage[i] = Iw2DCreateImage( "black.png" );
			break;
		case 2:
			break;
		}
		
		transitionSprite[i].setImage( transitionImage[i] );
		transitionSprite[i].setDelayTime( 1 );
		transitionSprite[i].setPosition( IwGxGetScreenWidth()/2, IwGxGetScreenHeight()/2 );
	}

}

void TransitionObject::Terminate()
{
	for( int i = 0; i < numOfOverlays; i++ )
	{
		delete transitionImage[i];
	}
}

void TransitionObject::Render()
{
	switch( color )
	{
	case WHITE:
		if( isFinished() == false )
		{
			transitionSprite[0].Render();
		}
		break;
	case BLACK:
		if( isFinished() == false )
		{
			transitionSprite[1].Render();
		}
		break;
	}
}

void TransitionObject::setTransition( int16 col, int16 st, int16 t )
{
	color = col;
	state = st;

	switch( color )
	{
	case WHITE:
		if( state == FADEIN )
		{
			transitionSprite[0].setStartingAlpha( 255 );
			transitionSprite[0].setEndingAlpha( 0 );
			transitionSprite[0].setAlphaInterpolationTime( t );
		}
		else if( state == FADEOUT )
		{
			transitionSprite[0].setStartingAlpha( 0 );
			transitionSprite[0].setEndingAlpha( 255 );
			transitionSprite[0].setAlphaInterpolationTime( t );
		}
		break;
	case BLACK:
		if( state == FADEIN )
		{
			transitionSprite[1].setStartingAlpha( 255 );
			transitionSprite[1].setEndingAlpha( 0 );
			transitionSprite[1].setAlphaInterpolationTime( t );
		}
		else if( state == FADEOUT )
		{
			transitionSprite[1].setStartingAlpha( 0 );
			transitionSprite[1].setEndingAlpha( 255 );
			transitionSprite[1].setAlphaInterpolationTime( t );
		}
		break;

	}
}

bool TransitionObject::isFinished()
{
	switch( color )
	{
	case WHITE:
		if( state == FADEIN )
		{
			// fading in, the ending alpha should be zero
			if( transitionSprite[0].currentAlpha == transitionSprite[0].endingAlpha && transitionSprite[0].endingAlpha == 0 )
			{
				return true;
			}
		}
		else if( state == FADEOUT )
		{
			// fading out, the ending alpha should be 255
			if( transitionSprite[0].currentAlpha == transitionSprite[0].endingAlpha && transitionSprite[0].endingAlpha == 255 )
			{
				return true;
			}
		}
		break;
	case BLACK:
		if( state == FADEIN )
		{
			// fading in, the ending alpha should be zero
			if( transitionSprite[1].currentAlpha == transitionSprite[1].endingAlpha && transitionSprite[1].endingAlpha == 0 )
			{
				return true;
			}
		}
		else if( state == FADEOUT )
		{
			// fading out, the ending alpha should be 255
			if( transitionSprite[1].currentAlpha == transitionSprite[1].endingAlpha && transitionSprite[1].endingAlpha == 255 )
			{
				return true;
			}
		}
		break;
	}

	return false;
}
