#include "MenuCube.h"

MenuCube::MenuCube(void)
{
}

void MenuCube::Initialize( int16 t, int16 n )
{
	type = t;

	if( type == NEW )
	{
		positionID = 0;
	}
	else if( type == TUTORIAL )
	{
		positionID = 1;
	}
	else if( type == CREDITS )
	{
		positionID = 2;
	}
	else if( type == HIGH_SCORE )
	{
		positionID = 3;
	}
	else if( type == QUESTION_MARK )
	{
		positionID = 4;
	}
	else if( type == RAP_RECORD )
	{
		positionID = 4;
	}
	else if( type == CONTINUE )
	{
		positionID = 5;
	}
	else if( type == CHALLENGE )
	{
		positionID = 6;
	}
	else if( type == QFCHAMBER )
	{

	}

	circleDivisionNumber = n; // this signifies how many menu cubes are in the menu wheel to autosnap.
	startingAngle = 2*PI/circleDivisionNumber;
	angleOffset = PI/2 - startingAngle;

	bobbleRotX.SetIdentity();
	bobbleRotY.SetIdentity();
	bobbleRotZ.SetIdentity();
	modelMatrix.SetIdentity();

	bobbleAngleX = 0.0;
	bobbleAngleY = 0.0;
	bobbleAngleZ = 0.0;

	IwRandSeed( (int32)s3eTimerGetMs() );

	piXMultiple = IwRandMinMax( 1, 8+1 ) / 4.0;
	piYMultiple = IwRandMinMax( 1, 8+1 ) / 4.0;
	piZMultiple = IwRandMinMax( 1, 8+1 ) / 4.0;

	//s = 4500;
	s = 2100;
	//s = IwGxGetScreenWidth() * 4.375;
	n = 2364;// normals //const int16 n = 0x93c;

	// position defaults to zero

	deltaX = 0;
	savedDisplacedAngle = 0;
	beingSwiped = false;
	lockedInPlace = true;
	continueBobble = false;
	savedAngle = -startingAngle - positionID * 2 * PI / circleDivisionNumber;

	// initialize the rotation matrices and values
	rotX.SetIdentity();
	rotY.SetIdentity();
	rotZ.SetIdentity();

	xRotation = 0;
	yRotation = 0;
	zRotation = 0;

	rotationIncrement = 96;

	int16 matInt = 100;

	material = new CIwMaterial;
	texture = new CIwTexture;

	material2 = new CIwMaterial;
	texture2 = new CIwTexture;
	if( type == NEW )
	{
		texture->LoadFromFile( "cubeTextureBlue.png");
		texture2->LoadFromFile( "cubeTextureBlue.png");
	}
	else if( type == TUTORIAL )
	{
		texture->LoadFromFile( "cubeTextureYellow.png");
		texture2->LoadFromFile( "cubeTextureYellow.png");
	}
	else if( type == CREDITS )
	{
		texture->LoadFromFile( "cubeTextureRed.png");
		texture2->LoadFromFile( "cubeTextureRed.png");
	}
	else if( type == HIGH_SCORE )
	{
		texture->LoadFromFile( "cubeTextureGreen.png");
		texture2->LoadFromFile( "cubeTextureGreen.png");
	}
	else if( type == QUESTION_MARK )
	{
		texture->LoadFromFile( "cubeTextureOrange.png");
		texture2->LoadFromFile( "cubeTextureOrange.png");
	}
	else if( type == RAP_RECORD )
	{
		texture->LoadFromFile( "cubeTextureOrange.png");
		texture2->LoadFromFile( "cubeTextureOrange.png");
	}
	else if( type == CONTINUE )
	{
		texture->LoadFromFile( "cubeTexturePurple.png");
		texture2->LoadFromFile( "cubeTexturePurple.png");
	}
	else if( type == CHALLENGE )
	{
		texture->LoadFromFile( "cubeTextureYellow.png");
		texture2->LoadFromFile( "cubeTextureYellow.png");
	}
	
	texture->Upload();
	material->SetTexture( texture );
	material->SetColAmbient( 255, 255, 255, 255 );
	material->SetColDiffuse( 255, 255, 255, 255 );
	material->SetCullMode( CIwMaterial::CULL_BACK ); // this is what displays on the outside
	//material->SetColAmbient( 100, 0, 0, 255 ); // use these without texture
	//material->SetColDiffuse( 100, 0, 0, 255 );
	//material->SetColSpecular( 255, 255, 255 );
	material->SetSpecularPower( 15 );
	material->SetAlphaMode( CIwMaterial::ALPHA_ADD );

	texture2->Upload();
	material2->SetTexture( texture2 );
	material2->SetColAmbient( 255, 255, 255, 255 );
	material2->SetColDiffuse( 255, 255, 255, 255 );
	material2->SetCullMode( CIwMaterial::CULL_FRONT ); // this is what displays on the outside
	//material->SetColAmbient( 100, 0, 0, 255 ); // use these without texture
	//material->SetColDiffuse( 100, 0, 0, 255 );
	//material->SetColSpecular( 255, 255, 255 );
	material2->SetSpecularPower( 15 );
	material2->SetAlphaMode( CIwMaterial::ALPHA_HALF );

	// initialize buttons
	button.Initialize( type, 1 );

	// initialize the vertex streams
	CIwSVec3 cubeVertices[24] =
	{
		// faceSide 1
		CIwSVec3(-s/2, -s/2, -s/2), 
		CIwSVec3( -s/2, s/2, -s/2),
		CIwSVec3( s/2,  s/2, -s/2),
		CIwSVec3( s/2, -s/2, -s/2),
	

		// faceSide 2
		CIwSVec3( s/2, -s/2,  -s/2),
		CIwSVec3( s/2, s/2,  -s/2),
		CIwSVec3( s/2,  s/2, s/2),
		CIwSVec3( s/2,  -s/2, s/2),

		// faceSide 3
		CIwSVec3( s/2, -s/2,  s/2),
		CIwSVec3( s/2, s/2,  s/2),
		CIwSVec3( -s/2,  s/2, s/2),
		CIwSVec3( -s/2,  -s/2, s/2),

		// faceSide 4
		CIwSVec3( -s/2, -s/2,  s/2),
		CIwSVec3( -s/2, s/2,  s/2),
		CIwSVec3( -s/2,  s/2, -s/2),
		CIwSVec3( -s/2,  -s/2, -s/2),

		// faceSide 5
		CIwSVec3( -s/2, -s/2,  s/2),
		CIwSVec3( -s/2, -s/2,  -s/2),
		CIwSVec3( s/2,  -s/2, -s/2),
		CIwSVec3( s/2, -s/2, s/2),

		// faceSide 6
		CIwSVec3( -s/2, s/2,  -s/2),
		CIwSVec3( -s/2, s/2,  s/2),
		CIwSVec3( s/2,  s/2, s/2),
		CIwSVec3( s/2,  s/2, -s/2),
	};

	CIwSVec3 cubeNormals[24] = 
	{
		// faceSide 1
		CIwSVec3( -n, -n, -n),
		CIwSVec3( -n, n, -n),
		CIwSVec3( n,  n, -n),
		CIwSVec3( n, -n, -n),
	
		// faceSide 2
		CIwSVec3( n, -n,  -n),
		CIwSVec3( n, n,  -n),
		CIwSVec3( n,  n, n),
		CIwSVec3( n,  -n, n),

		// faceSide 3
		CIwSVec3( n, -n,  n),
		CIwSVec3( n, n,  n),
		CIwSVec3( -n,  n, n),
		CIwSVec3( -n,  -n, n),

		// faceSide 4 
		CIwSVec3( -n, -n,  n),
		CIwSVec3( -n, n,  n),
		CIwSVec3( -n,  n, -n),
		CIwSVec3( -n,  -n, -n),

		// faceSide 5
		CIwSVec3( -n, -n,  n),
		CIwSVec3( -n, -n,  -n),
		CIwSVec3( n,  -n, -n),
		CIwSVec3( n, -n, n),

		// faceSide 6
		CIwSVec3(-n, n,-n),
		CIwSVec3(-n, n, n),
		CIwSVec3( n, n, n),
		CIwSVec3( n, n,-n),
	};

	CIwSVec2 uvstream_base[24] = 
	{
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),

		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),

		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),

		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),

		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),

		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
		CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
		CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),
	};

	// copy the vertices
	for( int i = 0; i < 24; i++ )
	{
		vertices[i] = cubeVertices[i];
		normals[i] = cubeNormals[i];
		uvstream[i] = uvstream_base[i];
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

MenuCube::~MenuCube(void)
{
}

void MenuCube::Update() // deltaX acts as the angle theta
{	
	int16 r = s*3; // r is the radius of circle that makes position points for menu cubes
	double theta = 0; // theta deals only with NEGATIVE angles. they must be less than -PI/2
	// calculate the (x, y, z) position coordinates with trig.
	double X = 0; 
	double Z = 0;
	double Y = 0; // this will not change. currently NOT used.

	int16 tier1SpeedDenominator = 90; // smaller is faster
	int16 tier2SpeedDenominator = 180;


	// CALCULATE POSITION BASED ON DELTAX
	// if CONTROLLED EXTERNALLY, calculate position based on the deltaX value as angle
	if( beingSwiped == true )
	{
		// divide theta b/c deltaX is initially not angle, so drag value is too high. subtract PI/2 b/c zero represents zero radians, whereas camera is at -PI/2 radians on X-Z plane
		theta = (savedDisplacedAngle + -deltaX) - startingAngle - (positionID * 2 * PI / circleDivisionNumber);
	}
	else // if the cube is NOT being controlled externally
	{
		if( lockedInPlace == false )
		{
			// autosnap position to nearest position
			for( int i = 0; i < circleDivisionNumber; i++ )
			{
				theta = savedDisplacedAngle - startingAngle - (positionID * 2 * PI / circleDivisionNumber); // the pID*2PI/CDN is the offset in the menu wheel depending on which item it is
					
				// WRAP theta
				while( theta > -PI/circleDivisionNumber ) // theta's upper limit, recalculate theta with new displacement
				{
					theta += -2*PI;
				}
				while( theta < (-2*PI - PI/circleDivisionNumber) ) // theta's lower limit, recalculate theta with new displacement
				{
					theta += 2*PI;
				}

				// if theta is in between the +/- range of each point on menu wheel
				if( (theta > (-startingAngle - i*2*PI/circleDivisionNumber - PI/circleDivisionNumber)) && (theta < (-startingAngle - i*2*PI/circleDivisionNumber + PI/circleDivisionNumber)) )
				{
					if( theta <= -startingAngle - i*2*PI/circleDivisionNumber ) // if theta is LESS than the spoke
					{
						/*
						// have TWO TIERS of displacement rates
						if( theta > -startingAngle - i*2*PI/circleDivisionNumber - i*2*PI/circleDivisionNumber/4) // the 2nd tier speed, slower speed
						{
							savedDisplacedAngle += PI/tier2SpeedDenominator;
						}
						else // the first tier speed, faster speed
						{
							savedDisplacedAngle += PI/tier1SpeedDenominator; // denominator controls autosnap sensitivity/speed
						}
						*/

						savedDisplacedAngle += PI/90;
						
						// CLAMP the angle
						theta = savedDisplacedAngle - startingAngle - (positionID * 2 * PI / circleDivisionNumber); // the pID*2PI/CDN is the offset in the menu wheel depending on which item it is
					
						// WRAP theta
						while( theta > -PI/circleDivisionNumber ) // theta's upper limit, recalculate theta with new displacement
						{
							theta += -2*PI;
							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}
						while( theta < (-2*PI - PI/circleDivisionNumber) ) // theta's lower limit, recalculate theta with new displacement
						{
							theta += 2*PI;
							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}


						if( theta >= -startingAngle - i*2*PI/circleDivisionNumber )
						{
							theta = -startingAngle - i*2*PI/circleDivisionNumber;
							savedAngle = theta;
							lockedInPlace = true;

							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}
					}
					else if( theta > -startingAngle - i*2*PI/circleDivisionNumber )// if theta is greater than the spoke
					{
						/*
						if( theta < -startingAngle - i*2*PI/circleDivisionNumber + i*2*PI/circleDivisionNumber/4) // the 2nd tier speed, slower speed
						{
							savedDisplacedAngle -= PI/tier2SpeedDenominator;
						}
						else// the first tier speed, faster speed
						{
							savedDisplacedAngle -= PI/tier1SpeedDenominator; // denominator controls autosnap sensitivity/speed
						}
						*/
						
						savedDisplacedAngle -= PI/90; // denominator controls autosnap sensitivity/speed

						// CLAMP the angle
						theta = savedDisplacedAngle - startingAngle - (positionID * 2 * PI / circleDivisionNumber); // the pID*2PI/CDN is the offset in the menu wheel depending on which item it is
	
						// WRAP theta
						while( theta > -PI/circleDivisionNumber ) // theta's upper limit, recalculate theta with new displacement
						{
							theta += -2*PI;
							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}
						while( theta < (-2*PI - PI/circleDivisionNumber) ) // theta's lower limit, recalculate theta with new displacement
						{
							theta += 2*PI;
							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}

						if( theta <= -startingAngle - i*2*PI/circleDivisionNumber )
						{
							theta = -startingAngle - i*2*PI/circleDivisionNumber;
							savedAngle = theta;
							lockedInPlace = true;

							// calculate new savedDisplacedAngle
							savedDisplacedAngle = theta + startingAngle + (positionID * 2 * PI / circleDivisionNumber);
						}
					}

					// break out of loop once found the boundaries
					break;
				}
			} // end of for loop checking every spoke on wheel for boundaries
		} // end of if lockedInPlace == false
		else if( lockedInPlace == true )
		{
			// do nothing
		}
	}

	// CALCULATE THE X-Z COORDINATES
	if( lockedInPlace == false )
	{
		X = r * cos( theta - angleOffset ); // divide theta b/c deltaX is initially not angle, so drag value is too high. subtract PI/2 b/c zero represents zero radians, whereas camera is at -PI/2 radians on X-Z plane
		Z = r * sin( theta - angleOffset );
	}
	else
	{
		X = r * cos( savedAngle - angleOffset ); // divide theta b/c deltaX is initially not angle, so drag value is too high. subtract PI/2 b/c zero represents zero radians, whereas camera is at -PI/2 radians on X-Z plane
		Z = r * sin( savedAngle - angleOffset );
	}

	// for testing to be deleted
	theta = (savedDisplacedAngle + -deltaX) - startingAngle - (positionID * 2 * PI / circleDivisionNumber);
	X = r * cos( theta - angleOffset ); // divide theta b/c deltaX is initially not angle, so drag value is too high. subtract PI/2 b/c zero represents zero radians, whereas camera is at -PI/2 radians on X-Z plane
	Z = r * sin( theta - angleOffset );

	// ASSIGN the position coordinates
	position.x = (int16)X;
	position.z = (int16)Z;
	position.y = s/2;	
	
	// transform vertices
	for( int i = 0; i < 24; i++ )
	{
		verticesTranslated[i] = vertices[i] + position;
	}

	for( int i = 0; i < 4; i++ )
	{
		fuzzyVerticesTranslated[i] = fuzzyVertices[i] + position;
	}

	/*
	// perform rotations to the corresponding side of cube if a button is pressed and released
	if( highScoreButton.activated == true ) // rotate to HIGH SCORE
	{
		// for high scores, rotate to face side 2
		yRotation -= rotationIncrement;

		// clamps the max rotation
		if( yRotation <= -1024 )
		{
			yRotation = -1024;
			highScoreButton.activated = false;
		}

		rotY.SetRotY( yRotation );
	}

	if( highScoreBackButton.activated == true ) // back to menu from high score
	{
		yRotation += rotationIncrement;

		// clamps the max rotation
		if( yRotation >= 0 )
		{
			yRotation = 0;
			highScoreBackButton.activated = false;
		}

		rotY.SetRotY( yRotation );
	} */

	/* // play tutorial instead
	if( helpButton.activated == true ) // rotate to HELP
	{
		yRotation += rotationIncrement;

		// clamps the max rotation
		if( yRotation >= 1024 )
		{
			yRotation = 1024;
			helpButton.activated = false;
		}

		rotY.SetRotY( yRotation );
	}
	*/

	/* obsolete
	if( helpBackButton.activated == true ) // rotate back to menu from help
	{
		yRotation -= rotationIncrement;

		// clamps the max rotation
		if( yRotation <= 0 )
		{
			yRotation = 0;
			helpBackButton.activated = false;
		}

		rotY.SetRotY( yRotation );
	}

	if( creditsButton.activated == true ) // rotate to CREDITS
	{
		xRotation += rotationIncrement;

		// clamps the max rotation
		if( xRotation >= 1024 )
		{
			xRotation = 1024;
			creditsButton.activated = false;
		}

		rotX.SetRotX( xRotation );
	}

	if( creditsBackButton.activated == true ) // rotate back to menu from credits
	{
		xRotation -= rotationIncrement;

		// clamps the max rotation
		if( xRotation <= 0 )
		{
			yRotation = 0;
			creditsBackButton.activated = false;
		}

		rotX.SetRotX( xRotation );
	} */

	translateForward.SetIdentity();
	translateBackward.SetIdentity();

	translateForward.SetTrans( position );
	translateBackward.SetTrans( -position );

	CIwMat xzCorrection;
	xzCorrection.SetRotX( 55 ); // the xz correction matrix is a rotation of the xz plane of cubes on the xaxis to have cubes seemingly face center after downward translation


	bobbleAngleX += PI / 32 * 1.25; // these are super small numbers. they should not overflow...
	bobbleAngleY += PI / 32 * 1;
	bobbleAngleZ += PI / 32 * 1.5;

	int16 bobbleX, bobbleY, bobbleZ;

	if( button.pressed == false )
	{
		bobbleX = 64 * cos( bobbleAngleX + PI*piXMultiple );
		bobbleY = 64 * cos( bobbleAngleZ + PI*piYMultiple );
		bobbleZ = 64 * cos( bobbleAngleZ + PI*piZMultiple );
	}
	else
	{
		bobbleX = 64 * cos( bobbleAngleX*3 + PI*piXMultiple );
		bobbleY = 64 * cos( bobbleAngleZ*3 + PI*piYMultiple );
		bobbleZ = 64 * cos( bobbleAngleZ*3 + PI*piZMultiple );
	}

	// this makes the button continue to bobble after it is pressed and released
	if( continueBobble == true )
	{
		bobbleX = 64 * cos( bobbleAngleX*3 + PI*piXMultiple );
		bobbleY = 64 * cos( bobbleAngleZ*3 + PI*piYMultiple );
		bobbleZ = 64 * cos( bobbleAngleZ*3 + PI*piZMultiple );
	}

	bobbleRotX.SetRotX( bobbleX );
	bobbleRotY.SetRotY( bobbleY );
	bobbleRotZ.SetRotZ( bobbleZ );
	
	//modelMatrix = modelMatrix * rotX * rotY * rotZ; // rotX,Y,Z was used for turning the cube
	modelMatrix = bobbleRotX * bobbleRotY * bobbleRotZ;
	modelMatrix = translateBackward * modelMatrix * translateForward * xzCorrection;
	button.Update( CIwSVec2( 0, 0 ), modelMatrix, position );
	
	//button.Update( CIwSVec2( -s/10, -(s/5/5/2 + s/5/2 + s/5 + s/5/5) ), modelMatrix, position ); // updates the position entry for the buttons
	

	/* obsolete
							// s/5 is height of each. /5 is height of each space separating b/c of 4 buttons. /2 is shifting up/down half of space
							// s/5/2 is half of space of height.
							// first entry is space, second is button. we are shifting each multiples of both-by-half up or down
	newButton.Update		( CIwSVec2( -s/10, -(s/5/5/2 + s/5/2 + s/5 + s/5/5) ), modelMatrix ); // updates the position entry for the buttons
	highScoreButton.Update	( CIwSVec2( -s/10, -(s/5/5/2 + s/5/2) ), modelMatrix );
	helpButton.Update		( CIwSVec2( -s/10, (s/5/5/2 + s/5/2) ), modelMatrix );
	creditsButton.Update	( CIwSVec2( -s/10, (s/5/5/2 + s/5/2 + s/5 + s/5/5) ), modelMatrix );

	highScoreBackButton.Update	( CIwSVec2( -s/10, -(s/5/5/2 + s/5/2) ), modelMatrix );
	helpBackButton.Update		( CIwSVec2( -s/10, (s/5/5/2 + s/5/2) ), modelMatrix );
	creditsBackButton.Update	( CIwSVec2( -s/10, (s/5/5/2 + s/5/2 + s/5 + s/5/5) ), modelMatrix );
	*/
}

void MenuCube::Render()
{
	// render button
	button.Render();

	IwGxSetUVStream( uvstream ); // the outside surface
	IwGxSetMaterial( material );
	IwGxSetColStream( NULL );
	IwGxSetModelMatrix( &modelMatrix );
	IwGxSetNormStream( normals, 24 );
	IwGxSetVertStream( verticesTranslated, 24 ); // use Model space b/c of light reflections during rotation
	IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 24 );

	IwGxSetUVStream( uvstream ); // the outside surface
	IwGxSetMaterial( material2 );
	IwGxSetColStream( NULL );
	IwGxSetModelMatrix( &modelMatrix );
	IwGxSetNormStream( normals, 24 );
	IwGxSetVertStream( verticesTranslated, 24 ); // use Model space b/c of light reflections during rotation
	IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 24 );


}

void MenuCube::Terminate()
{
	button.Terminate();

	delete material;
	delete texture;

	delete material2;
	delete texture2;
}

void MenuCube::grabAndSetSwipe( int16 dx )
{

	int16 swipePixelsConverted = dx * 480.0/IwGxGetScreenWidth();
	//deltaX = (double)dx * PI / 540; // this controls sensitivity
	deltaX = (double)swipePixelsConverted * PI / 540; // this controls sensitivity
	beingSwiped = true;
	lockedInPlace = false;
}

void MenuCube::releaseSwipe()
{
	beingSwiped = false;
	savedDisplacedAngle = savedDisplacedAngle + -deltaX;
	deltaX = 0;
}

bool MenuCube::isTouched( int16 x, int16 y )
{
	// return button.isTouched( x, y ); // only test touching if the angle is close to -PI/2, the front cube
	if( savedAngle-angleOffset < -PI/2+PI/180 && savedAngle-angleOffset > -PI/2-PI/180 )
	{
		return button.isTouched( x, y ); // only test touching if the angle is close to -PI/2, the front cube
	}
	else
	{
		return false;
	}

}

void MenuCube::setBobbleRotX( int16 x )
{
	bobbleRotX.SetRotX( x );
}

void MenuCube::setBobbleRotY( int16 y )
{
	bobbleRotY.SetRotY( y );
}

void MenuCube::setBobbleRotZ( int16 z )
{
	bobbleRotZ.SetRotZ( z );
}