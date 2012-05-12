#include "s3e.h"
#include "IwGx.h"
#include "math.h"
//#include "s3eIOSBackgroundMusic.h"
//#include "IwUI.h"
#include "Cube.h"
#include "IwRandom.h"
#include <vector>
#include "Shadow.h"
#include "ShadowGroup.h"
#include "TouchButton.h"
#include "Iw2D.h"
#include "PlaneSide.h"
#include "BackgroundObject.h"
#include "Sprite.h"
#include "MenuCube.h"
#include "FloatingObject.h"
#include "ActiveSquare.h"
#include "Fuzzy3D.h"
#include "PointSprite.h"
#include "MenuScreen.h"
#include "TransitionObject.h"
#include "WindSystem.h"
#include "SaveFile.h"

#include "IwGraphics.h"
#include "IwModel.h"
#include "IwModelBuilder.h"
#include "IwResManager.h"
#include "Iw2D.h"
#include "IwModelExt.h"
#include "s3eIOSIAd.h"
#include "s3eSocket.h"
#include "s3eExt_OSExec.h"
#include "s3eFlurry.h"
//#include "s3eAdWhirl.h"

#include "IwGxFont.h"
#include <sstream>
#include <iostream>
#include <string>

using std::string;
using std::vector;

#pragma once
class FuzzyCubes
{
public:
	FuzzyCubes(void);
	~FuzzyCubes(void);
};

