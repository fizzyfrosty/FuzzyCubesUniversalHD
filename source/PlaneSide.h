#pragma once
#include "s3e.h"

class PlaneSide
{
public:
	PlaneSide(void);
	PlaneSide( int16 dir, int16 col );


	~PlaneSide(void);

	// overloaded assignment operator
	PlaneSide & operator=(const PlaneSide & ps ); 

	void copyCountAndMat(PlaneSide ps);
	void reset();
	void resetCounts();

	int16 direction;
	int16 color;
	enum { RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE };
	int16 count; // the number of cubes touching the plane
	int16 winCount; // number of times the plane was completed
	int16 highestLayerLevel; // used for easier cameraDepth autoadjusting
	bool beganWarping;
	int16 warpingMaterialIntensity;
	int16 warpingDelayTime;
	bool warpingUp;
	bool warped; // used b/c cubes had to delay removal from data structure after finish warping
	bool active; // active is used to determine if cubes are spawned for that corresponding side color
	bool allowSingleCubeSpawn;
};

