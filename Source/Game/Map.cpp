#include <stdafx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include<sstream>
#include<fstream>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Candy.h"
#include "Map.h"
#include"Ice.h"

Map::Map() {
	
}

void Map::Init() {
	for (int i = 0; i < 9; i++) {
		vector<Candy> temp_candy_row;
		vector<Ice> temp_ice_row;
		for (int j = 0; j < 9; j++) {
			Candy candy;
			Ice ice;
			temp_candy_row.push_back(candy);
			temp_ice_row.push_back(ice);
		}
		this->_candy_map.push_back(temp_candy_row);
		this->_ice_map.push_back(temp_ice_row);
	}
	_is_animation_finished = true;
	_is_fall_candy = false;
}

void Map::BeginState(){
	loadLevel();
	loadMapWidthAndHeight();
	loadCandyMap();
	loadIceMap();
}

int Map::level() {
	return _level;
}

int Map::width(){
	return _width;
}

int Map::height(){
	return _height;
}

void Map::loadLevel() {
	ifstream in;
	in.open("Resources/init_map/choose_level.txt");
	in >> this->_level;
	in.close();
}

void Map::loadMapWidthAndHeight() {
	ifstream in;
	in.open("Resources/init_map/" + to_string(level()) + ".txt");
	in >> this->_height >> this->_width;
	in.close();
}

void Map::loadCandyMap() {
	ifstream in;
	in.open("Resources/candy_maps/" + to_string(level()) + ".txt");
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			int x = 0;
			in >> x;
			_ice_map[i][j]._layer = x;
		}
	}
	in.close();
	updateCandyMap();
}

void Map::loadIceMap() {
	ifstream in;
	in.open("Resources/ice_maps/" + to_string(level()) + ".txt");
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			int x = 0;
			in >> x;
			_ice_map[i][j]._layer = x;
		}
	}
	in.close();
	updateIceMap();
}

void Map::updateCandyMap() {
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			_candy_map[i][j]._position.first = (400 - 25 * width()) + j * 50;
			_candy_map[i][j]._position.second = (400 - 25 * height()) + i * 50;
			_candy_map[i][j].updateCandy();
		}
	}
}

void Map::updateIceMap() {
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			_ice_map[i][j]._position.first = (400 - 25 * width()) + j * 50;
			_ice_map[i][j]._position.second = (400 - 25 * height()) + i * 50;
			_ice_map[i][j].updateIce();
		}
	}
}

void Map::fallCandyAll() {
	for (int j = 0; j < width(); j++) { // status2: fall one layer
		for (int i = 0; i < height(); i++) {
			if (_candy_map[i][j].is_fall() && !_candy_map[i][j].is_remove_obstacle()) {
				_is_fall_candy = true;
				startCandyAnimation(i, j, 0);
				fallCandy(i, j, 0);
			}
		}
	}
}

void Map::startCandyAnimation(int i, int j, int direction) {
	if (_candy_map[i][j].i() == 0 && _candy_map[i][j].j() == 0) {
		_is_animation_finished = 0;
	}
	_candy_map[i][j]._index.first = direction;
	_candy_map[i][j]._index.second = _candy_map[i][j].candy().GetTop() + 50;
	if (i == 0) { //potential bug (fall candy probably not start from i=0)
		return;
	}
	if (_candy_map[i - 1][j].type() >= -5 || _candy_map[i - 1][j].type() == -10) {
		startCandyAnimation(i - 1, j, 0);
		return;
	}
	if (j > 0) {
		if (_candy_map[i - 1][j - 1].type() >= -5) {
			startCandyAnimation(i - 1, j - 1, -1);
			return;
		}
	}
	if (j <= width() - 1) {
		if (_candy_map[i - 1][j + 1].type() >= -5) {
			startCandyAnimation(i - 1, j + 1, 1);
			return;
		}
	}
}

void Map::fallCandy(int i, int j, int direction) {

}