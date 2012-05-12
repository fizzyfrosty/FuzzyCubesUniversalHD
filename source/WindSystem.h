#pragma once

#include "IwGx.h"
#include "WindStreak.h"

class WindSystem
{
public:
	WindSystem(void);
	~WindSystem(void);

	void Initialize( int16 s );
	void Terminate();
	void Update( CIwMat modelMatrix );
	void Render();

	const static int16 NUM_OF_WINDSTREAKS = 40;
	WindStreak windStreaks[NUM_OF_WINDSTREAKS];
};

