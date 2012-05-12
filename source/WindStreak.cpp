#include "WindStreak.h"


WindStreak::WindStreak(void)
{
}


WindStreak::~WindStreak(void)
{
}

// Respawn should be the same method as Initialize without the texture loading
void WindStreak::Respawn()
{
	int16 RATE = 30; // this is to help determine velocity in terms of units per second
	int16 UNITS = s*30;

	int16 x = IwRandMinMax( -s*5, s*5 + 1 );
	int16 z = IwRandMinMax( -s*5, s*5 + 1 );
	int16 y = IwRandMinMax( -s*7, -s*3 + 1 );

	position = CIwSVec3(x, y, z );
	velocity = CIwSVec3(0, UNITS/RATE, 0 );

	// Generate Lifespan
	lifeSpan = IwRandMinMax( 15, 20+1 ); // lasting between 1 seconds and 2 seconds, so 30 frames, or 60 frames
}

void WindStreak::Initialize(int16 s)
{
	this->s = s;
	
	this->Respawn();

	// --------Load textures-----
	texture = new CIwTexture;
	texture->LoadFromFile("windstreak4.png");
	texture->Upload();

	material = new CIwMaterial;
	material->SetTexture( texture );

	// set vertices, normals, and uvstream
	// the length x height is 200 x 800, where s = 800
	CIwSVec3 fuzzyVertices_temp[4] =
	{
		CIwSVec3(-s/8, -s*3, 0), 
		CIwSVec3( -s/8, s*3, 0),
		CIwSVec3( s/8,  s*3, 0),
		CIwSVec3( s/8, -s*3, 0),
	};

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
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(1.0) ),
		CIwSVec2(IW_FIXED(1.0), IW_FIXED(1.0) ),
		CIwSVec2(IW_FIXED(1.0), IW_FIXED(0.0) ),
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
		vertices[i] = fuzzyVertices_temp[i];
		normals[i] = fuzzyNormals_temp[i];
		uvstream[i] = fuzzyUVStream_temp[i];
	}
}

void WindStreak::Terminate()
{
	// Terminate textures
	delete material;
	delete texture;	

	material = NULL;
	texture = NULL;
}

void WindStreak::Update( CIwMat modelMatrix )
{
	this->modelMatrix = modelMatrix;

	if( lifeSpan >= 0 )
	{
		// move the wind streak
		position = position + velocity;

		for( int i = 0; i < 4; i++ )
		{
			verticesTranslated[i] = vertices[i] + position;
		}
		// decrement 1 life span every frame
		lifeSpan--;
	}
	else
	{
		this->Respawn();
	}
}

void WindStreak::Render()
{
	if( lifeSpan >= 0 )
	{
		// render the wind streak
		material->SetAlphaMode( CIwMaterial::ALPHA_HALF );
		IwGxSetMaterial( material );

		// Create random rotation matrix to randomly rotate the streaks
		// Generate a random rotation of 90 degrees. This should be ok b/c a wind streak renders front and back
		IwRandMinMax(0, 1024 );
		CIwMat rotateRandom;
		rotateRandom.SetRotY();

		// draw front side of streak
		IwGxSetModelMatrix( &(rotateRandom * modelMatrix) );
		IwGxSetColStream( NULL );
		IwGxSetUVStream( uvstream );
		IwGxSetNormStream( normals, 4 );
		IwGxSetVertStream( verticesTranslated, 4);
		IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );

		CIwMat rotate90;
		rotate90.SetRotY( 2048 );

		// draw the back side of streak
		IwGxSetModelMatrix( &(rotate90 * rotateRandom * modelMatrix) );
		IwGxSetColStream( NULL );
		IwGxSetUVStream( uvstream );
		IwGxSetNormStream( normals, 4 );
		IwGxSetVertStream( verticesTranslated, 4);
		IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );

		/* // 2D rendering for testing
		material->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );
		IwGxSetMaterial( material );
		IwGxSetModelMatrix( &modelMatrix );
		IwGxSetColStream( NULL );
		IwGxSetUVStream( uvstream );
		IwGxSetNormStream( normals, 4 );

		CIwMat identity;
		identity.SetIdentity();

		CIwSVec3 viewSpaceLocation = (CIwSVec3)IwGxGetWorldViewMatrix().TransformVec( (identity).TransformVec( position ));
		IwGxSetViewSpaceOrg(&viewSpaceLocation); // modelMatrix does not affect viewspace, so it is not used
		IwGxSetVertStreamViewSpace( vertices, 4 );
		IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );
		*/
	}
}

