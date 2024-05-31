#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Candy.h"
#include"Ice.h"

class Map {
private:
	


public:
	int _level;
	int _width;
	int _height;
	vector<vector<Candy>> _candy_map;
	vector<vector<Ice>> _ice_map;
	bool _is_animation_finished;

	Map();
	int level();
	int width();
	int height();

	void OnInit();
	void OnBeginState();
	void loadLevel();
	void loadMapWidthAndHeight();
	void loadCandyMap();
	void loadIceMap();
	void updateCandyMap();
	void updateIceMap();
	// void fallCandy();
};