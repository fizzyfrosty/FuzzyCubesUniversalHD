#include "TouchButton3D.h"


TouchButton3D::TouchButton3D(void)
{
}

void TouchButton3D::Initialize( int16 t, int16 dir )
{
	s = 2100; // s is how big the menuCube is. this correctly places the button on the surface of the cube. 
	n = 2364;// normals //const int16 n = 0x93c;

	// Make sure s is big enough so that s/x is greater than 600-700ish
	size.x = s * 3 / 4;
	size.y = s * 3 / 4;

	pressed = false;
	initialPressed = false;
	activated = false;

	// the size's width and height will be a ratio of 's', the sidelength of the MenuCube

	material = new CIwMaterial;
	texture = new CIwTexture;

	materialPressed = new CIwMaterial;
	texturePressed = new CIwTexture;

	// initialize texture based on the type of the button
	// Load textures
	type = t;
	if( type == NEW )
	{
		texture->LoadFromFile("buttonPlay.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonPlay.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == TUTORIAL )
	{
		texture->LoadFromFile("buttonTutorial.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonTutorial.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == HIGH_SCORE )
	{
		texture->LoadFromFile("buttonHighScore.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonHighScore.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == HELP )
	{
		texture->LoadFromFile("menuButton_Help.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("menuButton_Touched.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == CREDITS )
	{
		texture->LoadFromFile("buttonCredits.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonCredits.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == QUESTION_MARK )
	{
		texture->LoadFromFile("buttonQuestionMark.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonQuestionMark.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == RAP_RECORD )
	{
		texture->LoadFromFile("buttonRapRecord.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonRapRecord.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == CONTINUE )
	{
		texture->LoadFromFile("buttonContinue.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("buttonContinue.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == CHALLENGE )
	{
		texture->LoadFromFile("test.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("menuButton_Touched.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == QFCHAMBER )
	{
		texture->LoadFromFile("test.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("test.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == HIGH_SCORE_BACK )
	{
		texture->LoadFromFile("menuButton_HighScore.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("menuButton_Touched.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == HELP_BACK )
	{
		texture->LoadFromFile("menuButton_Help.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("menuButton_Touched.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}
	else if( type == CREDITS_BACK )
	{
		texture->LoadFromFile("menuButton_Credits.png");
		texture->Upload();
		material->SetTexture( texture );

		texturePressed->LoadFromFile("menuButton_Touched.png");
		texturePressed->Upload();
		materialPressed->SetTexture( texturePressed );
	}

	direction = dir;

	// set the vertex, normal, and uv streams
	if( direction == 1 )
	{
		// initialize BASE VERTICES
		CIwSVec3 initialized_vertices[4] =
		{
			// faceSide 1
			CIwSVec3(-size.x/2, -size.y/2, -s/2 - 50), 
			CIwSVec3( -size.x/2, size.y/2, -s/2 - 50),
			CIwSVec3( size.x/2,  size.y/2, -s/2 - 50),
			CIwSVec3( size.x/2, -size.y/2, -s/2 - 50),
		};

		// initialize NORMALS
		CIwSVec3 initialized_normals[4] = 
		{
			// faceSide 1
			CIwSVec3( -n, -n, -n),
			CIwSVec3( -n, n, -n),
			CIwSVec3( n,  n, -n),
			CIwSVec3( n, -n, -n),
		};

		// initialize UV's 
		CIwSVec2 initialized_uvstream[4] = 
		{
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),
		};

		// initialze the streams
		for( int i = 0; i < 4; i++ )
		{
			base_vertices[i] = initialized_vertices[i];
			normals[i] = initialized_normals[i];
			uvstream[i] = initialized_uvstream[i];
		}

	}
	else if( direction == 2 )
	{
		// initialize BASE VERTICES
		CIwSVec3 initialized_vertices[4] =
		{
			// faceSide 2
			CIwSVec3( s/2 + 50, -size.y/2,  -size.x/2),
			CIwSVec3( s/2 + 50, size.y/2,  -size.x/2),
			CIwSVec3( s/2 + 50,  size.y/2, size.x/2),
			CIwSVec3( s/2 + 50,  -size.y/2, size.x/2),
		};

		// initialize NORMALS
		CIwSVec3 initialized_normals[4] = 
		{
			// faceSide 2
			CIwSVec3( n, -n,  -n),
			CIwSVec3( n, n,  -n),
			CIwSVec3( n,  n, n),
			CIwSVec3( n,  -n, n),
		};

		// initialize UV's 
		CIwSVec2 initialized_uvstream[4] = 
		{
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),
		};

		// initialze the streams
		for( int i = 0; i < 4; i++ )
		{
			base_vertices[i] = initialized_vertices[i];
			normals[i] = initialized_normals[i];
			uvstream[i] = initialized_uvstream[i];
		}
	}
	else if( direction == 3 )
	{
	}
	else if( direction == 4 )
	{
		// initialize BASE VERTICES
		CIwSVec3 initialized_vertices[4] =
		{
			// faceSide 4
			CIwSVec3( -s/2 - 50, -size.y/2,  size.x/2),
			CIwSVec3( -s/2 - 50, size.y/2,  size.x/2),
			CIwSVec3( -s/2 - 50,  size.y/2, -size.x/2),
			CIwSVec3( -s/2 - 50,  -size.y/2, -size.x/2),
		};

		// initialize NORMALS
		CIwSVec3 initialized_normals[4] = 
		{
			// faceSide 4 
			CIwSVec3( -n, -n,  n),
			CIwSVec3( -n, n,  n),
			CIwSVec3( -n,  n, -n),
			CIwSVec3( -n,  -n, -n),
		};

		// initialize UV's 
		CIwSVec2 initialized_uvstream[4] = 
		{
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),
		};

		// initialze the streams
		for( int i = 0; i < 4; i++ )
		{
			base_vertices[i] = initialized_vertices[i];
			normals[i] = initialized_normals[i];
			uvstream[i] = initialized_uvstream[i];
		}
	}
	else if( direction == 5 )
	{
	}
	else if( direction == 6 )
	{
		// initialize BASE VERTICES
		CIwSVec3 initialized_vertices[4] =
		{
			// faceSide 6
			CIwSVec3( -size.x/2, s/2 + 50,  -size.y/2),
			CIwSVec3( -size.x/2, s/2 + 50,  size.y/2),
			CIwSVec3( size.x/2,  s/2 + 50, size.y/2),
			CIwSVec3( size.x/2,  s/2 + 50, -size.y/2),
		};

		// initialize NORMALS
		CIwSVec3 initialized_normals[4] = 
		{
			// faceSide 6
			CIwSVec3(-n, n,-n),
			CIwSVec3(-n, n, n),
			CIwSVec3( n, n, n),
			CIwSVec3( n, n,-n),
		};

		// initialize UV's 
		CIwSVec2 initialized_uvstream[4] = 
		{
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 0.0 ) ),
			CIwSVec2( IW_FIXED( 0.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 1.0 ) ),
			CIwSVec2( IW_FIXED( 1.0 ), IW_FIXED( 0.0 ) ),
		};

		// initialze the streams
		for( int i = 0; i < 4; i++ )
		{
			base_vertices[i] = initialized_vertices[i];
			normals[i] = initialized_normals[i];
			uvstream[i] = initialized_uvstream[i];
		}
	}
}

TouchButton3D::~TouchButton3D(void)
{
}

void TouchButton3D::Update( CIwSVec2 location, CIwMat matrix, CIwSVec3 pos )
{
	// create the vertex streams
	position = location;

	// set model matrix
	modelMatrix = matrix;

	for( int i = 0; i < 4; i++ )
	{
		if( direction == 1 ) // if the menu button is on face side 1 of menu cube
		{
			// the position is a 2d vector. z-coordinate is untouched b/c has same depth as side of the menu cube
			// Or maybe it's a little bit outward depending on how it renders.
			vertices[i].x = base_vertices[i].x + position.x; 
			vertices[i].y = base_vertices[i].y + position.y;
			vertices[i].z = base_vertices[i].z;
		}
		else if( direction == 2 )
		{
			vertices[i].x = base_vertices[i].x; 
			vertices[i].y = base_vertices[i].y + position.y;
			vertices[i].z = base_vertices[i].z + position.x;
		}
		else if( direction == 3 )
		{
		}
		else if( direction == 4 )
		{
			vertices[i].x = base_vertices[i].x; 
			vertices[i].y = base_vertices[i].y + position.y;
			vertices[i].z = base_vertices[i].z - position.x;
		}
		else if( direction == 5 )
		{
		}
		else if( direction == 6 )
		{
			vertices[i].x = base_vertices[i].x + position.x; 
			vertices[i].y = base_vertices[i].y;
			vertices[i].z = base_vertices[i].z + position.y;
		}
	}

	// Transform vertices
	for( int i = 0; i < 4; i++ )
	{
		verticesTranslated[i] = vertices[i] + pos; // pos is the 3D coordinate of its location in space, where position is its 3D coordinate relative to Menu Cube
	}
}

void TouchButton3D::Render()
{
	// draw the button
	if( pressed == false ) // the 'material' material is the unpressed material for button
	{
		material->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );
		IwGxSetMaterial( material );
		IwGxSetColStream( NULL ); // col stream overrides material. Take note.
		IwGxSetModelMatrix( &modelMatrix ); // uses tt1
		IwGxSetUVStream( uvstream );
		IwGxSetNormStream( normals, 4 );
		IwGxSetVertStream( verticesTranslated, 4 );
		IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );
	}
	else
	{
		materialPressed->SetAlphaMode( CIwMaterial::ALPHA_DEFAULT );
		IwGxSetMaterial( materialPressed );
		IwGxSetColStream( NULL ); // col stream overrides material. Take note.
		IwGxSetModelMatrix( &modelMatrix ); // uses tt1
		IwGxSetUVStream( uvstream );
		IwGxSetNormStream( normals, 4 );
		IwGxSetVertStream( verticesTranslated, 4 );
		IwGxDrawPrims( IW_GX_QUAD_LIST, NULL, 4 );
	}
}


void TouchButton3D::setModelMatrix( CIwMat matrix )
{
	modelMatrix = matrix;
}

void TouchButton3D::setLocation( int16 x, int16 y )
{
	position.x = x;
	position.y = y;
}

void TouchButton3D::setSize( int16 width, int16 height )
{
	size.x = width;
	size.y = height;
}

// these are the isTouched() Functions borrowed and re-implemented from Shadow.h
bool TouchButton3D::isTouched( int16 x, int16 y )
{
	CIwSVec3 verticesTransformed[4]; // these are the transformed absolute-value-vertices used for isTouched() function

	// updates points based on shadow's current position
	// transforming the vertices by the modelmatrix gets absolute coordinates of vertices after camera rotation
	for( int i = 0; i < 4; i++ )
	{
		verticesTransformed[i] = modelMatrix.TransformVec( verticesTranslated[i] );
	}

	// returns true if both hitboxes of triangles that make up the square is touched
	// Uses isTriangleTouched to determine if the point-touched lies inside the 3-abs-coordinate points
	if( isTriangleTouched( (CIwVec3)verticesTransformed[0], (CIwVec3)verticesTransformed[1], (CIwVec3)verticesTransformed[2], x, y ) == true || 
		isTriangleTouched((CIwVec3)verticesTransformed[0], (CIwVec3)verticesTransformed[2], (CIwVec3)verticesTransformed[3], x, y ) == true )
	{
		// not only is it in the triangle, but the triangle's normal must also be facing the camera
		CIwVec3 normal = CrossProduct( (CIwVec3)(verticesTransformed[3] - verticesTransformed[0]), (CIwVec3)(verticesTransformed[1] - verticesTransformed[0]) );
		if( normal.z > 450000 ) // if the z-component of the normal is positive, that means the normal is facing the camera.
		{
			return true;
		}
		else // if the click was within the hitbox but the shadow was facing away from the camera, return false
		{
			return false;
		}
	}
	else // return false if the click was not in the hitbox
	{
		return false;
	}
}

bool TouchButton3D::isTriangleTouched( CIwVec3 v1, CIwVec3 v2, CIwVec3 v3, int16 x, int16 y )
{
	// these are the 2d points
	CIwVec2 vv1, vv2, vv3;

	// convert from 3d space to 2d space into the 2d points vv
	// convert only if not behind camera
	if( v1.z > IwGxGetViewMatrix().t.z &&  
		v2.z > IwGxGetViewMatrix().t.z &&
		v3.z > IwGxGetViewMatrix().t.z )
	{
		IwGxWorldToScreenXY( vv1.x, vv1.y, v1 );
		IwGxWorldToScreenXY( vv2.x, vv2.y, v2 );
		IwGxWorldToScreenXY( vv3.x, vv3.y, v3 );
	}
	else
	{
		return false;
	}

	// this is where the screen is touched
	CIwVec2 touchPoint( x, y );

	/*
	printf("The coordinates of v1 are: (%d, %d) \n", vv1.x, vv1.y );
	printf("The coordinates of v2 are: (%d, %d) \n", vv2.x, vv2.y );
	printf("The coordinates of v3 are: (%d, %d) \n", vv3.x, vv3.y );
	printf("The coordinates of Touch are: (%d, %d) \n", x, y );
	*/

	if( PointInTriangle( touchPoint, vv1, vv2, vv3 ) )
		return true;
	else
		return false;
}

// POINT IN TRIANGLE
bool TouchButton3D::PointInTriangle( CIwVec2 p, CIwVec2 a, CIwVec2 b, CIwVec2 c )
{
	/*
	printf("Same Side 1 is: %d \n", SameSide(p, a, b, c));
	printf("Same Side 2 is: %d \n", SameSide(p, b, a, c));
	printf("Same Side 3 is: %d \n", SameSide(p, c, a, b));
	*/
	bool s1 = SameSide(p, a, b, c);
	bool s2 = SameSide(p, b, a, c);
	bool s3 = SameSide(p, c, a, b);
	if( s1 && 
		s2 && 
		s3 )
		return true;
	else
		return false;
}

// SAMESIDE LINE FUNCTION
// intakes 2dimensional points, and converts to 3 dimensional points for cross product operation
bool TouchButton3D::SameSide( CIwVec2 p1_2d, CIwVec2 p2_2d, CIwVec2 a_2d, CIwVec2 b_2d )
{
	CIwVec3 p1( p1_2d.x, p1_2d.y, 0 );
	CIwVec3 p2( p2_2d.x, p2_2d.y, 0 );
	CIwVec3 a( a_2d.x, a_2d.y, 0 );
	CIwVec3 b( b_2d.x, b_2d.y, 0 );

	CIwVec3 cp1 = CrossProduct( b-a, p1-a );
	CIwVec3 cp2 = CrossProduct( b-a, p2-a );

	// Determining whether or not the point lies on the correct side

	// When there is a point and a side, the point and the end of a side
	// creates a vector. That vector, plus the side, makes 2 vectors.
	// The cross product is what the normal is of those 2 vectors.
	// the dot product is saying if the normal of the point with side
	// and the normal with third triangle vertex and side point in the same direction,
	// that means the point is on the correct side. 

	// But the dot product produces overflow of the int value sometimes with big numbers,
	// so we need to clamp the value of the Cross Products, or normals. 
	if( cp1.z > 0 )
		cp1.z = 1;
	else if( cp1.z < 0 )
		cp1.z = -1;

	if( cp2.z > 0 )
		cp2.z = 1;
	else if( cp2.z < 0 )
		cp2.z = -1;

	/*
	printf("Cross products are: %d, %d, %d and %d, %d, %d \n", cp1.x, cp1.y, cp1.z, cp2.x, cp2.y, cp2.z  );
	printf("Dot product is: %d \n", DotProduct(cp1, cp2) );
	*/

	if( DotProduct(cp1, cp2) >= 0 )
		return true;
	else
		return false;
}

// DOT PRODUCT
int16 TouchButton3D::DotProduct( CIwVec3 a, CIwVec3 b )
{
	int c = a.x * b.x + a.y * b.y + a.z * b.z;
	return c;
}

// CROSS PRODUCT
CIwVec3 TouchButton3D::CrossProduct( CIwVec3 a, CIwVec3 b )
{
	CIwVec3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return c;
}

void TouchButton3D::Terminate()
{
	delete material;
	delete texture;
	delete materialPressed;
	delete texturePressed;
}