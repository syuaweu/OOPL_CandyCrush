#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Candy.h"

class Map {
private:
	int _width;
	int _height;
	Candy *_map[9][9];
	bool _is_animation_finished;


public:
	Map();
	int width();
	int height();
	// void fallCandy();
};