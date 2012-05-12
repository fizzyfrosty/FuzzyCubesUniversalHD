#include "ShadowGroup.h"


ShadowGroup::ShadowGroup(void)
{
	direction = 0;
	dropCubes = false;
	dropCubesSlow = false;
	updatedBounds = false;
	moveable = true;

	firstCubeLanded = false;
	startSlowingDown = false;
	scoredPoints = false;
	landed = false;

	topBound = NULL;
	bottomBound = NULL;
	leftBound = NULL;
	rightBound = NULL;
}

ShadowGroup::ShadowGroup(int16 dir)
{
	direction = dir;
	dropCubes = false;
	dropCubesSlow = false;
	updatedBounds = false;
	moveable = true;
	startSlowingDown = false;

	firstCubeLanded = false;
	scoredPoints = false;
	landed = false;

	topBound = NULL;
	bottomBound = NULL;
	leftBound = NULL;
	rightBound = NULL;
}


ShadowGroup::~ShadowGroup(void)
{
	topBound = NULL;
	bottomBound = NULL;
	leftBound = NULL;
	rightBound = NULL;
}
