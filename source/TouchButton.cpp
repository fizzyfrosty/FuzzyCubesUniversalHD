#include "TouchButton.h"


TouchButton::TouchButton(void)
{
	pressed = false;
	initialPressed = false;
	enabled = true;

	x = 0;
	y = 0;
}


TouchButton::~TouchButton(void)
{
}

bool TouchButton::isPressed( int16 x, int16 y )
{
	if( enabled == true )
	{
		// sets the hitbox for the button, determines if it's pressed
		if( x > this->x - hitboxWidth/2 && x < this->x + hitboxWidth/2  && y > this->y - hitboxHeight/2 && y < this->y + hitboxHeight/2 )
			return true;
		else
			return false;
	}
	else
	{
		return false; // set as not touched if false
	}
}

void TouchButton::Render()
{
	if( enabled == true ) // only render if the button is enabled
	{
		if( pressed == false )
		{
			unpressedSprite.setPosition( x, y );
			unpressedSprite.Render();
		}
		else if( pressed == true )
		{
			pressedSprite.setPosition( x, y );
			pressedSprite.Render();
		}
	}
}

void TouchButton::setLocation( int16 x, int16 y )
{
	this->x = x;
	this->y = y;
}

void TouchButton::setTouchSize( int16 w, int16 h )
{
	hitboxWidth = w;
	hitboxHeight = h;
}

void TouchButton::setRenderSize( int16 w, int16 h )
{
	pressedSprite.setSize( w, h );
	unpressedSprite.setSize( w, h );
}

void TouchButton::setUnpressedSprite( Sprite s )
{
	unpressedSprite = s;
}

void TouchButton::setPressedSprite( Sprite s )
{
	pressedSprite = s;
}