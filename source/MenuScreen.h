#pragma once

#include "s3e.h"
#include "Sprite.h"
#include "TouchButton.h"

#include "IwGxFont.h"
#include <sstream>
#include <iostream>
#include <string>

using std::string;

#include <vector>

using std::vector;

class MenuScreen
{
public:
	MenuScreen(void);
	~MenuScreen(void);

	void Initialize( int16 t );
	void Terminate();
	void Update( bool trophies[], long highScore, int timeSeconds, int timeMinutes, int timeHours ); // for high score only
	void Update( bool gameOver );
	void Render();

	void setStartingPosition( int16 x, int16 y );
	void setEndingPosition( int16 x, int16 y );
	void setInterpolationTime( uint64 t );
	void setAcceleration( int16 accelLimit, int16 a );
	void setDeceleration( int16 decelLimit, int16 a );
	
	/*
	vector<TouchButton> button;
	vector<CIw2DImage*> buttonImage;
	vector<CIw2DImage*> buttonImage_pressed;

	vector<Sprite> buttonSprite;
	vector<Sprite> buttonSprite_pressed;
	int16 counter;
	*/

	// Button variables
	int buttonCount;

	const static int NUM_OF_TROPHIES = 5;
	bool trophies[NUM_OF_TROPHIES];

	long highScore;
	int timeSeconds;
	int timeMinutes;
	int timeHours;

	const static int NUM_OF_MAX_BUTTONS = 21;
	TouchButton button[NUM_OF_MAX_BUTTONS];

	Sprite buttonSprite[NUM_OF_MAX_BUTTONS];
	Sprite buttonSprite_pressed[NUM_OF_MAX_BUTTONS];

	CIw2DImage *buttonImageArray[NUM_OF_MAX_BUTTONS];
	CIw2DImage *buttonImageArray_pressed[NUM_OF_MAX_BUTTONS];

	Sprite buttonSpriteArray[NUM_OF_MAX_BUTTONS];
	Sprite buttonSpriteArray_pressed[NUM_OF_MAX_BUTTONS];

	// Background variables
	Sprite sprite;
	CIw2DImage* image;
	CIw2DImage *quitConfirmationImage2;
	int16 type;
	enum{ CHALLENGE, QFCHAMBER, STORY, HIGH_SCORE, CREDITS, TUTORIAL, QUIT_CONFIRMATION, QUESTION_MARK, NEW_STORY_CONFIRMATION };

	// Message variables for high score screen
	Sprite getTrophyMessages[NUM_OF_TROPHIES];
	Sprite gotTrophyMessages[NUM_OF_TROPHIES];

	CIw2DImage *getTrophyMessagesImages[NUM_OF_TROPHIES];
	CIw2DImage *gotTrophyMessagesImages[NUM_OF_TROPHIES];

	bool displayGetTrophyMessages[NUM_OF_TROPHIES];
	bool displayGotTrophyMessages[NUM_OF_TROPHIES];
};

