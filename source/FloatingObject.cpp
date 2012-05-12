#include "FloatingObject.h"


FloatingObject::FloatingObject(void)
{
	state = FLOATING;
	transitionCounter = 0;
	poofCounter = 0;

	IwRandSeed( (int32)s3eTimerGetMs() );
	do
	{
		velocity.x = IwRandMinMax( -2, 2 + 1 ); // generates speed between 1-10 for y
		velocity.y = IwRandMinMax( -2, 2 + 1 );
	}
	while (velocity.x == 0 || velocity.y == 0 ); // x and y cannot be zero
	position.x = 50;
	position.y = 50;

	size.x = 0;
	size.y = 0;

	rotateValue = 1;
	rotateDirection = 1; // positive is clockwise, negative is counter clockwise rotation

	activated = false;
}


FloatingObject::~FloatingObject(void)
{
}


void FloatingObject::Initialize( int16 t )
{
	type = t;
	transitionCounter = 0;
	poofCounter = 0;
	state = FLOATING;

	time0 = 0;
	time1 = 0;

	lifeTime = 0;
	expirationTime = 0;

	activated = false;

	// need to generate spawn position
	IwRandSeed( (int32)s3eTimerGetMs() );
	int16 spotLocation = IwRandMinMax( 1, 4+1 );
	if( spotLocation == 1 ) // location1 is the west side offscreen
	{
		// set the location
		position.x = 0 - size.x;
		position.y = 0 + IwGxGetScreenHeight()/2;

		// set the velocity
		do
		{
			velocity.x = IwRandMinMax( 1, 2 + 1 ); // x direction must be positive
			velocity.y = IwRandMinMax( -2, 2 + 1 );
		}
		while (velocity.x == 0 || velocity.y == 0 ); // x and y cannot be zero
	}
	else if( spotLocation == 2 ) // location2 is north side off screen
	{
		// set the location
		position.x = 0 + IwGxGetScreenWidth()/2;
		position.y = 0 - size.y;

		// set the velocity
		do
		{
			velocity.x = IwRandMinMax( -2, 2 + 1 ); 
			velocity.y = IwRandMinMax( 1, 2 + 1 ); // y direction must be positive
		}
		while (velocity.x == 0 || velocity.y == 0 ); // x and y cannot be zero
	}
	else if( spotLocation == 3 ) // location3 is east side off screen
	{
		// set the location
		position.x = IwGxGetScreenWidth() + size.x;
		position.y = 0 + IwGxGetScreenHeight()/2;

		// set the velocity
		do
		{
			velocity.x = IwRandMinMax( -2, -1 + 1 );  // x direction must be negative
			velocity.y = IwRandMinMax( -2, 2 + 1 ); 
		}
		while (velocity.x == 0 || velocity.y == 0 ); // x and y cannot be zero
	}
	else if( spotLocation == 4 ) // location4 is south side off screen
	{
		// set the location
		position.x = 0 + IwGxGetScreenWidth()/2;
		position.y = IwGxGetScreenHeight() + size.y;

		// set the velocity
		do
		{
			velocity.x = IwRandMinMax( -2, 2 + 1 ); 
			velocity.y = IwRandMinMax( -2, -1 + 1 );  // y direction must be negative
		}
		while (velocity.x == 0 || velocity.y == 0 ); // x and y cannot be zero
	}

	if( type == EXTRA_LIFE )
	{
		expirationTime = 10; // will poof in 10 seconds
	}
	else if( type == SLOW_MO )
	{
	}
	else if( type == SHIP_PART )
	{
	}
}

// updates position
void FloatingObject::Update( int16 screenWidth, int16 screenHeight )
{
	// determine the object's current life length
	time0 = time1;
	time1 = s3eTimerGetMs() / 1000;
	if( time1 - time0 == 1 )
		lifeTime++; // increment life time variable if one second has passed;

	if( lifeTime >= expirationTime )
	{
		state = POOF;
	}
	
	// Rotate the object
	if( rotateDirection < 0 )
		rotateValue -= 20; // negative is counter clockwise rotation
	else if( rotateDirection > 0 )
		rotateValue += 20;

	if( rotateValue > 4096 || rotateValue < -4096 )
		rotateValue %= 4096;

	position.x += velocity.x;
	position.y += velocity.y;

	// clamp the positions if hits border and invert the velocity of that line of axis
	if(  velocity.x < 0 && (position.x - size.x/2 <= 0) ) // if the xVelocity is negative and the position hits the left side
	{
		position.x = size.x/2;
		velocity.x *= -1;

		// set rotation direction
		if( velocity.y < 0 )
			rotateDirection = -1;
		else
			rotateDirection = 1;
	}

	if( velocity.x > 0 && (position.x + size.x/2 >= screenWidth ) ) // if hits the right side
	{
		position.x = IwGxGetScreenWidth() - size.x/2;
		velocity.x *= -1;

		// set rotation direction
		if( velocity.y < 0 )
			rotateDirection = 1;
		else
			rotateDirection = -1;
	}

	if( velocity.y < 0 && (position.y - size.y/2 <= 0 ) ) // if hits the top side
	{
		position.y = size.y/2;
		velocity.y *= -1;

		// set rotation direction
		if( velocity.x < 0 )
			rotateDirection = 1;
		else
			rotateDirection = -1;
	}

	if( velocity.y > 0 && (position.y + size.y/2 >= screenHeight ) ) // if hits the bottom side
	{
		position.y = IwGxGetScreenHeight() - size.y/2;
		velocity.y *= -1;

		// set rotation direction
		if( velocity.x < 0 )
			rotateDirection = -1;
		else
			rotateDirection = 1;
	}

	// update sprites for rendering
	if( mainSprite.image != NULL )
	{
		mainSprite.setPosition( position.x, position.y );
		mainSprite.setSize( size.x, size.y );
	}

	if( transitionSprite.image != NULL )
	{
		transitionSprite.setPosition( position.x, position.y );
		transitionSprite.setSize( size.x, size.y );
	}

	if( poofSprite.image != NULL )
	{
		poofSprite.setPosition( position.x, position.y );
		poofSprite.setSize( size.x, size.y );
	}


	// check the TransitionCounter to see if transitioning out finished playing
	if( transitionCounter == 60 )
	{
		// set the state to whatever the type is
		state = DEAD;
	}

	if( poofCounter == 60 ) // if poofed, make it nonexistent. place in limbo. 
	{
		state = DEAD; // will not render
	}
}


// make sure to account for null value of the sprite -> ciw2dimage
void FloatingObject::Render()
{
	CIwMat2D rot;
	rot.SetRot( rotateValue, (CIwVec2)position );
	Iw2DSetTransformMatrix( rot );

	if( state == FLOATING )
	{
		if( mainSprite.image != NULL )
		{
			mainSprite.Render();
		}
	}

	if( state == TRANSITION )
	{
		if( transitionSprite.image != NULL )
		{
			transitionSprite.Render();
			transitionCounter++;
		}
	}

	if( state == POOF )
	{
		if( poofSprite.image != NULL )
		{
			poofSprite.Render();
			poofCounter++;
			printf("poofing!");
		}
	}

	Iw2DSetTransformMatrix( CIwMat2D::g_Identity );
}

void FloatingObject::setSize( int16 x, int16 y )
{
	size.x = x;
	size.y = y;
}

int16 FloatingObject::getState()
{
	return state;
}

bool FloatingObject::isTouched( int16 x, int16 y )
{
	// sets the hitbox for the button, determines if it's pressed
	if( x > position.x - size.x/2 && x < position.x + size.x/2  && y > position.y - size.y/2 && y < position.y + size.y/2 )
	{
		return true;
	}
	else
		return false;
}

void FloatingObject::makePoof()
{
	// if the floating object is touched
	state = POOF;
}

void FloatingObject::makeTransition()
{
	state = TRANSITION;
}