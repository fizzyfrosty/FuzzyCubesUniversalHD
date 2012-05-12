#include "ActiveSquare.h"


ActiveSquare::ActiveSquare(void)
{
}


ActiveSquare::~ActiveSquare(void)
{
}

void ActiveSquare::Initialize( int16 t )
{
	type = t;
	increment = 5;
	intensity = 0;
	plusMinusIndex = 1; // this is whether intensity is increasing or decreasing

	activated = false;
	fallingCubeExists = false;
	image = NULL;
	blankImage = NULL;

	x = 0;
	y = 0;

	//width = 25;
	//height = 25;
	width = IwGxGetScreenWidth() * .052;
	height = IwGxGetScreenWidth() * .052;
	float spacingIndex = 1;
	int xDisplacement = IwGxGetScreenWidth()*.365;

	red = 0;
	blue = 0;
	green = 0;
	alpha = 0;

	blankImage = Iw2DCreateImage( "blankSquare.png" );

	// set the coordinates and color/image
	if( type == BLUE )
	{
		//x = IwGxGetScreenWidth() - 175 + width;
		x = IwGxGetScreenWidth() - xDisplacement + width*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "blueSquare.png" );
	}
	if( type == RED )
	{
		//x = IwGxGetScreenWidth() - 175 + width*2;
		x = IwGxGetScreenWidth() - xDisplacement + width*2*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "redSquare.png" );
	}
	if( type == PURPLE )
	{
		//x = IwGxGetScreenWidth() - 175 + width*3;
		x = IwGxGetScreenWidth() - xDisplacement + width*3*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "purpleSquare.png" );
	}
	if( type == ORANGE )
	{
		//x = IwGxGetScreenWidth() - 175 + width*4;
		x = IwGxGetScreenWidth() - xDisplacement + width*4*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "orangeSquare.png" );
	}
	if( type == GREEN )
	{
		//x = IwGxGetScreenWidth() - 175 + width*5;
		x = IwGxGetScreenWidth() - xDisplacement + width*5*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "greenSquare.png" );
	}
	if( type == YELLOW )
	{
		//x = IwGxGetScreenWidth() - 175 + width*6;
		x = IwGxGetScreenWidth() - xDisplacement + width*6*spacingIndex;
		y = 0 + height;

		image = Iw2DCreateImage( "yellowSquare.png" );
	}
	
}

void ActiveSquare::Update( bool active, bool exists, int16 increm )
{
	activated = active;
	fallingCubeExists = exists;
	increment = increm;

	if( activated == true )
	{
		if( fallingCubeExists == true )
		{
			// make blink by incrementing alpha
			if( plusMinusIndex > 0 )
			{
				alpha += increment;
				red += increment;
				green += increment;
				blue += increment;
			}
			else
			{
				alpha -= increment;
				red -= increment;
				green -= increment;
				blue-= increment;
			}

			// update the intensity and color
			if(  alpha > 255 )
			{
				alpha = 255;
				plusMinusIndex *= -1;
			}
			if( alpha < 175 )
			{
				alpha = 175;
				plusMinusIndex *= -1;
			}

			if(  red > 255 )
			{
				red = 255;
				//plusMinusIndex *= -1;
			}
			if( red < 175 )
			{
				red = 175;
				//plusMinusIndex *= -1;
			}

			if(  green > 255 )
			{
				green = 255;
			}
			if( green < 175 )
			{
				green = 175;
			}

			if(  blue> 255 )
			{
				blue= 255;
			}
			if( blue< 175 )
			{
				blue= 175;
			}
		}
		else // if the plane side is active but cube is not falling
		{
			// make lighter
			if( alpha <= 25 )
			{
				alpha = 25;
			}
			else
			{
				alpha -= 5;
			}

			red = 255;
			green = 255;
			blue= 255;
		}
		
	}
	else if( activated == false )
	{
		if( alpha <= 50 )
		{
			alpha = 50;
		}
		else
		{
			alpha -= 5;
		}

		red = 255;
		green = 255;
		blue= 255;
	}

	color.Set( red, green, blue, alpha );
}

void ActiveSquare::Render()
{
	// get current color and alphamode to restore later
	CIwColour originalColor = Iw2DGetColour();
	CIw2DAlphaMode originalAlphaMode = Iw2DGetAlphaMode();

	// set color
	Iw2DSetColour( color );
	//Iw2DSetAlphaMode( CIw2DAlphaMode::IW_2D_ALPHA_ADD );

	if( activated )
	{
		// draw square. The Image Size, width * .052 is based off a 25 pixel size on a 480 width resolution screen
		//Iw2DDrawImageRegion( image, CIwSVec2( x - width/2, y - height/2 ), CIwSVec2( width, height ), CIwSVec2(0, 0), CIwSVec2(image->GetHeight(), image->GetWidth() ) );
		Iw2DDrawImageRegion( image, CIwSVec2( x - width/2, y - height/2 ), CIwSVec2( IwGxGetScreenWidth() * .052, IwGxGetScreenWidth() * .052 ), CIwSVec2(0, 0), CIwSVec2(image->GetHeight(), image->GetWidth() ) );
	}
	else
	{
		// draw blank square. The Image Size, width * .052 is based off a 25 pixel size on a 480 width resolution screen
		//Iw2DDrawImageRegion( blankImage, CIwSVec2( x - width/2, y - height/2 ), CIwSVec2( width, height ), CIwSVec2(0, 0), CIwSVec2(image->GetHeight(), image->GetWidth() ) );
		Iw2DDrawImageRegion( blankImage, CIwSVec2( x - width/2, y - height/2 ), CIwSVec2( IwGxGetScreenWidth() * .052, IwGxGetScreenWidth() * .052 ), CIwSVec2(0, 0), CIwSVec2(image->GetHeight(), image->GetWidth() ) );
	}

	// reset color
	Iw2DSetColour( originalColor );
	Iw2DSetAlphaMode( originalAlphaMode );
}

void ActiveSquare::Terminate()
{
	if( image != NULL )
	{
		delete image;
	}

	if( blankImage != NULL )
	{
		delete blankImage;
	}
}