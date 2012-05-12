#pragma once

#include "IwGx.h"
#include "Sprite.h"
#include "IwRandom.h"

class WindStreak
{
public:
	WindStreak(void);
	~WindStreak(void);

	void Initialize(int16 s);
	void Terminate();
	void Update( CIwMat modelMatrix );
	void Render();

	void Respawn(); // Respawn should be the same method as Initialize()

	int16 s; 
	CIwSVec3 position;
	CIwSVec3 velocity;
	int16 lifeSpan;
	CIwMat modelMatrix;

	CIwMaterial *material;
	CIwTexture *texture;

	CIwSVec3 vertices[4];
	CIwSVec3 verticesTranslated[4];
	CIwSVec3 normals[4];
	CIwSVec2 uvstream[4];
};

