#pragma once

#include "s3e.h"
#include "IwGx.h"


class TouchButton3D
{
public:
	TouchButton3D(void);
	~TouchButton3D(void);
	void Initialize( int16 t, int16 dir ); // type, direction
	void Render();
	void Update( CIwSVec2 location, CIwMat matrix, CIwSVec3 pos ); // updates with the position. Basically this method creates vertex streams for rendering
	void Terminate();
	void setLocation( int16 x, int16 y );
	void setSize( int16 width, int16 height );
	bool isTouched( int16 x, int16 y );
	void setModelMatrix( CIwMat matrix );

	CIwSVec2 position; // the position is a 2d vector b/c it represents the coordinate-position of a side of the menu cube
	CIwSVec3 base_vertices[4];
	CIwSVec3 vertices[4];	
	CIwSVec3 verticesTranslated[4];
	CIwSVec3 normals[4];
	CIwSVec2 uvstream[4];
	int16 direction;
	CIwMat modelMatrix; // for touch calculations
	CIwSVec2 size;

	int16 s; // s is the side length of MenuCube
	int16 n; // n is the normal

	CIwMaterial* material;
	CIwTexture* texture;

	CIwMaterial* materialPressed; // this is the material/image displayed if the button is pressed
	CIwTexture* texturePressed;

	bool pressed; // pressed handles the image that is being displayed, either pressed image or unpressed image
	bool initialPressed;
	bool activated; // activated handles the activation of the purpose of the button

	int16 type; // this is used in initialization to determine what kind of button is created
	enum {  NEW, TUTORIAL, HIGH_SCORE, HELP, CREDITS, QUESTION_MARK, RAP_RECORD, CONTINUE,  // THIS MUST BE IN SYNC WITH MENUCUBE.H ENUMS
		CHALLENGE, QFCHAMBER, STORY, HIGH_SCORE_BACK, HELP_BACK, CREDITS_BACK };

private:
	// these are the touch methods used in Shadow.h to determine if a 3D surface of 4 vertices is touched
	bool isTriangleTouched( CIwVec3 v1, CIwVec3 v2, CIwVec3 v3, int16 x, int16 y );
	bool PointInTriangle( CIwVec2 p, CIwVec2 a, CIwVec2 b, CIwVec2 c );
	bool SameSide( CIwVec2 p1_2d, CIwVec2 p2_2d, CIwVec2 a_2d, CIwVec2 b_2d );
	int16 DotProduct( CIwVec3 a, CIwVec3 b );
	CIwVec3 CrossProduct( CIwVec3 a, CIwVec3 b );


};

