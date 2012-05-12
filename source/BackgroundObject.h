#pragma once
#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include "IwRandom.h"

class BackgroundObject
{
public:
	BackgroundObject(void);
	BackgroundObject(int16 s);
	~BackgroundObject(void);

	// methods
	void setPosition( CIwSVec3 p );
	void setType( int16 t ); // obsolete
	void initialize( int16 t, CIwTexture* tx); // initialize hardcoded vertex stream, uv stream, texture, material based on type
	void Terminate();
	void Initialize( int16 t );
	void Update( CIwMat m );
	void Render(); // the backgroundobject has the option to render, which may or may not be used depending if batch rendering is desired


	// variables
	CIwSVec3 position;
	CIwSVec3 initialPosition;
	CIwSVec2 uvstream[4];
	CIwSVec3 vertexstream[4];
	CIwSVec3 normals[4]; // these and below are used for the new BG object that self-renders. The ones above were used for stars
	CIwSVec3 verticesTranslated[4];
	CIwSVec3 vertices[4];
	int16 s;
	int16 type; // this utilizes the enum of types
	int16 rotationSpeed;
	CIwMat modelMatrix;

	// types of stars/objects
	enum { BLUESTAR_SMALL, PLANET, EARTH, COLORED_STAR };
	CIwTexture* texture;
	CIwMaterial* material;

private:

};

