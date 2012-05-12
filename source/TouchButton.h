#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include "Sprite.h"


class TouchButton
{
public:
	TouchButton(void);
	// Initialize with a texture
	~TouchButton(void);

	bool isPressed( int16 x, int16 y ); // for some reason, this only works for high values, with s > 500/600. Oh that's b/c of the normal.z comparison. I have it as a huge number
	void setLocation( int16 x, int16 y ); // set in Update() continuously 

	// New methods after re-implementation
	void setTouchSize( int16 w, int16 h );
	void setRenderSize( int16 w, int16 h );
	void setUnpressedSprite( Sprite s );
	void setPressedSprite( Sprite s );
	void Render();


	bool pressed;
	bool initialPressed;

	// these hold all of the rendering data. initialized separately
	// initialize the sprite before assigning to button
	Sprite unpressedSprite;
	Sprite pressedSprite;

	int16 x, y;
	int16 hitboxWidth, hitboxHeight;
	bool enabled; // used for displaying/being activated

};

