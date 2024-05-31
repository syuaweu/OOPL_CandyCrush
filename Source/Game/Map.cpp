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
		vector<Candy> x;
		vector<Ice> y;
		for (int j = 0; j < 9; j++) {
			Candy c;
			Ice ic;
			x.push_back(c);
			y.push_back(ic);
		}
		this->_candy_map.push_back(x);
		this->_ice_map.push_back(y);
	}
}

int Map::width(){
	return _width;
}
int Map::height(){
	return _height;
}

void Map::loadCandyMap() {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	in.open("Resources/map/" + to_string(map_name) + ".txt");
	int r, c;
	in >> r >> c;
	this->_width = c;
	this->_height = r;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int x = 0;
			in >> x;
			_candy_map[i][j]._type = x;
		}
	}
	in.close();
	updateCandyMap();
}

void Map::loadIceMap() {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	in.open("Resources/map/" + to_string(map_name) + ".txt");
	int r, c;
	in >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int x = 0;
			in >> x;
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int x = 0;
			in >> x;
			_ice_map[i][j]._layer = x;
		}
	}
	in.close();
	updateIceMap();
}

void  Map::updateCandyMap() {

	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			_candy_map[i][j]._position.first = (400 - 25 * width()) + j * 50;
			_candy_map[i][j]._position.second = (400 - 25 * height()) + i * 50;
			_candy_map[i][j].updateCandy();
		}
	}
}

void  Map::updateIceMap() {

	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			_ice_map[i][j]._position.first = (400 - 25 * width()) + j * 50;
			_ice_map[i][j]._position.second = (400 - 25 * height()) + i * 50;
			_ice_map[i][j].updateIce();
		}
	}
}

//void Map::fallCandy() {
//	if (this->i() == 0 && this->j() == 0) {
//		this->_position.first = this->candy.GetLeft();
//		this->_position.second = this->candy.GetTop() + 50;
//			
//	}
//	if (this->i() == 0) { //potential bug (fall candy probably not start from i=0)
//		return;
//	}
//	if (this->_map[this->i() - 1][this->j()] >= 0) {
//		fallCandy(this->i() - 1, this->j());
//		// TRACE("%d %d", i - 1, j);
//		return;
//	}
//	else if (this->j() >= 0) {
//		if (this->_map[this->i() - 1][this->j() - 1] >= 0) {
//			fallCandy(this->i() - 1, this->j() - 1);
//			// TRACE("%d %d", i - 1, j - 1);
//			return;
//		}
//	}
//	else if (j <= this->width() - 1) {
//		if (this->_map[this->i() - 1][this->j() + 1] >= 0) {
//			fallCandy(this->i() - 1, this->j() + 1);
//			// TRACE("%d %d", i - 1, j + 1);
//			return;
//		}
//	}
//}