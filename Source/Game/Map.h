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
	int _width;
	int _height;
	vector<vector<Candy>> _candy_map;
	vector<vector<Ice>> _ice_map;
	bool _is_animation_finished;
	Map();
	int width();
	int height();
	void Init();
	void loadCandyMap();
	void loadIceMap();
	void updateCandyMap();
	void updateIceMap();
	// void fallCandy();
};