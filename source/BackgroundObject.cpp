#include "BackgroundObject.h"


BackgroundObject::BackgroundObject(void)
{
	texture = NULL;
	material = NULL;

	type = -1;
	s = 0;
	rotationSpeed = 0;
}

BackgroundObject::BackgroundObject(int16 s)
{
	texture = NULL;
	material = NULL;

	type = -1;
	this->s = s/4;
	rotationSpeed = 0;
}

// destructor
BackgroundObject::~BackgroundObject(void)
{

	/*
	if( texture != NULL )
		delete texture;

	if( material != NULL )
		delete material;

		*/
}

void BackgroundObject::setPosition( CIwSVec3 p )
{
	position = p;
	initialPosition = p;
}

void BackgroundObject::setType( int16 t )
{
	type = t;
}

void BackgroundObject::initialize( int16 t, CIwTexture* tx )
{
	// initialize variables based on the type set
	type = t;

	if( type == BLUESTAR_SMALL )
	{
		/*
		texture = new CIwTexture();
		texture->LoadFromFile("blueStar_small.png");
		texture->Upload();
		*/

		texture = tx;

		material = new CIwMaterial();
		material->SetTexture( texture );
		material->SetAlphaMode( CIwMaterial::ALPHA_ADD );
		material->SetColAmbient( 255, 255, 255, 255 ); // BLUE
		material->SetColDiffuse( 255, 255, 255, 255 );

		// these are used to initialze vertex stream
		CIwSVec3 tempvertexstream[4] = 
		{
			CIwSVec3( -1 * s / 2, -1 * s / 2, 0 ),
			CIwSVec3( -1 * s / 2, 1 * s / 2, 0 ),
			CIwSVec3( 1 * s / 2, 1 * s / 2, 0 ),
			CIwSVec3( 1 * s / 2, -1 * s / 2, 0 ),
			/*
			CIwSVec3( -1 * texture->GetWidth() / 2, -1 * texture->GetHeight() / 2, 0 ),
			CIwSVec3( -1 * texture->GetWidth() / 2, 1 * texture->GetHeight() / 2, 0 ),
			CIwSVec3( 1 * texture->GetWidth() / 2, 1 * texture->GetHeight() / 2, 0 ),
			CIwSVec3( 1 * texture->GetWidth() / 2, -1 * texture->GetHeight() / 2, 0 ),
			*/
		};

		CIwSVec2 tempuvstream[4] =
		{
			CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.0) ),
			CIwSVec2(IW_FIXED(0.0), IW_FIXED(1.0) ),
			CIwSVec2(IW_FIXED(1.0), IW_FIXED(1.0) ),
			CIwSVec2(IW_FIXED(1.0), IW_FIXED(0.0) ),
		};

		for( int i = 0; i < 4; i++ )
		{
			vertexstream[i] = tempvertexstream[i];
			uvstream[i] = tempuvstream[i];
		}
	}

}

void BackgroundObject::Initialize( int16 t )
{
	type = t;
	s = 800;

	if( type == PLANET )
	{
		s = 8000; // s is the size of one side length of the object in 3d space

		int16 sDistance = 800;

		position = CIwSVec3( sDistance*6, -sDistance*6, -sDistance*6 );
		// create and load the texture
		texture = new CIwTexture();
		texture->LoadFromFile("fuzzyPlanet.png");
		texture->Upload();
		
		// create and load the material
		material = new CIwMaterial();
		material->SetTexture( texture );
		material->SetColAmbient( 255, 255, 255, 255 );
		material->SetColDiffuse( 255, 255, 255, 255 );
	}
	else if( type == EARTH )
	{

	}

	// these are used to initialze vertex stream
	CIwSVec3 tempvertexstream[4] = 
	{
		CIwSVec3( -1 * s / 2, -1 * s / 2, 0 ),
		CIwSVec3( -1 * s / 2, 1 * s / 2, 0 ),
		CIwSVec3( 1 * s / 2, 1 * s / 2, 0 ),
		CIwSVec3( 1 * s / 2, -1 * s / 2, 0 ),
		/*
		CIwSVec3( -1 * texture->GetWidth() / 2, -1 * texture->GetHeight() / 2, 0 ),
		CIwSVec3( -1 * texture->GetWidth() / 2, 1 * texture->GetHeight() / 2, 0 ),
		CIwSVec3( 1 * texture->GetWidth() / 2, 1 * texture->GetHeight() / 2, 0 ),
		CIwSVec3( 1 * texture->GetWidth() / 2, -1 * texture->GetHeight() / 2, 0 ),
		*/
	};

	CIwSVec2 tempuvstream[4] =
	{
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.0) ),
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(1.0) ),
		CIwSVec2(IW_FIXED(1.0), IW_FIXED(1.0) ),
		CIwSVec2(IW_FIXED(1.0), IW_FIXED(0.0) ),
	};

	CIwSVec3 tempnormals[4] =
	{
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
	};

	for( int i = 0; i < 4; i++ )
	{
		vertexstream[i] = tempvertexstream[i];
		uvstream[i] = tempuvstream[i];
		normals[i] = tempnormals[i];
	}
}

void BackgroundObject::Update( CIwMat m )
{
	modelMatrix = m;
}

void BackgroundObject::Render()
{
	material->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );
	IwGxSetMaterial( material );
	IwGxSetColStream( NULL ); // col stream overrides material. Take note.
	IwGxSetModelMatrix( &modelMatrix ); // uses tt1

	IwGxSetUVStream( uvstream );
	IwGxSetNormStream( normals, 4 );
	CIwSVec3 viewSpaceLocation = (CIwSVec3)IwGxGetWorldViewMatrix().TransformVec( modelMatrix.TransformVec( position )); // this coordinate is position of object
	IwGxSetViewSpaceOrg(&viewSpaceLocation);
	IwGxSetVertStreamViewSpace( vertexstream, 4 );
	IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );

}

void BackgroundObject::Terminate()
{
	delete material;
	if( type == PLANET )
	{
		// do not delete texture otherwise because Stars are using texture pointers and not actually creating texture inside bg object
		delete texture;
	}
}