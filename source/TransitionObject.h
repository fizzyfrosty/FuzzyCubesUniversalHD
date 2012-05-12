#pragma once
#include "s3e.h"
#include "IwGx.h"
#include "Sprite.h"
#include "Iw2D.h"

class TransitionObject
{
public:
	TransitionObject(void);
	~TransitionObject(void);

	void Initialize();
	void Terminate();
	void Render();

	void setTransition( int16 col, int16 st, int16 t );
	bool isFinished();

	int16 color;
	enum{ WHITE, BLACK };
	int16 state;
	enum{ NO_TRANSITION, FADEIN, FADEOUT };

	const static int16 numOfOverlays = 2;
	Sprite transitionSprite[numOfOverlays];
	CIw2DImage *transitionImage[numOfOverlays];

};

