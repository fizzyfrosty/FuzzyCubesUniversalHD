#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "math.h"
#include "Cube.h"
#include "ShadowGroup.h"

class ShadowGroup;
class Cube;

class Shadow
{
public:
	Shadow(void);
	Shadow( int16 dir );
	Shadow( int16 dir, int16 sideLength );
	void linkCube( Cube* c );
	void setDirection( int16 d );
	bool isTouched( int16 x, int16 y ); // for some reason, this only works for high values, with s > 500/600. Oh that's b/c of the normal.z comparison. I have it as a huge number
	void setModelMatrix( CIwMat mm );
	void setTouchIntersection( int16 x, int16 y ); // obsolete
	void convertToGridLocation( int16 widthUnits, int16 heightUnits, int16 depthUnits ); // obsolete but use this limit calculation for new method
	void setSpawnPosition( CIwSVec3 pos );

	//Shadow & operator=(const Shadow & shadow ); 

	CIwSVec3 getDeltaTranslation();
	enum sideType {ODD, EVEN};

	~Shadow(void);


	// variables
	CIwSVec3 position;
	CIwSVec3 initialPosition; // used for shadowBounds
	CIwSVec3 spawnPosition; // used for rotating. this is NEVER touched after initialization
	CIwSVec3 deltaDistance;	
	int16 direction;
	int16 s; // the side length of the shadow
	int16 tapTime; // used to see how long the shadow was touched
	bool touched;
	bool spawnPositionSet;
	CIwMat modelmatrix;

	Cube* cube;
	Shadow* neighbor1;
	Shadow* neighbor2;
	Shadow* neighbor3;
	Shadow* neighbor4;

	ShadowGroup* shadowGroup;

	CIwSVec3 point1, point2, point3, point4;
	CIwSVec3 point1Translated, point2Translated, point3Translated, point4Translated;
	CIwSVec3 point1Transformed, point2Transformed, point3Transformed, point4Transformed; // these are used exclusively for checking touching
	
	int16 material; // material type

private:
	// private methods
	void setVertices( int16 dir );

	bool isTriangleTouched( CIwVec3 v1, CIwVec3 v2, CIwVec3 v3, int16 x, int16 y );
	bool PointInTriangle( CIwVec2 p, CIwVec2 a, CIwVec2 b, CIwVec2 c );
	bool SameSide( CIwVec2 p1_2d, CIwVec2 p2_2d, CIwVec2 a_2d, CIwVec2 b_2d );
	int16 DotProduct( CIwVec3 a, CIwVec3 b );
	CIwVec3 CrossProduct( CIwVec3 a, CIwVec3 b );

	// private variables
	CIwVec3 intersection;
	CIwVec3 normal;
	int16 distance;
	CIwSVec3 gridLocation;
	CIwSVec3 deltaTranslation;
};

