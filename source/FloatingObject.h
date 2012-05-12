#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include "IwRandom.h"
#include "Sprite.h"

class FloatingObject
{
public:
	FloatingObject(void);
	~FloatingObject(void);
	void Initialize( int16 t );
	void Update(int16 screenWidth, int16 screenHeight); // this updates the floating object's position
	void Render(); // this renders the sprites if they aren't null
	void setSize(int16 x, int16 y);
	bool isTouched( int16 x, int16 y ); // used in touch button method in global.
	int16 getState(); // determines how the outside states are affected

	void makePoof(); // sets state to poof
	void makeTransition(); // sets state to transition

	Sprite mainSprite; // this is loaded outside of this object
	Sprite transitionSprite; // this is loaded outside of this object
	Sprite poofSprite; // this is loaded outside of this object. Poof is when it disappears with nothing activated

	int16 state; // the state dictates how it is being updated and used for the getState() to influence outside behavior
	enum { FLOATING, TRANSITION, POOF, DEAD, RETURN_LIFE, ENABLE_SLOWMO, RETURN_SHIPPART };
	int16 type;
	enum { EXTRA_LIFE, SLOW_MO, SHIP_PART };
	CIwSVec2 velocity;
	CIwSVec2 position;
	CIwSVec2 size;
	int16 rotateValue; // degrees/value that the object rotates by
	int16 rotateDirection; // determines whether the object rotates clockwise or CCwise. negative is counter clockwise rotation, pos is clockwise

	int64 time0, time1; // these are helper variables to determine how long object has lived
	int64 lifeTime; // this is how long (in seconds) the object has lived. 
	int64 expirationTime; // this is how long the object has to live

	int16 transitionCounter; // used to count the number of frames played for transitions to determine 1 iteration of animation
	int16 poofCounter;
	bool touched;
	bool activated; // used for whether or not it is updated/rendered in fuzzycubes.cpp
};

