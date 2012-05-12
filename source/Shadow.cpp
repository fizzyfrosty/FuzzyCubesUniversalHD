#include "Shadow.h"


Shadow::Shadow(void)
{
	position = CIwSVec3(0, 0, 0);
	initialPosition = CIwSVec3(0, 0, 0);
	spawnPosition = CIwSVec3(0, 0, 0);
	deltaDistance = CIwSVec3(0, 0, 0);	
	direction = 0;
	tapTime = 0; // used to see how long the shadow was touched
	touched = false;
	spawnPositionSet = false;

	cube = NULL;
	neighbor1 = NULL;
	neighbor2 = NULL;
	neighbor3 = NULL;
	neighbor4 = NULL;

	shadowGroup = NULL;

	point1 = CIwSVec3(0, 0, 0);
	point2 = CIwSVec3(0, 0, 0);
	point3 = CIwSVec3(0, 0, 0);
	point4 = CIwSVec3(0, 0, 0);

	material = 0;
}

Shadow::Shadow(int16 dir)
{
	position = CIwSVec3(0, 0, 0);
	initialPosition = position;
	spawnPosition = position;
	deltaDistance = CIwSVec3(0, 0, 0);	
	direction = dir;
	s = 100;
	tapTime = 0; // used to see how long the shadow was touched
	touched = false;
	spawnPositionSet = false;

	cube = NULL;
	neighbor1 = NULL;
	neighbor2 = NULL;
	neighbor3 = NULL;
	neighbor4 = NULL;

	shadowGroup = NULL;

	point1 = CIwSVec3(0, 0, 0);
	point2 = CIwSVec3(0, 0, 0);
	point3 = CIwSVec3(0, 0, 0);
	point4 = CIwSVec3(0, 0, 0);

	material = 0;
}

Shadow::Shadow(int16 dir, int16 sideLength)
{
	position = CIwSVec3(0, 0, 0);
	initialPosition = position;
	spawnPosition = position;
	deltaDistance = CIwSVec3(0, 0, 0);	
	direction = dir;
	s = sideLength;
	tapTime = 0; // used to see how long the shadow was touched
	touched = false;
	spawnPositionSet = false;

	cube = NULL;
	neighbor1 = NULL;
	neighbor2 = NULL;
	neighbor3 = NULL;
	neighbor4 = NULL;

	shadowGroup = NULL;

	// for picking
	point1 = CIwSVec3(0, 0, 0);
	point2 = CIwSVec3(0, 0, 0);
	point3 = CIwSVec3(0, 0, 0);
	point4 = CIwSVec3(0, 0, 0);

	material = 0;
}

void Shadow::linkCube( Cube* c )
{
	cube = c;
}

// sets the direction, and then initializes vertices of shadow for picking based on faceside direction
void Shadow::setDirection( int16 d )
{
	direction = d;
	setVertices( d );
	if( shadowGroup != NULL )
		shadowGroup->direction = d;
}

void Shadow::setVertices( int16 dir) // private
{
	// increase the area of hitbox
	int16 temp = s;
	s = s*3/2; // increasing the s value makes the hitboxes of the shadows bigger
	switch( direction ) // sees which side the shadow is facing
	{		/*
		case 1:
		// faceSide 1
		point1 = CIwSVec3(-s/2, -s/2, -s/2 ); 
		point2 = CIwSVec3( -s/2, s/2, -s/2 );
		point3 = CIwSVec3( s/2,  s/2, -s/2 );
		point4 = CIwSVec3( s/2, -s/2, -s/2 );
		break;
	case 2:
		// faceSide 2
		point1 = CIwSVec3( s/2 , -s/2,  -s/2);
		point2 = CIwSVec3( s/2 , s/2,  -s/2);
		point3 = CIwSVec3( s/2 ,  s/2, s/2);
		point4 = CIwSVec3( s/2 ,  -s/2, s/2);
		break;
	case 3:
		// faceSide 3
		point1 = CIwSVec3( s/2, -s/2,  s/2 );
		point2 = CIwSVec3( s/2, s/2,  s/2 );
		point3 = CIwSVec3( -s/2,  s/2, s/2 );
		point4 = CIwSVec3( -s/2,  -s/2, s/2 );
		break;
	case 4:
		// faceSide 4
		point1 = CIwSVec3( -s/2 , -s/2,  s/2);
		point2 = CIwSVec3( -s/2 , s/2,  s/2);
		point3 = CIwSVec3( -s/2 ,  s/2, -s/2);
		point4 = CIwSVec3( -s/2 ,  -s/2, -s/2);
		break;
	case 5:
		// faceSide 5
		point1 = CIwSVec3( -s/2, -s/2 ,  s/2);
		point2 = CIwSVec3( -s/2, -s/2 ,  -s/2);
		point3 = CIwSVec3( s/2,  -s/2 , -s/2);
		point4 = CIwSVec3( s/2, -s/2 , s/2);
		break;
	case 6:
		// faceSide 6
		point1 = CIwSVec3( -s/2, s/2 ,  -s/2);
		point2 = CIwSVec3( -s/2, s/2 ,  s/2);
		point3 = CIwSVec3( s/2,  s/2 , s/2);
		point4 = CIwSVec3( s/2,  s/2 , -s/2);
		break;
		*/

	case 1:
		// faceSide 1
		point1 = CIwSVec3(-s/2, -s/2, -s/2 - temp); // adding the -s/+s (temp) makes the shadow's hitbox one level higher toward camera
		point2 = CIwSVec3( -s/2, s/2, -s/2 - temp); // the hitbox is now at the end of the blinking transparent shadow
		point3 = CIwSVec3( s/2,  s/2, -s/2 - temp);
		point4 = CIwSVec3( s/2, -s/2, -s/2 - temp); 
		break;
	case 2:
		// faceSide 2
		point1 = CIwSVec3( s/2 + temp, -s/2,  -s/2);
		point2 = CIwSVec3( s/2 + temp, s/2,  -s/2);
		point3 = CIwSVec3( s/2 + temp,  s/2, s/2);
		point4 = CIwSVec3( s/2 + temp,  -s/2, s/2);
		break;
	case 3:
		// faceSide 3
		point1 = CIwSVec3( s/2, -s/2,  s/2 + temp);
		point2 = CIwSVec3( s/2, s/2,  s/2 + temp);
		point3 = CIwSVec3( -s/2,  s/2, s/2 + temp);
		point4 = CIwSVec3( -s/2,  -s/2, s/2 + temp);
		break;
	case 4:
		// faceSide 4
		point1 = CIwSVec3( -s/2 - temp, -s/2,  s/2);
		point2 = CIwSVec3( -s/2 - temp, s/2,  s/2);
		point3 = CIwSVec3( -s/2 - temp,  s/2, -s/2);
		point4 = CIwSVec3( -s/2 - temp,  -s/2, -s/2);
		break;
	case 5:
		// faceSide 5
		point1 = CIwSVec3( -s/2, -s/2 - temp,  s/2);
		point2 = CIwSVec3( -s/2, -s/2 - temp,  -s/2);
		point3 = CIwSVec3( s/2,  -s/2 - temp, -s/2);
		point4 = CIwSVec3( s/2, -s/2 - temp, s/2);
		break;
	case 6:
		// faceSide 6
		point1 = CIwSVec3( -s/2, s/2 + temp,  -s/2);
		point2 = CIwSVec3( -s/2, s/2 + temp,  s/2);
		point3 = CIwSVec3( s/2,  s/2 + temp, s/2);
		point4 = CIwSVec3( s/2,  s/2 + temp, -s/2);
		break;
		
	}

	// reset the size
	s = temp;
}

void Shadow::setModelMatrix( CIwMat mm )
{
	modelmatrix = mm;
}

bool Shadow::isTouched( int16 x, int16 y )
{
	// updates points based on shadow's current position
	// transforming the vertices by the modelmatrix gets absolute coordinates of vertices after camera rotation
	point1Transformed = modelmatrix.TransformVec( point1 + position );
	point2Transformed = modelmatrix.TransformVec( point2 + position );
	point3Transformed = modelmatrix.TransformVec( point3 + position );
	point4Transformed = modelmatrix.TransformVec( point4 + position );

	// returns true if both hitboxes of triangles that make up the square is touched
	// Uses isTriangleTouched to determine if the point-touched lies inside the 3-abs-coordinate points
	if( isTriangleTouched( (CIwVec3)point1Transformed, (CIwVec3)point2Transformed, (CIwVec3)point3Transformed, x, y ) == true || 
		isTriangleTouched((CIwVec3)point1Transformed, (CIwVec3)point3Transformed, (CIwVec3)point4Transformed, x, y ) == true )
	{
		// not only is it in the triangle, but the triangle's normal must also be facing the camera
		CIwVec3 normal = CrossProduct( (CIwVec3)(point4Transformed - point1Transformed), (CIwVec3)(point2Transformed - point1Transformed) );
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

bool Shadow::isTriangleTouched( CIwVec3 v1, CIwVec3 v2, CIwVec3 v3, int16 x, int16 y )
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
bool Shadow::PointInTriangle( CIwVec2 p, CIwVec2 a, CIwVec2 b, CIwVec2 c )
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
bool Shadow::SameSide( CIwVec2 p1_2d, CIwVec2 p2_2d, CIwVec2 a_2d, CIwVec2 b_2d )
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
int16 Shadow::DotProduct( CIwVec3 a, CIwVec3 b )
{
	int c = a.x * b.x + a.y * b.y + a.z * b.z;
	return c;
}

// CROSS PRODUCT
CIwVec3 Shadow::CrossProduct( CIwVec3 a, CIwVec3 b )
{
	CIwVec3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return c;
}

void Shadow::setTouchIntersection( int16 x, int16 y )
{
	point1Translated = point1 + initialPosition;
	point2Translated = point2 + initialPosition;
	point3Translated = point3 + initialPosition;
	point4Translated = point4 + initialPosition;

	// The direction vector is the source of where the touch comes from.
	// Because the world coordinates have (0,0,0) as the center, and the x and y's origin of touch are 
	// at the upper left corner of screen, we center the origin to middle of screen with minus width/2, minus height/2.
	// When displaying the models, they are transformed by the ModelMatrix for camera rotation. So the direction vector must
	// account for this by rotating in the "reverse angle," which is why we transpose it with the model matrix.
	// We are only doing transpose Rotate because only rotation transforms have been applied to models.
	CIwVec3 directionVector = CIwVec3( x - IwGxGetScreenWidth()/2, y - IwGxGetScreenHeight()/2, IwGxGetPerspMul() );
	//directionVector = IwGxGetModelMatrix().TransposeRotateVec( directionVector );
	directionVector = modelmatrix.TransposeRotateVec( directionVector );


	// The origin of the touch/eye/ray is obtained from the view matrix here, which is where the camera/eye is.
	// It is just the coordinate position, separate from the direction. 
	// Once again, we rotate it in the "reverse angle" of the model matrix that transformed the stuff in the world,
	// so that it is still "facing the front" of the models
	// We are only doing transpose rotation b/c only rotation transforms have been applied to the models.
	//CIwVec3 origin(0, 0, 0);
	CIwVec3 origin = IwGxGetViewMatrix().t;
	origin = IwGxGetModelMatrix().TransposeRotateVec( origin );

	// We are using the airplay's normalize function, which uses fixed-point number system.
	normal = CrossProduct( (CIwVec3)(point2Translated - point1Translated), (CIwVec3)(point3Translated - point1Translated) );
	normal.Normalise(); // The normal vector MUST be normalized, a magnitude of 1

	// Thus we must convert it back to 16bit/32bit integers for our own math.
	CIwVec3 normalizedNormal( IW_GEOM_ROUND(normal.x), IW_GEOM_ROUND(normal.y), IW_GEOM_ROUND(normal.z) );

	if( DotProduct( normalizedNormal, directionVector ) != 0 ) // checks for division by zero
		distance = DotProduct( normalizedNormal, point1Translated - origin ) / DotProduct( normalizedNormal, directionVector );
		// ^ this is part of the Formula for Intersection:
		// distance = (plane_normal dot ( point_in_plane - ray origin)) / (plane_normal dot ray_direction)
		// Then, intersection = ray_origin + (ray_direction * distance) calculated down below
	else
		printf("Division by zero. \n");

	// directionS is the direction vector scaled / multiplied by the distance.
	CIwVec3 directionS;

	directionS.x = directionVector.x * distance;
	directionS.y = directionVector.y * distance;
	directionS.z = directionVector.z * distance;
	
	intersection = origin + directionS;
	/*
	printf("initialPosition is %d, %d, %d ", initialPosition.x, initialPosition.y, initialPosition.z );
	printf("point1translated is %d, %d, %d ", point1Translated.x, point1Translated.y, point1Translated.z );
	printf("intersection is %d, %d, %d \n", intersection.x, intersection.y, intersection.z );
	*/
}

// uses the intersection point to convert to a position on the "grid" with length of s
void Shadow::convertToGridLocation( int16 widthUnits, int16 heightUnits, int16 depthUnits )
{
	int16 multipleX, multipleY, multipleZ; // determines how many times to multiply sidelength to get new position
	int16 posnegx, posnegy, posnegz; // keeps track if the intersection coordinate is positive or negative

	int16 delta;
	int16 limit; // right now, the limit changes every time depending on where the bounds are.
				// this makes things very confusing and needs a lot of updating. trying to change implementation right now...

	if( widthUnits % 2 == 1 ) // if the sides are ODD
	{
		// different for each faceside
		switch( direction )
		{
		// Case 1 and 3, 2 and 4, 5 and 6 are all the same respectively as pairs ----------------------------
		case 1:
			if( intersection.x >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleX = (intersection.x + s/2) / s;
			else
				multipleX = (intersection.x - s/2) / s; 

			if( intersection.y >= 0 )
				multipleY = (intersection.y + s/2) / s;
			else
				multipleY = (intersection.y - s/2) / s;

			gridLocation.x = multipleX * s;
			gridLocation.y = multipleY * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.x = position.x;

			//printf("delta is %d \n", delta );
			//printf("limit is %d \n", limit );

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.x = gridLocation.x;
			position.y = gridLocation.y;

			
			//printf("grid location x, y is %d, %d \n", gridLocation.x, gridLocation.y );
			//printf("left bound is %d. Right bound is %d \n", shadowGroup->leftBound, shadowGroup->rightBound );

			break;
		case 2:
			if( intersection.z >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleZ = (intersection.z + s/2) / s;
			else
				multipleZ = (intersection.z - s/2) / s; 

			if( intersection.y >= 0 )
				multipleY = (intersection.y + s/2) / s;
			else
				multipleY = (intersection.y - s/2) / s;

			gridLocation.z = multipleZ * s;
			gridLocation.y = multipleY * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )
				gridLocation.z = position.z;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.z = position.z;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.z = gridLocation.z;
			position.y = gridLocation.y;
			break;
		case 3:
			if( intersection.x >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleX = (intersection.x + s/2) / s;
			else
				multipleX = (intersection.x - s/2) / s; 

			if( intersection.y >= 0 )
				multipleY = (intersection.y + s/2) / s;
			else
				multipleY = (intersection.y - s/2) / s;

			gridLocation.x = multipleX * s;
			gridLocation.y = multipleY * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit ) // the x limits are reversed from face1, because face3 is mirror
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.x = position.x;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.x = gridLocation.x;
			position.y = gridLocation.y;
			break;
		case 4:
			if( intersection.z >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleZ = (intersection.z + s/2) / s;
			else
				multipleZ = (intersection.z - s/2) / s; 

			if( intersection.y >= 0 )
				multipleY = (intersection.y + s/2) / s;
			else
				multipleY = (intersection.y - s/2) / s;

			gridLocation.z = multipleZ * s;
			gridLocation.y = multipleY * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit ) // limits are reversed from face 2 b/c face 4 has mirror z-axis
				gridLocation.z = position.z;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.z = position.z;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.z = gridLocation.z;
			position.y = gridLocation.y;
			break;
		case 5:
			if( intersection.z >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleZ = (intersection.z + s/2) / s;
			else
				multipleZ = (intersection.z - s/2) / s; 

			if( intersection.x >= 0 )
				multipleX = (intersection.x + s/2) / s;
			else
				multipleX = (intersection.x - s/2) / s;

			gridLocation.z = multipleZ * s;
			gridLocation.x = multipleX * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit )
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.x = position.x;

			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta > limit )
				gridLocation.z = position.z;
			else if( shadowGroup->bottomBound + delta < -1*limit )
				gridLocation.z = position.z;

			position.z = gridLocation.z;
			position.x = gridLocation.x;
			break;
		case 6:
			if( intersection.z >= 0 ) // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
				multipleZ = (intersection.z + s/2) / s;
			else
				multipleZ = (intersection.z - s/2) / s; 

			if( intersection.x >= 0 )
				multipleX = (intersection.x + s/2) / s;
			else
				multipleX = (intersection.x - s/2) / s;

			gridLocation.z = multipleZ * s;
			gridLocation.x = multipleX * s;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits - 1) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )  // both the x and z's are reversed for faceside 6 because of the "right-side up" orientation
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.x = position.x;

			delta = gridLocation.z - initialPosition.z; // clamps the y positions
			limit = (heightUnits - 1) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.z = position.z;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.z = position.z;

			position.z = gridLocation.z;
			position.x = gridLocation.x;
			break;
		}		
	}
	else // if side type is even
	{
		switch( direction )
		{
		// Case 1 and 3, 2 and 4, 5 and 6 are all the same respectively as pairs ----------------------------
		case 1:			
			multipleX = (intersection.x) / s;
			multipleY = (intersection.y) / s;

			if( intersection.x >= 0 )
				gridLocation.x = multipleX * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.x = multipleX * s - s/2;

			if( intersection.y >= 0 )
				gridLocation.y = multipleY * s + s/2;
			else
				gridLocation.y = multipleY * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.x = position.x;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.x = gridLocation.x;
			position.y = gridLocation.y;
			break;
		case 2:
			multipleZ = (intersection.z) / s;
			multipleY = (intersection.y) / s;

			if( intersection.z >= 0 )
				gridLocation.z = multipleZ * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.z = multipleZ * s - s/2;

			if( intersection.y >= 0 )
				gridLocation.y = multipleY * s + s/2;
			else
				gridLocation.y = multipleY * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )
				gridLocation.z = position.z;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.z = position.z;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.z = gridLocation.z;
			position.y = gridLocation.y;
			break;
		case 3:
			multipleX = (intersection.x) / s;
			multipleY = (intersection.y) / s;

			if( intersection.x >= 0 )
				gridLocation.x = multipleX * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.x = multipleX * s - s/2;

			if( intersection.y >= 0 )
				gridLocation.y = multipleY * s + s/2;
			else
				gridLocation.y = multipleY * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit ) // the x limits are reversed from face1, because face3 is mirror
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.x = position.x;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.x = gridLocation.x;
			position.y = gridLocation.y;
			break;
		case 4:
			multipleZ = (intersection.z) / s;
			multipleY = (intersection.y) / s;

			if( intersection.z >= 0 )
				gridLocation.z = multipleZ * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.z = multipleZ * s - s/2;

			if( intersection.y >= 0 )
				gridLocation.y = multipleY * s + s/2;
			else
				gridLocation.y = multipleY * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit ) // limits are reversed from face 2 b/c face 4 has mirror z-axis
				gridLocation.z = position.z;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.z = position.z;

			delta = gridLocation.y - initialPosition.y; // clamps the y positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.y = position.y;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.y = position.y;

			position.z = gridLocation.z;
			position.y = gridLocation.y;
			break;
		case 5:
			multipleZ = (intersection.z) / s;
			multipleX = (intersection.x) / s;

			if( intersection.z >= 0 )
				gridLocation.z = multipleZ * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.z = multipleZ * s - s/2;

			if( intersection.x >= 0 )
				gridLocation.x = multipleX * s + s/2;
			else
				gridLocation.x = multipleX * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta > limit )
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta < -1*limit )
				gridLocation.x = position.x;

			delta = gridLocation.z - initialPosition.z; // clamps the z positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta > limit )
				gridLocation.z = position.z;
			else if( shadowGroup->bottomBound + delta < -1*limit )
				gridLocation.z = position.z;

			position.z = gridLocation.z;
			position.x = gridLocation.x;
			break;
		case 6:
			multipleZ = (intersection.z) / s;
			multipleX = (intersection.x) / s;

			if( intersection.z >= 0 )
				gridLocation.z = multipleZ * s + s/2; // checks to see if on positive or negative side of axis. Lock is different for pos and neg sides
			else
				gridLocation.z = multipleZ * s - s/2;

			if( intersection.x >= 0 )
				gridLocation.x = multipleX * s + s/2;
			else
				gridLocation.x = multipleX * s - s/2;

			// CLAMPS THE POSITION so that it does not move off the base
			delta = gridLocation.x - initialPosition.x; // clamps the x positions
			limit = (widthUnits) / 2 * s;
			// clamps the location based on the shadow group's bounds
			if( shadowGroup->leftBound + delta < -1*limit )  // both the x and z's are reversed for faceside 6 because of the "right-side up" orientation
				gridLocation.x = position.x;
			if( shadowGroup->rightBound + delta > limit )
				gridLocation.x = position.x;

			delta = gridLocation.z - initialPosition.z; // clamps the y positions
			limit = (heightUnits) / 2 * s;
			if( shadowGroup->topBound + delta < -1*limit )
				gridLocation.z = position.z;
			else if( shadowGroup->bottomBound + delta > limit )
				gridLocation.z = position.z;

			position.z = gridLocation.z;
			position.x = gridLocation.x;
			break;
		}
	}

	deltaTranslation = position - initialPosition;

	// need to CLAMP the position so it does not go off cube


}


CIwSVec3 Shadow::getDeltaTranslation()
{
	return deltaTranslation;
}


Shadow::~Shadow(void)
{
	neighbor1 = NULL;
	neighbor2 = NULL;
	neighbor3 = NULL;
	neighbor4 = NULL;

	cube = NULL;

	shadowGroup = NULL;

}

void Shadow::setSpawnPosition( CIwSVec3 pos )
{
	if( spawnPositionSet == false )
	{
		spawnPosition = pos;
		spawnPositionSet = true; // this ensures spawn position is only set once when cubes are spawned
	}
}

// copy constructor may not have been required. Error was initially initialPosition getting adjusted, but fixed in LinkShadowToCube() in fuzzycubes.cpp
// in fact, this may be causing errors trying to access shadow.shadowGroup even if it is NULL. It may not have been set to NULL internally...
/*
Shadow& Shadow::operator=(const Shadow &shadow)
{

	this->position = shadow.position;
	this->initialPosition = shadow.initialPosition;
	this->spawnPosition = shadow.spawnPosition;
	this->deltaDistance = shadow.deltaDistance;
	this->direction = shadow.direction;
	this->s = shadow.s;
	this->tapTime = shadow.tapTime; // used to see how long the shadow was touched
	this->touched = shadow.touched;
	this->spawnPositionSet = shadow.spawnPositionSet;

	if( shadow.shadowGroup != NULL )
		this->shadowGroup = shadow.shadowGroup;

	// for picking
	this->point1 = shadow.point1;
	this->point2 = shadow.point2;
	this->point3 = shadow.point3;
	this->point4 = shadow.point4;

	this->material = shadow.material;

	if( shadow.cube != NULL )
	{
		this->cube = shadow.cube;
	}

	return *this;
}
*/