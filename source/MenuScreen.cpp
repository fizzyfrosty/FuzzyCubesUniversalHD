#include "MenuScreen.h"


MenuScreen::MenuScreen(void)
{
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::Initialize( int16 t )
{
	image = Iw2DCreateImage("splash.png");

	//counter = 0;
	buttonCount = 0;
	type = t;
	sprite.setUWidth( 480 );
	sprite.setUHeight( 320 );
	//sprite.setSize( 480, 320 );
	sprite.setSize( IwGxGetScreenWidth(), IwGxGetScreenHeight() );
	sprite.setImage( image );
	sprite.setPosition( IwGxGetScreenWidth()/2, -IwGxGetScreenHeight()/2 );

	if( type == CHALLENGE )
	{
		int row = 1;
		int column = 1;
		buttonCount = 21;

		// make 20 buttons for levels, 1 button to go back
		for( int i = 0; i < buttonCount; i++ )
		{
			// add if-condition here to create a different image for every button

			buttonImageArray[i] = Iw2DCreateImage("test.png");
			buttonSprite[i].setImage( buttonImageArray[i] );
			buttonSprite[i].setUWidth( 128 );
			buttonSprite[i].setUHeight( 128 );
			buttonSprite[i].setSize( 40, 40 );

			buttonImageArray_pressed[i] = Iw2DCreateImage("menuButton_Touched.png");
			buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
			buttonSprite_pressed[i].setUWidth( 128 );
			buttonSprite_pressed[i].setUHeight( 128 );
			buttonSprite_pressed[i].setSize( 40, 40 );

			button[i].setUnpressedSprite( buttonSprite[i] );
			button[i].setPressedSprite( buttonSprite_pressed[i] );
			button[i].setTouchSize( 40, 40 );
			button[i].setLocation( column*buttonSprite[i].size.x + 30*(column) + 35, row*buttonSprite[i].size.y + 15*(row) + 5 - IwGxGetScreenHeight()/2 );
			

			// increment the rows/columns
			column++;
			if( column >= 6 )
			{
				column = 1;
				row++;
			}
			
		} // end of for-loop creating buttons
	} // end of type == challenge menu
	else if( type == HIGH_SCORE )
	{
		delete image;
		image = Iw2DCreateImage("highscore_screen.png");
		// high score screen has back button, and Rate button
		buttonCount = 12; // buttons 0-1 are rate, 2-6 are black trophies, 7-11 are trophies

		for( int i = 0; i < NUM_OF_TROPHIES; i++ )
		{
			trophies[i] = false;
		}

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0: // RATE button
				buttonImageArray[i] = Iw2DCreateImage("rateButton_red.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("rateButton_green.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 64 );
				buttonSprite[i].setUHeight( 64 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 64 );
				buttonSprite_pressed[i].setUHeight( 64 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );

				//button[i].setLocation( 50, 100 ); // not affected here. in render
				break;
			case 1: // BACK button
				buttonImageArray[i] = Iw2DCreateImage("backButton_red.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("backButton_green.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 64 );
				buttonSprite[i].setUHeight( 64 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 64 );
				buttonSprite_pressed[i].setUHeight( 64 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );

				//button[i].setLocation( 300, 100 ); // not affected here. in render
				break;
			case 2: // all the BLACK TROPHY buttons
			case 3:
			case 4:
			case 5:
			case 6:
				buttonImageArray[i] = Iw2DCreateImage("trophyButton_black.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("trophyButton_black.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 100 );
				buttonSprite[i].setUHeight( 100 );
				//buttonSprite[i].setSize( 100, 100 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .208, IwGxGetScreenWidth() * .208 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 100 );
				buttonSprite_pressed[i].setUHeight( 100 );
				//buttonSprite_pressed[i].setSize( 80, 80 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .167, IwGxGetScreenWidth() * .167 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .167, IwGxGetScreenWidth() * .167 );
				break;
			case 7:
			case 8:
			case 9:
			case 10:
			case 11: // all the REGULAR TROPHY buttons
				buttonImageArray[i] = Iw2DCreateImage("trophyButton.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("trophyButton.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 64 );
				buttonSprite[i].setUHeight( 64 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 64 );
				buttonSprite_pressed[i].setUHeight( 64 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
				break;
			}
		}

	} // end of type == high score
	else if( type == CREDITS )
	{
		delete image;
		image = Iw2DCreateImage("credits_screen.png");

		// high score screen has back button, and Rate button
		buttonCount = 2;

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0: // RATE button
				buttonImageArray[i] = Iw2DCreateImage("rateButton_red.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("rateButton_green.png");
				button[i].setLocation( 50, 100 );
				break;
			case 1: // BACK button
				buttonImageArray[i] = Iw2DCreateImage("backButton_red.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("backButton_green.png");
				button[i].setLocation( 300, 100 );
				break;
			}
			
			buttonSprite[i].setImage( buttonImageArray[i] );
			buttonSprite[i].setUWidth( 64 );
			buttonSprite[i].setUHeight( 64 );
			//buttonSprite[i].setSize( 64, 64 );
			buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
			buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
			buttonSprite_pressed[i].setUWidth( 64 );
			buttonSprite_pressed[i].setUHeight( 64 );
			//buttonSprite_pressed[i].setSize( 50, 50 );
			buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

			button[i].setUnpressedSprite( buttonSprite[i] );
			button[i].setPressedSprite( buttonSprite_pressed[i] );
			//button[i].setTouchSize( 64, 64 );
			button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
		}
	}
	else if( type == TUTORIAL )
	{
		delete image;
		image = Iw2DCreateImage("tutorial.png");

		// high score screen has back button, and Rate button
		buttonCount = 4;

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0:
				buttonImageArray[i] = Iw2DCreateImage("backButton_red.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("backButton_green.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 64 );
				buttonSprite[i].setUHeight( 64 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 64 );
				buttonSprite_pressed[i].setUHeight( 64 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
				break;
			case 1:
				buttonImageArray[i] = Iw2DCreateImage("buttonBasic.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("buttonBasic.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
				break;
			case 2:
				buttonImageArray[i] = Iw2DCreateImage("buttonDanger.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("buttonDanger.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
				break;
			case 3:
				buttonImageArray[i] = Iw2DCreateImage("buttonDefuse.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("buttonDefuse.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 64, 64 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 50, 50 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .104, IwGxGetScreenWidth() * .104 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 64, 64 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .133, IwGxGetScreenWidth() * .133 );
				break;
			}			
		}
	}
	else if( type == QUIT_CONFIRMATION )
	{
		delete image;
		image = Iw2DCreateImage("quitconfirmation.png");
		sprite.setUWidth( 480 );
		sprite.setUHeight( 320 );
		//sprite.setSize( 480, 320 );
		sprite.setSize( IwGxGetScreenWidth(), IwGxGetScreenHeight() );
		sprite.setImage( image );
		sprite.setPosition( IwGxGetScreenWidth()/2, IwGxGetScreenHeight()/2 );

		// high score screen has back button, and Rate button
		buttonCount = 2;

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0:
				buttonImageArray[i] = Iw2DCreateImage("quitconfirmation_yes.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("quitconfirmation_yes.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 128, 128 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 100, 100 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .208, IwGxGetScreenWidth() * .208 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 128, 128 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
				break;
			case 1:
				buttonImageArray[i] = Iw2DCreateImage("quitconfirmation_no.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("quitconfirmation_no.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 128, 128 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 100, 100 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .208, IwGxGetScreenWidth() * .208 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 128, 128 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
				break;
			}			
		}
	}
	else if( type == NEW_STORY_CONFIRMATION )
	{
		delete image;
		image = Iw2DCreateImage("newstoryconfirmation.png");
		sprite.setUWidth( 480 );
		sprite.setUHeight( 320 );
		//sprite.setSize( 480, 320 );
		sprite.setSize( IwGxGetScreenWidth(), IwGxGetScreenHeight() );
		sprite.setImage( image );
		sprite.setPosition( IwGxGetScreenWidth()/2, IwGxGetScreenHeight()/2 );

		// high score screen has back button, and Rate button
		buttonCount = 2;

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0:
				buttonImageArray[i] = Iw2DCreateImage("quitconfirmation_yes.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("quitconfirmation_yes.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 128, 128 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 100, 100 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .208, IwGxGetScreenWidth() * .208 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 128, 128 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );

				break;
			case 1:
				buttonImageArray[i] = Iw2DCreateImage("quitconfirmation_no.png");
				buttonImageArray_pressed[i] = Iw2DCreateImage("quitconfirmation_no.png");

				buttonSprite[i].setImage( buttonImageArray[i] );
				buttonSprite[i].setUWidth( 128 );
				buttonSprite[i].setUHeight( 128 );
				//buttonSprite[i].setSize( 128, 128 );
				buttonSprite[i].setSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
			
				buttonSprite_pressed[i].setImage( buttonImageArray_pressed[i] );	
				buttonSprite_pressed[i].setUWidth( 128 );
				buttonSprite_pressed[i].setUHeight( 128 );
				//buttonSprite_pressed[i].setSize( 100, 100 );
				buttonSprite_pressed[i].setSize( IwGxGetScreenWidth() * .208, IwGxGetScreenWidth() * .208 );

				button[i].setUnpressedSprite( buttonSprite[i] );
				button[i].setPressedSprite( buttonSprite_pressed[i] );
				//button[i].setTouchSize( 128, 128 );
				button[i].setTouchSize( IwGxGetScreenWidth() * .267, IwGxGetScreenWidth() * .267 );
				break;
			}
		}
	}
	else if( type == QUESTION_MARK )
	{
		delete image;
		image = Iw2DCreateImage("questionmarkinfo.png");
		sprite.setUWidth( 480 );
		sprite.setUHeight( 320 );
		//sprite.setSize( 480, 320 );
		sprite.setSize( IwGxGetScreenWidth(), IwGxGetScreenHeight() );
		sprite.setImage( image );
		sprite.setPosition( IwGxGetScreenWidth()/2, IwGxGetScreenHeight()/2 );
	}

} // end of initialize()

void MenuScreen::Terminate()
{
	delete image; 

	for( int i = 0; i < buttonCount; i++ )
	{
		//delete buttonImage[i];
		//delete buttonImage_pressed[i];

		delete buttonImageArray[i];
		delete buttonImageArray_pressed[i];
	}

	/*
	// delete the messages for obtaining trophies
	if( type == HIGH_SCORE )
	{
		for( int i = 0; i < NUM_OF_TROPHIES; i++ )
		{
			delete getTrophyMessagesImages[i];
			delete gotTrophyMessagesImages[i];
		}
	}
	*/
}

// only need for high score menu screen
void MenuScreen::Update( bool trophies[], long highScore, int timeSeconds, int timeMinutes, int timeHours )
{
	for( int i = 0; i < NUM_OF_TROPHIES; i++ )
	{
		this->trophies[i] = trophies[i];
	}

	this->highScore = highScore;
	this->timeSeconds = timeSeconds;
	this->timeMinutes = timeMinutes;
	this->timeHours = timeHours;
}

void MenuScreen::Render()
{
	sprite.Render();

	if( type == CHALLENGE )
	{
		int row = 1;
		int column = 1;
		for( int i = 0; i < buttonCount; i++ )
		{
			button[i].setLocation( (column*buttonSprite[i].size.x + 30*(column) + 35) + (sprite.position.x - IwGxGetScreenWidth()/2), (row*buttonSprite[i].size.y + 15*(row) + 5) + (sprite.position.y - IwGxGetScreenHeight()/2) );
			button[i].Render();

			// increment the rows/columns
			column++;
			if( column >= 6 )
			{
				column = 1;
				row++;
			}
		}
	}
	else if( type == HIGH_SCORE )
	{

		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0:
				//button[i].setLocation( sprite.position.x - 75, sprite.position.y + 122 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .156, sprite.position.y + IwGxGetScreenHeight() * .381 );
				button[i].Render();
				break;
			case 1:
				//button[i].setLocation( sprite.position.x + 97, sprite.position.y + 122 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .202, sprite.position.y +  IwGxGetScreenHeight() * .381);
				button[i].Render();
				break;
			case 2: // render black trophies
				//button[i].setLocation( sprite.position.x - 190, sprite.position.y - 75 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .396, sprite.position.y - IwGxGetScreenHeight() * .234);
				if( trophies[0] == false )
				{
					button[i].Render();
				}
				break;
			case 3:
				//button[i].setLocation( sprite.position.x + 183, sprite.position.y - 80 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .381, sprite.position.y - IwGxGetScreenHeight() * .25 );
				if( trophies[1] == false )
				{
					button[i].Render();
				}
				break;
			case 4:
				//button[i].setLocation( sprite.position.x - 190, sprite.position.y + 50 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .396, sprite.position.y + IwGxGetScreenHeight() * .156);
				if( trophies[2] == false )
				{
					button[i].Render();
				}
				break;
			case 5:
				//button[i].setLocation( sprite.position.x + 12, sprite.position.y + 63 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .025, sprite.position.y + IwGxGetScreenHeight() * .197);
				if( trophies[3] == false )
				{
					button[i].Render();
				}
				break;
			case 6:
				//button[i].setLocation( sprite.position.x + 187, sprite.position.y + 45 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .390, sprite.position.y + IwGxGetScreenHeight() * .141);
				if( trophies[4] == false )
				{
					button[i].Render();
				}
				break;
			case 7:
				//button[i].setLocation( sprite.position.x - 190, sprite.position.y - 75 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .396, sprite.position.y - IwGxGetScreenHeight() * .234);
				if( trophies[0] == true )
				{
					button[i].Render();
				}
				break;
			case 8:
				//button[i].setLocation( sprite.position.x + 183, sprite.position.y - 80 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .381, sprite.position.y - IwGxGetScreenHeight() * .25);
				if( trophies[1] == true )
				{
					button[i].Render();
				}
				break;
			case 9:
				//button[i].setLocation( sprite.position.x - 190, sprite.position.y + 50 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .396, sprite.position.y + IwGxGetScreenHeight() * .156);
				if( trophies[2] == true )
				{
					button[i].Render();
				}
				break;
			case 10:
				//button[i].setLocation( sprite.position.x + 12, sprite.position.y + 63 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .025, sprite.position.y + IwGxGetScreenHeight() * .197);
				if( trophies[3] == true )
				{
					button[i].Render();
				}
				break;
			case 11:
				//button[i].setLocation( sprite.position.x + 187, sprite.position.y + 45 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .390, sprite.position.y + IwGxGetScreenHeight() * .141);
				if( trophies[4] == true )
				{
					button[i].Render();
				}
				break;
			}
		}

		// need to render the current images because fonts are automatically displayed underneath them.
		IwGxFlush();

		// the high score
		CIwGxFontPreparedData scoreData;
		char scoreChar[100] = "";
		std::ostringstream scoreStringStream;
		scoreStringStream << highScore;
		string scoreString = scoreStringStream.str();
		strcat( scoreChar, scoreString.c_str() );
		

		// draw the shadow
		//IwGxFontSetCol(0xffaaffff);
		IwGxFontSetCol(0xff330000);
		//IwGxFontSetRect( CIwRect( sprite.position.x - (scoreString.length()/2 * 10), sprite.position.y - 100, 500, 300 ) ); // major glitch here. the size of score affects size of time. vice versa
		IwGxFontSetRect( CIwRect( sprite.position.x - (scoreString.length()/2 * 10), sprite.position.y - IwGxGetScreenHeight() * .312, 500, 300 ) ); // major glitch here. the size of score affects size of time. vice versa
		IwGxFontPrepareText( scoreData, scoreChar );
		IwGxFontDrawText( scoreData );

		// draw the text
		IwGxFontSetCol(0xff66ffff);
		//IwGxFontSetRect( CIwRect( sprite.position.x - (scoreString.length()/2 * 10) - 1, sprite.position.y - 100 - 2, 500, 300 ) ); // major glitch here. the size of score affects size of time. vice versa
		IwGxFontSetRect( CIwRect( sprite.position.x - (scoreString.length()/2 * 10) - IwGxGetScreenWidth()*.002, sprite.position.y - IwGxGetScreenHeight() * .319, 500, 300 ) ); // major glitch here. the size of score affects size of time. vice versa
		IwGxFontPrepareText( scoreData, scoreChar );
		IwGxFontDrawText( scoreData );

		// the time played
		// the high score
		CIwGxFontPreparedData timeData;
		char timeChar[100] = "";
		std::ostringstream timeStringStream;
		timeStringStream << timeHours << " hours  " << timeMinutes << " minutes  " << timeSeconds << " seconds";
		string timeString = timeStringStream.str();
		strcat( timeChar, timeString.c_str() );
		


		// draw the shadow
		//IwGxFontSetCol(0xffaaffff);
		IwGxFontSetCol(0xff330000);	
		//IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 10), sprite.position.y - 15, 400, 300 ) );
		if( IwGxGetScreenHeight() >= 640 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 20), sprite.position.y - IwGxGetScreenHeight() * .047, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		else if( IwGxGetScreenHeight() >= 480 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 15), sprite.position.y - IwGxGetScreenHeight() * .047, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		else //if( IwGxGetScreenHeight() >= 320 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 10), sprite.position.y - IwGxGetScreenHeight() * .047, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		IwGxFontPrepareText( timeData, timeChar );
		IwGxFontDrawText( timeData );


		// draw the text
		IwGxFontSetCol(0xff66ffff);	
		//IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 10) - 1, sprite.position.y - 15 - 2, 400, 300 ) );
		if( IwGxGetScreenHeight() >= 640 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 20) - IwGxGetScreenWidth()*.002, sprite.position.y - IwGxGetScreenHeight() * .053, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		else if( IwGxGetScreenHeight() >= 480 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 15) - IwGxGetScreenWidth()*.002, sprite.position.y - IwGxGetScreenHeight() * .053, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		else //if( IwGxGetScreenHeight() >= 320 )
		{
			IwGxFontSetRect( CIwRect( sprite.position.x - (timeString.length()/2 * 10) - IwGxGetScreenWidth()*.002, sprite.position.y - IwGxGetScreenHeight() * .053, IwGxGetScreenWidth(), IwGxGetScreenHeight() ) );
		}
		IwGxFontPrepareText( timeData, timeChar );
		IwGxFontDrawText( timeData );
	}
	else if( type == CREDITS )
	{
		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0:
				//button[i].setLocation( sprite.position.x - 75, sprite.position.y + 122 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .156, sprite.position.y + IwGxGetScreenHeight() * .381 );
				break;
			case 1:
				//button[i].setLocation( sprite.position.x + 15, sprite.position.y + 122 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .031, sprite.position.y + IwGxGetScreenHeight() * .381 );
				button[i].Render(); // only render back button
				break;
			}
		}
	}
	else if( type == TUTORIAL )
	{
		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0: // the back button
				//button[i].setLocation( sprite.position.x + 180, sprite.position.y + 122 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .375, sprite.position.y + IwGxGetScreenHeight() * .381);
				break;
			case 1:
				//button[i].setLocation( sprite.position.x - 60, sprite.position.y + 125 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .390 );
				break;
			case 2:
				//button[i].setLocation( sprite.position.x + 0, sprite.position.y + 125 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * 0, sprite.position.y + IwGxGetScreenHeight() * .390);
				break;
			case 3:
				//button[i].setLocation( sprite.position.x + 60, sprite.position.y + 125 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .390);
				break;
			}
			
			button[i].Render();
		}
	}
	else if( type == QUIT_CONFIRMATION )
	{
		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0: // the back button
				//button[i].setLocation( sprite.position.x - 60, sprite.position.y + 45 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .140 );
				break;
			case 1:
				//button[i].setLocation( sprite.position.x + 60, sprite.position.y + 45 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .140 );
				break;
			}
			
			button[i].Render();
		}
	}
	else if( type == NEW_STORY_CONFIRMATION )
	{
		for( int i = 0; i < buttonCount; i++ )
		{
			switch( i )
			{
			case 0: // the back button
				//button[i].setLocation( sprite.position.x - 60, sprite.position.y + 50 );
				button[i].setLocation( sprite.position.x - IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .156 );
				break;
			case 1:
				//button[i].setLocation( sprite.position.x + 60, sprite.position.y + 50 );
				button[i].setLocation( sprite.position.x + IwGxGetScreenWidth() * .125, sprite.position.y + IwGxGetScreenHeight() * .156 );
				break;
			}
			
			button[i].Render();
		}
	}

}

void MenuScreen::setStartingPosition( int16 x, int16 y )
{
	sprite.setStartingPosition( x, y );
}

void MenuScreen::setEndingPosition( int16 x, int16 y )
{
	sprite.setEndingPosition( x, y );
}

void MenuScreen::setInterpolationTime( uint64 t )
{
	sprite.setInterpolationTime( t );
}

void MenuScreen::setAcceleration( int16 accelLimit, int16 a )
{
	
	sprite.setAcceleration( accelLimit, a );
}

void MenuScreen::setDeceleration( int16 decelLimit, int16 a )
{
	sprite.setDeceleration( decelLimit, a );
}