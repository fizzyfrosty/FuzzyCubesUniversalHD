#pragma once
#include "s3e.h"
#include "IwGx.h"
#include "Cube.h"
#include "TouchButton3D.h"
#include "math.h" 

class MenuCube: public Cube // inherits cube.h
{
public:
	MenuCube(void);
	~MenuCube(void);

	void Initialize(int16 t, int16 n);
	void Render();
	void Update(); // update with the model matrix, and deltaX to determine location of menuCube for swiping
	void Terminate();
	void grabAndSetSwipe( int16 dx ); // controls the position of the menuCube externally
	void releaseSwipe(); // gives control back to menuCube to autosnap back its position
	bool isTouched( int16 x, int16 y ); 
	void setBobbleRotX( int16 x );
	void setBobbleRotY( int16 y );
	void setBobbleRotZ( int16 z );

	CIwSVec3 position; // the position of the menuCube, from 0 to circleDivisionNumber-1
	CIwSVec3 initialPosition; // initial position for keeping track of location for swiping. May not be needed. Not used right now.
	CIwMat bobbleRotX, bobbleRotY, bobbleRotZ; // rotation matrices for individual bobbling
	double bobbleAngleX, bobbleAngleY, bobbleAngleZ;
	double piXMultiple, piYMultiple, piZMultiple; // these are the intial phase-shift offsets for bobbling
	int16 s; // the sidelength
	int16 n; // the normal
	int16 type; // type set on initialization
	enum{ NEW, TUTORIAL, HIGH_SCORE, HELP, CREDITS, QUESTION_MARK,RAP_RECORD, CONTINUE, // THIS MUST BE IN SYNC WITH TOUCHBUTTON3D.H ENUMS
		CHALLENGE, QFCHAMBER, STORY };
	double startingAngle;
	double angleOffset; // used to add to starting angle to make -PI/2
	double deltaX; // used to control drag Sensitivity in grabAndSetSwipe()
	double savedDisplacedAngle;
	double savedAngle;
	int16 positionID; // this is an integer to calculate later on multiple of -PI/2, starting from 0+
	int16 circleDivisionNumber; // CDN is how many menu cubes exist in the circle
	bool lockedInPlace;

	bool beingSwiped; // tells if the menuCube is being controlled externally, so that it knows to calculate position based on theta
					// otherwise default to an auto-snap

	bool continueBobble;

	CIwSVec3 vertices[24];
	CIwSVec3 normals[24];
	CIwSVec2 uvstream[24];
	CIwSVec3 verticesTranslated[24];

	CIwSVec3 fuzzyVertices[4];
	CIwSVec3 fuzzyVerticesTranslated[4];
	CIwSVec3 fuzzyNormals[4];
	CIwSVec2 fuzzyUVStream[4];

	CIwMaterial* material;
	CIwTexture* texture;

	CIwMaterial* material2;
	CIwTexture* texture2;

	CIwMat modelMatrix;
	CIwMat rotX, rotY, rotZ; // the rotation matrices that affect the model matrix
	CIwMat translateBackward, translateForward; // used to center bobbling 
	int16 xRotation, yRotation, zRotation; // these are the values that affect Menu Cube's rotation corresponding to the respective axis
	int16 rotationIncrement; // this is how many degrees the cube rotates. Is effectively the rotation speed

	TouchButton3D button;
	/* obsolete
	TouchButton3D newButton;
	TouchButton3D highScoreButton;
	TouchButton3D helpButton;
	TouchButton3D creditsButton;

	TouchButton3D highScoreBackButton;
	TouchButton3D helpBackButton;
	TouchButton3D creditsBackButton;
	*/

	
};

