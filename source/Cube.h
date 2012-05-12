#pragma once
#include "s3e.h"
#include "IwGx.h"
#include "math.h"
#include <vector>
#include "Shadow.h"
#include "Bomb.h"

using std::vector;

class Shadow;

class Cube
{
public:
	Cube(void);
	// initialization for cubes. Use for both spawning static and moving cubes.
	// Cube( pos, dir, sidelength, dist to landing, speed, accel, material, color, numConColReq activeside, isLanded )
	Cube( int16 sl ); // just initialze sidelength

	~Cube(void);
	void linkAsNeighbor( Cube* cube, int16 faceSide ); // must be pass-by-reference to keep neighbors updated in network
	Cube getNeighbor( int16 faceSide );

	void setID( int16 id );
	int16 getID();
	void setInitialSpeed( int16 spd );
	int16 getSpeed(); // not implemented
	void setAcceleration( int16 acc ); // not implemented
	int16 getAcceleration(); // not implemented

	bool isAdjacentTo( Cube cube );
	int16 sideResidesOn( Cube cube ); // returns the side that cube in comparison resides on.
	void updateNetwork( bool u, int16 id, int16 color2, int16 ncc ); // updates the network of connected cubes if they have same color to same ID and color count


	void move(); // moves the cube
	void addNeighbor(); // adds a neighbor to array
	void checkAddNeighbors(); // performed after initialization
	void checkConnectColor( bool checkedColor2, int16 iteration ); // recursively traverses through neighbor web. happens inside addNeighbor
	void release(); // sets neighbor pointers to null. might not be necessary
	// void explode(); // check back later
	bool hasNeighbor();
	

	int16 ID;
	Shadow* shadow;
	bool hasFuzzy;
	CIwTexture* fuzzyTexture;
	CIwMaterial* fuzzyMaterial;

	CIwTexture* fuzzyExplodeTexture;
	CIwMaterial* fuzzyExplodeMaterial;
	bool explosionLoaded;

	bool hasBomb;
	Bomb bomb; // the bomb is initialized in fuzzycubes.cpp

	CIwTexture *bombWarpTexture;
	CIwMaterial *bombWarpMaterial;

	Cube* closestLandingCube;
	vector<int16> sideNeighborBelongsTo; // not used I think
	bool neighborIsLinked[6]; // these determine if that neighbor is filled/linked. Number corresponds to face side // not used I think
	int16 neighborSize; // not used I think
	bool updated;
	bool hasMovedOnce; // this is used to prevent cube from rotating, b/c a cube must move once before it can rotate


	// The following pointers are NOT used.
	// the Sides are for the static cube having different colors for every side, possibly even on one cube
	// Re-using Shadow objects here because they are already implemented and basically has same function
	// for displaying purposes
	Shadow* side1; 
	Shadow* side2;
	Shadow* side3;
	Shadow* side4;
	Shadow* side5;
	Shadow* side6;

	vector<Cube> neighbors;
	Cube* neighbor1; // this has to be a pointer. Otherwise vector makes a deep copy
	Cube* neighbor2;
	Cube* neighbor3;
	Cube* neighbor4;
	Cube* neighbor5;
	Cube* neighbor6;

	CIwSVec3 initialPosition;
	CIwSVec3 position;
	int16 direction; // for moving cubes only
	int16 sideLength;
	int16 distanceToLanding;
	int16 initialSpeed;
	int32 speed;	
	int16 acceleration;
	
	int16 material; // material type
	enum { SOLID_RED, SOLID_GREEN, SOLID_BLUE, SOLID_YELLOW, SOLID_PURPLE, SOLID_ORANGE,
			TRANS_RED, TRANS_GREEN, TRANS_BLUE, TRANS_YELLOW, TRANS_PURPLE, TRANS_ORANGE, 
			WARPING_MATERIAL, EXPLODING_MATERIAL };

	int color;
	enum { RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE };
			//TRANS_RED, TRANS_BLUE, TRANS_GREEN, TRANS_YELLOW, TRANS_ORANGE, TRANS_PURPLE, TRANS_PINK };

	int16 numOfConnectedColor; // determines if cube is going to explode
	int16 numOfConnectedColorRequired; 

	int16 activeSide; // determines which side is facing the center, and thus moving towards the center
	int16 shadowSide; // for shadow rendered on static cubes
	enum {NEG_X, POS_X, NEG_Y, POS_Y, NEG_Z, POS_Z, NONE};

	bool isLanded; // if the cube has landed and stopped moving
	bool checkedColor; // determines whether or not the cube was checked for connected color

	bool touchingSide; // determines if a cube is touching a plane side
	bool warping; // determines if a cube is in process of warping / disappearing
	bool warped; // determines if a cube is still alive. If it's warped, it should be removed from static cubes array. Not used yet

	bool exploding; // used to determine if a cube is displaying the exploding animations/materials
	bool exploded; // this is used set cube aside for removal in data structure after exploding to avoid memory conflict if 2 sides simultaneously explode

	int16 layerLevel; // this tells how many layers the cube is above the surface

};

