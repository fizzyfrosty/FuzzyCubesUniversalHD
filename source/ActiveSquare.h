#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"

#pragma once
class ActiveSquare
{
public:

	void Initialize( int16 t ); // initializes with type to determine color and coordinate
	void Update( bool active, bool exists, int16 increm );
	void Render();
	void Terminate();

	int16 type;
	enum{ BLUE, RED, YELLOW, ORANGE, GREEN, PURPLE };
	CIw2DImage* image;
	CIw2DImage* blankImage;
	CIwColour color;
	int16 red, blue, green, alpha; // channels are split b/c only alpha is tweaked
	int16 intensity, increment, plusMinusIndex;
	int16 x, y;
	int16 width, height;
	bool activated; // determines whether or not to display color image or null material image
	bool fallingCubeExists; // dictates the alpha value of the activated image. Darker if cube is falling, lighter if not

	ActiveSquare(void);
	~ActiveSquare(void);
};

