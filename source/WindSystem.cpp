#include "WindSystem.h"


WindSystem::WindSystem(void)
{
}


WindSystem::~WindSystem(void)
{
}

void WindSystem::Initialize( int16 s )
{
	IwRandSeed( (int32)s3eTimerGetMs() );
	for( int i = 0; i < NUM_OF_WINDSTREAKS; i++ )
	{
		windStreaks[i].Initialize( s );
	}
}

void WindSystem::Terminate()
{
	for( int i = 0; i < NUM_OF_WINDSTREAKS; i++ )
	{
		windStreaks[i].Terminate();
	}
}

void WindSystem::Update( CIwMat modelMatrix )
{
	for( int i = 0; i < NUM_OF_WINDSTREAKS; i++ )
	{
		windStreaks[i].Update( modelMatrix );
	}
}

void WindSystem::Render()
{
	for( int i = 0; i < NUM_OF_WINDSTREAKS; i++ )
	{
		windStreaks[i].Render();
	}
}