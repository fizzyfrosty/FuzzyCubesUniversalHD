#include "Bomb.h"


Bomb::Bomb(void)
{
}


Bomb::~Bomb(void)
{
}

// initialize with 3 materials for animation blinking speeds
void Bomb::Initialize( int16 s ) 
{
	this->s = s;

	bool defused = false;

	state = STABLE;
	seconds = 0;
	secondsCounter = 0;

	material[0] = NULL;
	material[1] = NULL;
	material[2] = NULL;

	renderMaterial = NULL;
	explodeMaterial = NULL;
	defuseMaterial = NULL;

	// initialize fuzzy vertex streams
	CIwSVec3 vertices_temp[4] =
	{
		CIwSVec3(-s/2, -s/2, 0), 
		CIwSVec3( -s/2, s/2, 0),
		CIwSVec3( s/2,  s/2, 0),
		CIwSVec3( s/2, -s/2, 0),
	};

	// FUZZY MATERIAL UV STREAM
	CIwSVec2 uvStream_temp[4] = 
	{	
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.0) ),
		CIwSVec2(IW_FIXED(0.0), IW_FIXED(0.125) ),
		CIwSVec2(IW_FIXED(0.125), IW_FIXED(0.125) ),
		CIwSVec2(IW_FIXED(0.125), IW_FIXED(0.0) ),
	};

	CIwSVec3 normals_temp[4] = 
	{
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
		CIwSVec3( 0, 0, -IW_GEOM_ONE ),
	};

	// copy fuzzy vertices
	for( int i = 0; i < 4; i++ )
	{
		vertices[i] = vertices_temp[i];
		normals[i] = normals_temp[i];
		uvStream[i] = uvStream_temp[i];
	}
}

// update position and modelmatrix transformation
void Bomb::Update( CIwSVec3 p, CIwMat m )
{
	if( state != EXPLODED )
	{
		position = p;
		modelMatrix = m;

		// update seconds passed for detonation
		if( seconds <= 14 && (state == TICKING || state == HEATING_UP) ) // stop secondsCounter from incrementing if already reached 10 seconds timer for bomb
		{
			secondsCounter++;
		}

		if( secondsCounter % 30 == 1 && (state == TICKING || state == HEATING_UP) ) // 30 fps, so 30 passes is 1 second
		{
			seconds++;
			//printf("seconds is %d \n", seconds );
		}

	
		// set the current blinking material
		if( seconds <= 5 )
		{
			renderMaterial = material[0];
		}
		else if( seconds <= 9 )
		{
			renderMaterial = material[1];
		}
		else if( seconds <= 12 )
		{
			renderMaterial = material[2];
		}
		else if( seconds <= 13 ) // there must be exactly ONE second difference between heating up and the 3rd blink speed to match explosion animation timing
		{
			renderMaterial = material[2];
			state = HEATING_UP;
		}
		else
		{
			if( state == HEATING_UP )
			{
				state = START_EXPLODING;
			}
		}


		if( state == START_EXPLODING )
		{
			if( explodeMaterial->IsAnim() == false )
			{
				explodeMaterial->CreateAnim();
				explodeMaterial->SetAnimCelW( 64 );
				explodeMaterial->SetAnimCelH( 64 );
				explodeMaterial->SetAnimCelPeriod( 1 );
				explodeMaterial->SetAnimCelNum( 30 );
				explodeMaterial->SetColAmbient( 255, 255, 255, 255 );
				explodeMaterial->SetColDiffuse( 255, 255, 255, 255 );	
			}
			state = EXPLODING;
		}
		else if( state == EXPLODING )
		{
			renderMaterial = explodeMaterial;

		}

		if( state == START_DEFUSING )
		{
			if( defuseMaterial->IsAnim() == false )
			{
				defuseMaterial->CreateAnim();
				defuseMaterial->SetAnimCelW( 64 );
				defuseMaterial->SetAnimCelH( 64 );
				defuseMaterial->SetAnimCelPeriod( 1 );
				defuseMaterial->SetAnimCelNum( 30 );
				defuseMaterial->SetColAmbient( 255, 255, 255, 255 );
				defuseMaterial->SetColDiffuse( 255, 255, 255, 255 );	
			}

			state = DEFUSING;
		}
		else if( state == DEFUSING || state == DEFUSED )
		{
			renderMaterial = defuseMaterial;
		}

		
	} // end of if state != exploded

	
}

void Bomb::setState( int16 st )
{
	state = st;
}

void Bomb::Render()
{
	if( state != EXPLODED )
	{
		if( renderMaterial != NULL )
		{
			renderMaterial->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );

			IwGxSetMaterial( renderMaterial );
			IwGxSetColStream( NULL );
			IwGxSetUVStream( uvStream );
			IwGxSetNormStream( normals, 4 );

			CIwSVec3 viewSpaceLocation = (CIwSVec3)IwGxGetWorldViewMatrix().TransformVec( modelMatrix.TransformVec( position ));
			IwGxSetViewSpaceOrg(&viewSpaceLocation);
			IwGxSetVertStreamViewSpace( vertices, 4 );

			IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );

			if( state == EXPLODING )
			{
				if( renderMaterial->IsAnim() )
				{
					if( renderMaterial->GetAnimCelID() >= 28 )
					{
						renderMaterial->PauseAnim();
						state = EXPLODED;
						printf("bomb finished exploding\n");
					}
				}
			}

			if( state == DEFUSING )
			{
				if( renderMaterial->IsAnim() )
				{
					if( renderMaterial->GetAnimCelID() >= 24 )
					{
						renderMaterial->PauseAnim();
						state = DEFUSED;
						printf("bomb defused\n");
					}
				}
			}
		}
		else
		{
			printf("NULL BOMB MATERIAL. COULD NOT RENDER.");
		}
	}
}

void Bomb::Terminate()
{
	for( int i = 0; i < 3; i++ )
	{
		if( material[i] )
		{
			delete material[i];
		}
	}

	if( explodeMaterial )
	{
		delete explodeMaterial;
	}

	if( defuseMaterial )
	{
		delete defuseMaterial;
	}
}