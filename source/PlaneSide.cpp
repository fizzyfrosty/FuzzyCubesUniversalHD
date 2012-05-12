#include "PlaneSide.h"


PlaneSide::PlaneSide(void)
{
}

PlaneSide::PlaneSide(int16 dir, int16 col)
{
	direction = dir;
	color = col;
	count = 0;
	beganWarping = false;
	warpingMaterialIntensity = 0;
	warpingDelayTime = 0;
	warpingUp = true;
	warped = false;
	active = true;
	winCount = 0;
	highestLayerLevel = 0;

	allowSingleCubeSpawn = true;
}

PlaneSide::~PlaneSide(void)
{
}

PlaneSide& PlaneSide::operator=(const PlaneSide &ps)
{
	this->direction = ps.direction;
	this->color = ps.color;
	this->count = ps.count;
	this->beganWarping = ps.beganWarping;
	this->warpingMaterialIntensity = ps.warpingMaterialIntensity;
	this->warpingDelayTime = ps.warpingDelayTime;
	this->warpingUp = ps.warpingUp;
	this->warped = ps.warped;
	this->active = ps.active;
	this->winCount = ps.winCount;
	this->highestLayerLevel = ps.highestLayerLevel;
	this->allowSingleCubeSpawn = ps.allowSingleCubeSpawn;
	return *this;
}

void PlaneSide::copyCountAndMat(PlaneSide ps)
{
	color = ps.color;
	count = ps.count;
	beganWarping = ps.beganWarping;
	warpingMaterialIntensity = ps.warpingMaterialIntensity;
	warpingDelayTime = ps.warpingDelayTime;
	warpingUp = ps.warpingUp;
	warped = ps.warped;
	active = ps.active;
	winCount = ps.winCount;
	highestLayerLevel = ps.highestLayerLevel;
	allowSingleCubeSpawn = ps.allowSingleCubeSpawn;
}

void PlaneSide::reset()
{	
	count = 0;
	beganWarping = false;
	warpingMaterialIntensity = 0;
	warpingUp = true;
	winCount = 0;
	highestLayerLevel = 0;
	warped = false;
	allowSingleCubeSpawn = true;
}

void PlaneSide::resetCounts()
{
	count = 0;
	winCount = 0;
	highestLayerLevel = 0;
}