#pragma once
#include "s3e.h"
#include "IwGx.h"

class Fuzzy3D
{
public:
	void Initialize(int16 t);	
	void Update(); // update with the model matrix, and deltaX to determine location of menuCube for swiping
	void Render();
	void Terminate();
	void setPosition( int16 x, int16 y, int16 z );

	int16 type;
	enum{ BUBBLY }; // SPARKY, FROSTY };

	CIwSVec3 position;
	int16 s; // not used externally right now for size
	CIwMat modelMatrix;

	CIwMaterial* material;
	CIwTexture* texture;

	CIwSVec3 fuzzyVertices[4];
	CIwSVec3 fuzzyNormals[4];
	CIwSVec2 fuzzyUVStream[4];



	Fuzzy3D(void);
	~Fuzzy3D(void);
};

