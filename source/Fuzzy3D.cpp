#include "Fuzzy3D.h"


Fuzzy3D::Fuzzy3D(void)
{
}


Fuzzy3D::~Fuzzy3D(void)
{
}

void Fuzzy3D::Initialize( int16 t )
{
	type = t;
	s = 10000; // this is the size of the fuzzy

	if( type == BUBBLY )
	{
		material = new CIwMaterial;
		texture = new CIwTexture;
		texture->LoadFromFile("fuzzy_bubbly.png");
		texture->Upload();
		material->SetTexture( texture );


		material->CreateAnim();
		material->SetAnimCelW( 128 );
		material->SetAnimCelH( 128 );
		material->SetAnimCelPeriod( 1 );
		material->SetAnimCelNum( 64 );
	
	}
	
	// initialize fuzzy vertex streams
	CIwSVec3 fuzzyVertices_temp[4] =
	{
		CIwSVec3(-s/2, -s/2, s/4), 
		CIwSVec3( -s/2, s/2, s/4),
		CIwSVec3( s/2,  s/2, s/4),
		CIwSVec3( s/2, -s/2, s/4),
	};

	// FUZZY MATERIAL UV STREAM
	CIwSVec2 fuzzyUVStream_temp[4] = 
	{
		// this is for mapping cells for sprites
		// Each UV corresponds to each Vertex drawn with the draw mode
		// or whatever Index order things are drawn in.
		// Tweak the UVs so that they match each coordinate for U and V
		// Just look at this example and figure it out.
		// Where there is a non-zero number, represents a corner in the axis direction, 
		// or a UV value of 1 if this were NOT a sprite image.
	
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.0) ),
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.125) ),
		CIwSVec2(IW_FIXED(0.125), IW_FIXED(0.125) ),
		CIwSVec2(IW_FIXED(0.125), IW_FIXED(0.0) ),
	};

	CIwSVec3 fuzzyNormals_temp[4] = 
	{
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
	};

	// copy fuzzy vertices
	for( int i = 0; i < 4; i++ )
	{
		fuzzyVertices[i] = fuzzyVertices_temp[i];
		fuzzyNormals[i] = fuzzyNormals_temp[i];
		fuzzyUVStream[i] = fuzzyUVStream_temp[i];
	}
}

void Fuzzy3D::Update()
{
	
}

void Fuzzy3D::Render()
{


	material->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );
	IwGxSetMaterial( material );
	IwGxSetColStream( NULL );
	IwGxSetUVStream( fuzzyUVStream );
	IwGxSetNormStream( fuzzyNormals, 4 );

	/*
	CIwMat moveForward; // move forward matrix just moves the fuzzy towards the camera and up a little bit. It does not move during swipe.
	moveForward.SetIdentity();
	moveForward.SetTrans( CIwSVec3(0, -(s+s/4), -s*3));
	*/
	CIwMat identity;
	identity.SetIdentity();

	CIwSVec3 viewSpaceLocation = (CIwSVec3)IwGxGetWorldViewMatrix().TransformVec( modelMatrix.TransformVec( position ));
	IwGxSetViewSpaceOrg(&viewSpaceLocation); // modelMatrix does not affect viewspace, so it is not used
	IwGxSetVertStreamViewSpace( fuzzyVertices, 4 );
	IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );
}

void Fuzzy3D::Terminate()
{
	delete material;
	delete texture;
}

void Fuzzy3D::setPosition( int16 x, int16 y, int16 z )
{
	position.x = x;
	position.y = y;
	position.z = z;
}