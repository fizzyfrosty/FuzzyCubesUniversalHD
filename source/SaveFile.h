#pragma once
#include "IwGx.h"
#include <string>

using std::string;

class SaveFile
{
public:
	SaveFile(void);
	~SaveFile(void);
	
	/*void saveVersion( float version, bool p, long s, long highScore, 
		int n, int l, int t, bool trophies[], 
		int timeSeconds, int timeMinutes, int timeHours);
		*/

	void print();

	//float version;
	//bool playingStory;
	//long score;
	//int numOfLives;
	//int livesGained;
	//int targetEpisode;
	//long highScore;

	//int timeSeconds;
	//int timeMinutes;
	//int timeHours;

	//const static int NUM_OF_TROPHIES = 5;
	//bool trophies[NUM_OF_TROPHIES];

	int versionNumber;
	static const int NUM_OF_VARIABLES = 1000;
	int integers[NUM_OF_VARIABLES];	
	float floats[NUM_OF_VARIABLES];
	long longs[NUM_OF_VARIABLES];
	bool booleans[NUM_OF_VARIABLES];

	// Version 1.0
	// integers
	enum{ numOfLives,
		targetEpisode,
		timeSeconds,
		timeMinutes,
		timeHours,
		newValue1,
		newValue2,
		newValue3,
		newValue4,
		fuzzyFactCounter,
	};
	// longs
	enum{ score,
		highScore,
		scoreLivesBonusBucket};
	// bools
	enum{ trophy00,
		trophy01,
		trophy02,
		trophy03,
		trophy04,
		playingStory,
		playedHowToTutorialOnce,
		playedBombTutorialOnce,
		playedWarningTutorialOnce,
		startAtCheckpoint,
	};
	
};

