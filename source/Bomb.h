#pragma once
#include "s3e.h"
#include "IwGx.h"

class Bomb
{
public:
	Bomb(void);
	~Bomb(void);

	void Initialize( int16 s ); // initialize with 3 materials for animation blinking speeds
	void Update( CIwSVec3 p, CIwMat m ); // update position and modelmatrix transformation
	void Render();
	void Terminate();
	void setState( int16 st );

	CIwSVec3 position;
	int16 s; // s should be size of cubes
	CIwMat modelMatrix;

	int16 secondsCounter;
	int16 seconds; // seconds increments 1 every time counter increments 30
	int16 state;
	enum{ STABLE, TICKING, HEATING_UP, START_EXPLODING, EXPLODING, EXPLODED, START_DEFUSING, DEFUSING, DEFUSED };

	bool defused; // used for knowing if a bomb was defused in time b/c of delay of tap-drop and falling

	// the three materials and textures represent the different blinking speeds animations
	CIwMaterial* material[3];
	CIwMaterial* renderMaterial;
	CIwMaterial* explodeMaterial;
	CIwMaterial *defuseMaterial;

	CIwSVec3 vertices[4];
	CIwSVec3 normals[4];
	CIwSVec2 uvStream[4];
};

