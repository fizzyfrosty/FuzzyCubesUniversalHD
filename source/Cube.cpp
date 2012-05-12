#include "Cube.h"

// initialize
// This constructor is NOT used;
Cube::Cube(void)
{	
	neighborSize = 0;

	ID = 0;
	for( int i = 0; i < 6; i++ )
		neighborIsLinked[i] = false;

	initialPosition = CIwSVec3(0, 0, 0);
	position = CIwSVec3(0, 0, 0);
	direction = 0;
	sideLength = 10;
	distanceToLanding = 0;
	speed = 0;
	acceleration = 0;
	
	material = SOLID_RED; // material type
	//enum { SOLID, TRANSPARENT };

	color = RED;
	//enum { RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, PINK }; 
			//TRANS_RED, TRANS_BLUE, TRANS_GREEN, TRANS_YELLOW, TRANS_ORANGE, TRANS_PURPLE, TRANS_PINK };

	numOfConnectedColor = 1; // determines if cube is going to explode
	numOfConnectedColorRequired = 6; 

	activeSide = NONE; // determines which side is facing the center, and thus moving towards the center. This is the static rubix's side that it is falling on, not the side in which itself is moving
	shadowSide = NONE;
	//enum {NEG_X, POS_X, NEG_Y, POS_Y, NEG_Z, POS_Z, NONE};

	isLanded = true; // if the cube has landed and stopped moving
	checkedColor = false; // determines whether or not the cube was checked for connected color
	touchingSide = false;
	warping = false;
	warped = false;
	exploding = false;
	exploded = false;

	layerLevel = 0;

	updated = false;
	hasMovedOnce = false;

	closestLandingCube = NULL;

	shadow = NULL;
	fuzzyTexture = NULL;
	fuzzyMaterial = NULL;

	hasFuzzy = false;
	hasBomb = false;
	explosionLoaded = false;
}

// THIS is the constructor that is used.
Cube::Cube( int16 s )
{
	neighborSize = 0;

	ID = 0;
	for( int i = 0; i < 6; i++ )
		neighborIsLinked[i] = false;

	initialPosition = CIwSVec3(0, 0, 0);
	position = CIwSVec3(0, 0, 0);
	direction = 0;
	sideLength = s;
	distanceToLanding = 0;
	initialSpeed = 0;
	speed = 0;
	initialSpeed = 0;
	acceleration = 0;
	
	material = SOLID_RED; // material type
	//enum { SOLID, TRANSPARENT };

	color = RED;
	//enum { RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, PINK }; 
			//TRANS_RED, TRANS_BLUE, TRANS_GREEN, TRANS_YELLOW, TRANS_ORANGE, TRANS_PURPLE, TRANS_PINK };

	numOfConnectedColor = 1; // determines if cube is going to explode
	numOfConnectedColorRequired = 6; 

	activeSide = NONE; // determines which side is facing the center, and thus moving towards the center
	shadowSide = NONE;
	//enum {NEG_X, POS_X, NEG_Y, POS_Y, NEG_Z, POS_Z, NONE};

	isLanded = true; // if the cube has landed and stopped moving
	checkedColor = false; // determines whether or not the cube was checked for connected color
	touchingSide = false;
	warping = false;
	warped = false;
	exploding = false;
	exploded = false;

	layerLevel = 0;

	updated = false;

	closestLandingCube = NULL;

	shadow = NULL;
	fuzzyTexture = NULL;
	fuzzyMaterial = NULL;

	hasFuzzy = false;
	hasBomb = false;
	explosionLoaded = false;
}

// must use POINTER for a true linked list. a pass-by-reference vector copy makes a deep copy, not a pointer to original
void Cube::linkAsNeighbor( Cube* cube, int16 faceSide )
{
	//neighbor[ faceSide ] = cube;
	if( faceSide >= 1 && faceSide <= 6 )
	{
		if( faceSide == 1 )
			neighbor1 = cube;
		else if( faceSide == 2 )
			neighbor2 = cube;
		else if( faceSide == 3 )
			neighbor3 = cube;
		else if( faceSide == 4 )
			neighbor4 = cube;
		else if( faceSide == 5 )
			neighbor5 = cube;
		else if( faceSide == 6 )
			neighbor6 = cube;

		//neighbors.push_back( cube ); // makes a deep copy. not a pointer to cube. problem.
		sideNeighborBelongsTo.push_back( faceSide );
		neighborIsLinked[faceSide -1 ] = true;
		neighborSize++;
	}
}

// gets neighbor belonging to this face side
Cube Cube::getNeighbor( int16 faceSide )
{
	if( faceSide >= 1 && faceSide <= 6 ) // if the face side is within correct boundaries
	{
		// return corresponding neighbor if not null
		switch( faceSide )
		{
			case 1:
				if( neighbor1 != NULL )
					return *neighbor1;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
			case 2:
				if( neighbor2 != NULL )
					return *neighbor2;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
			case 3:
				if( neighbor3 != NULL )
					return *neighbor3;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
			case 4:
				if( neighbor4 != NULL )
					return *neighbor4;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
			case 5:
				if( neighbor5 != NULL )
					return *neighbor5;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
			case 6:
				if( neighbor6 != NULL )
					return *neighbor6;
				else
					printf("Error: Neighbor on face side %d does not exist. \n", faceSide );
				break;
		}

	}

	// else, return NULL
	return NULL;
}

void Cube::setID( int16 id )
{
	ID = id;
}

int16 Cube::getID()
{
	return ID;
}

// determines if this is adjacent to cube
bool Cube::isAdjacentTo( Cube cube )
{
	
	if( this->position.x == cube.position.x && // if the cube is on face1
		this->position.y == cube.position.y && 
		this->position.z == cube.position.z-sideLength)
		return true;
	if( this->position.x == cube.position.x-sideLength && // if the cube is on face2
		this->position.y == cube.position.y && 
		this->position.z == cube.position.z)
		return true;
	if( this->position.x == cube.position.x && // if the cube is on face3
		this->position.y == cube.position.y && 
		this->position.z == cube.position.z+sideLength)
		return true;
	if( this->position.x == cube.position.x+sideLength && // if the cube is on face4
		this->position.y == cube.position.y && 
		this->position.z == cube.position.z)
		return true;
	if( this->position.x == cube.position.x && // if the cube is on face5
		this->position.y == cube.position.y+sideLength && 
		this->position.z == cube.position.z)
		return true;
	if( this->position.x == cube.position.x && // if the cube is on face6
		this->position.y == cube.position.y-sideLength && 
		this->position.z == cube.position.z)
		return true;

	return false;
}
		

// returns the side that cube in comparison resides on.
// cubes must be adjacent to each other to work
int16 Cube::sideResidesOn( Cube cube )
{	
	if( this->isAdjacentTo( cube ) )
	{
		if( cube.position.z == (position.z - sideLength) ) // if cube is on side 1 of this
			return 1;
		if( cube.position.x == (position.x + sideLength) ) // if cube is on side 2 of this
			return 2;
		if( cube.position.z == (position.z + sideLength) ) // if cube is on side 3 of this
			return 3;
		if( cube.position.x == (position.x - sideLength) ) // if cube is on side 4 of this
			return 4;
		if( cube.position.y == (position.y - sideLength) ) // if cube is on side 5 of this
			return 5;
		if( cube.position.y == (position.y + sideLength) ) // if cube is on side 6 of this
			return 6;
	}
	else
	{
		printf("No comparison of what side the cube is on was made. The two cubes are not adjacent.\n");
	}

	return 0;
}

// updates the network of connected cubes, IF they have same color, to same ID and numOfConnectedColors
void Cube::updateNetwork( bool u, int16 id, int16 color2, int16 ncc ) // ncc = numOfConnectedColors
{
	updated = u;

	if( neighbor1 != NULL )
	{
		if( neighbor1->updated == false && neighbor1->color==color2 )
		{
			neighbor1->updateNetwork( true, id, color2, ncc );
		}
	}
	if( neighbor2 != NULL )
	{
		if( neighbor2->updated == false && neighbor2->color==color2  )
		{
			neighbor2->updateNetwork( true, id, color2, ncc );
		}
	}
	if( neighbor3 != NULL )
	{
		if( neighbor3->updated == false && neighbor3->color==color2  )
		{
			neighbor3->updateNetwork( true, id, color2, ncc );
		}
	}
	if( neighbor4 != NULL )
	{
		if( neighbor4->updated == false && neighbor4->color==color2  )
		{
			neighbor4->updateNetwork( true, id, color2, ncc );
		}
	}
	if( neighbor5 != NULL )
	{
		if( neighbor5->updated == false && neighbor5->color==color2 )
		{
			neighbor5->updateNetwork( true, id, color2, ncc );
		}
	}
	if( neighbor6 != NULL )
	{
		if( neighbor6->updated == false && neighbor6->color==color2 )
		{
			neighbor6->updateNetwork( true, id, color2, ncc );
		}
	}
	// once returning from the recursion, update everything
	ID = id;
	numOfConnectedColor = ncc;
	updated = false;
}

void Cube::setInitialSpeed( int16 spd )
{
	initialSpeed = spd;
	speed = spd;
}

void Cube::move()
{
}

void Cube::checkAddNeighbors()
{
}

void Cube::checkConnectColor( bool checkedColor2, int16 iteration )
{
}

bool Cube::hasNeighbor()
{
	return false;
}


Cube::~Cube(void)
{
	neighbor1 = NULL;
	neighbor2 = NULL;
	neighbor3 = NULL;
	neighbor4 = NULL;
	neighbor5 = NULL;
	neighbor6 = NULL;
	closestLandingCube = NULL;
	//for( int i = 0; i < 6; i++)
//		*neighbor[i] = NULL;
}
