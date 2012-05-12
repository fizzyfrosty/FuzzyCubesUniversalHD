#pragma once

#include "Sprite.h"


class PointSprite: public Sprite
{
public:


	PointSprite(void);
	void setType( int16 t );
	void Render();
	bool finishedRendering();

	void set50PointsImage( CIw2DImage* i );
	void set100PointsImage( CIw2DImage* i );
	void set500PointsImage( CIw2DImage* i );
	void set1000PointsImage( CIw2DImage* i );
	void set5000PointsImage( CIw2DImage* i );
	void set10000PointsImage( CIw2DImage* i );
	//void set50PointsImage( CIw2DImage* i );

	int16 type;
	enum{ NONE, FIFTY, ONE_HUNDRED, FIVE_HUNDRED, ONE_THOUSAND, FIVE_THOUSAND, TEN_THOUSAND };

	CIw2DImage* pointsImage50;
	CIw2DImage* pointsImage100;
	CIw2DImage* pointsImage500;
	CIw2DImage* pointsImage1000;
	CIw2DImage* pointsImage5000;
	CIw2DImage* pointsImage10000;
	//CIw2DImage* pointsImage20000;


	~PointSprite(void);
};

