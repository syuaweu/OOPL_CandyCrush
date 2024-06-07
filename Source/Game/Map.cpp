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
			candy.Init();
			ice.Init();
			temp_candy_row.push_back(candy);
			temp_ice_row.push_back(ice);
		}
		this->_candy_map.push_back(temp_candy_row);
		this->_ice_map.push_back(temp_ice_row);
	}
	_is_animation_finished = true;
	_is_fall_candy = false;
	idx0 = 0, idx1 = 0;
	idy0 = 0, idy1 = 0;
}

void Map::BeginState(){
	loadLevel();
	loadMapWidthAndHeight();
	loadCandyMap();
	loadIceMap();
}

void Map::Show() {
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			_ice_map[i][j].ice().ShowBitmap();
			_candy_map[i][j].candy().ShowBitmap();
		}
	}
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
	in.open("Resources/init_map/choose_level.txt"); //"Resources/init_map/choose_level.txt"
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
			_candy_map[i][j]._type = x;
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

void Map::updateMap() {
	updateCandyMap();
	updateIceMap();
}

void Map::fallCandyAll() {
	for (int j = 0; j < width(); j++) { // status2: fall one layer
		for (int i = 0; i < height(); i++)
		{
			if (_candy_map[i][j].fall_status() == 1) {
				_is_fall_candy = true;
				fallCandy(i, j);
				removeObstacle(i, j);
				removeAroundObstacle(i, j);
			}
			if (_candy_map[i][j].fall_status() == 2) {
				_is_fall_candy = true;
				removeObstacle(i, j);
			}
			if (_is_fall_candy == true) {
				updateMap();
				return;
			}
		}
		if (_is_fall_candy == true) {
			updateMap();
			return;
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
void Map::produceCandy(int i, int j) {
	int min = 0;
	int max = 3;
	int x = rand() % (max - min + 1) + min;
	_candy_map[i][j]._type = x;
}

void Map::fallCandy(int i, int j) {
	if (i == 0) { // probably fail (if i=0 )
		produceCandy(i, j);
		return;
	}
	if (_candy_map[i - 1][j].can_dropped()) {
		_candy_map[i][j]._type = _candy_map[i - 1][j].type();
		fallCandy(i - 1, j);
		return;
	}
	if (j > 0) {
		if (_candy_map[i - 1][j - 1].can_dropped()) {
			_candy_map[i][j]._type = _candy_map[i - 1][j - 1].type();
			fallCandy(i - 1, j - 1);
			return;
		}
	}
	if (j <= width() - 1) {
		if (_candy_map[i - 1][j + 1].can_dropped()) {
			_candy_map[i][j]._type = _candy_map[i - 1][j + 1].type();
			fallCandy(i - 1, j + 1);
			return;
		}
	}
	_candy_map[i][j]._type = -10;
}

void Map::removeObstacle(int i, int j) {
	if (_ice_map[i][j].isIce() != 0) {
		_ice_map[i][j]._layer -= 1;
		//score += 1000;
	}
	if (_candy_map[i][j].is_frosting()) {
		_candy_map[i][j]._type += 1;
	}
	if (!_candy_map[i][j].is_frosting()) {
		fallCandy(i, j);
	}
}

void Map::removeAroundObstacle(int i, int j) {
	if (_ice_map[i][j].isIce() != 0) {
		_ice_map[i][j]._layer -= 1;
		//score += 1000;
	}
	if (i > 0) {
		if (_candy_map[i - 1][j].type() > -15 && _candy_map[i - 1][j].type() < 0 && _candy_map[i - 1][j].type() != -10 && _candy_map[i - 1][j].type() != 99) {
			_candy_map[i - 1][j]._type += 1;
		}
	}
	if (j > 0) {
		if (_candy_map[i][j - 1].type() > -15 && _candy_map[i][j - 1].type() < 0 && _candy_map[i][j - 1].type() != -10 && _candy_map[i][j - 1].type() != 99) {
			_candy_map[i][j - 1]._type += 1;
		}
	}
	if (i < height() - 1) {
		if (_candy_map[i + 1][j].type() > -15 && _candy_map[i + 1][j].type() < 0 && _candy_map[i + 1][j].type() != -10 && _candy_map[i + 1][j].type() != 99) {
			_candy_map[i + 1][j]._type += 1;
		}
	}
	if (j < width() - 1) {
		if (_candy_map[i][j + 1].type() > -15 && _candy_map[i][j + 1].type() < 0 && _candy_map[i][j + 1].type() != -10 && _candy_map[i][j + 1].type() != 99) {
			_candy_map[i][j + 1]._type += 1;
		}
	}
}

bool Map::is_LTypeCandy(int i, int j) {
	if (i < 0 || j < 0) {
		return false;
	}
	if (j >= 2 && i < height() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 2][j])) {
			return true;
		}
	}
	if (j < width() - 2 && i < height() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 2])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 2][j])) {
			return true;
		}
	}
	if (j >= 2 && i >= 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])) {
			return true;
		}
	}
	if (j < width() - 2 && i >= 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 2])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])) {
			return true;
		}
	}
	return false;
}

bool Map::is_ITypeCandy(int i, int j) {
	if (i < 0 || j < 0) {
		return false;
	}
	if (i >= 2 && i < height() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])) {
			return true;
		}
	}
	if (i >= 1 && i < height() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 2][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])) {
			return true;
		}
	}
	return false;
}

bool Map::is_TTypeCandy(int i, int j) {
	if (i < 0 || j < 0) {
		return false;
	}
	if (j < width() - 2 && i >= 1 && i < height() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 2])) {
			return true;
		}
	}
	if (j >= 2 && i >= 1 && i < height() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])) {
			return true;
		}
	}
	if (i >= 2 && j >= 1 && j < width() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])) {
			return true;
		}
	}
	if (i < height() - 2 && j >= 1 && j < width() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 2][j])) {
			return true;
		}
	}
	return false;
}

bool Map::is_ETypeCandy(int i, int j) {
	if (i < 0 || j < 0) {
		return false;
	}
	if (j > 0 && j < width() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 2])) {
			return true;
		}

	}
	if (j > 1 && j < width() - 1) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])) {
			return true;
		}
	}
	return false;
}

bool Map::is_ChocoCandy(int i, int j) {
	if (i < 0 || j < 0) {
		return false;
	}
	if (i >= 2 && i < height() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 1][j])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i + 2][j])) {
			return true;
		}
	}
	if (j >= 2 && j < width() - 2) {
		if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 1])
			&& _candy_map[i][j].is_sameColor_candy(_candy_map[i][j + 2])) {
			return true;
		}
	}
	return false;
}

void Map::deleteRow(int i, int j) {
	if (i >= height() || i < 0) {
		return;
	}
	for (int jj = j; jj >=0; jj--) {
		if (_candy_map[i][jj].type() == -1) {
			_candy_map[i][jj]._fall_status = 2;
			break;
		}
		_candy_map[i][jj]._fall_status = 2;
	}
	for (int jj = j; jj < width(); jj++) {
		if (_candy_map[i][jj].type() == -1) {
			_candy_map[i][jj]._fall_status = 2;
			break;
		}
		_candy_map[i][jj]._fall_status = 2;
	}
}

void Map::deleteColumn(int i, int j) {
	if (j >= width() || j < 0) {
		return;
	}
	for (int ii = i; i >= 0; i--) {
		if (_candy_map[ii][j].type() == -1) {
			_candy_map[ii][j]._fall_status = 2;
			break;
		}
		_candy_map[ii][j]._fall_status = 2;
	}
	for (int ii = i; ii < height(); ii++) {
		if (_candy_map[ii][j].type() == -1) {
			_candy_map[ii][j]._fall_status = 2;
			break;
		}
		_candy_map[ii][j]._fall_status = 2;
	}
}

bool Map::can_change_candy() {
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			if (_candy_map[i][j].type() == 99 || _candy_map[i][j].type() == -10) {
				return true;
			}
			if (_candy_map[i][j].type() < 0) {
			}
			else {
				if (i >= 2) {
					if (_candy_map[i][j].type() % 10 == _candy_map[i - 1][j].type() % 10 && _candy_map[i][j].type() % 10 == _candy_map[i - 2][j].type() % 10) {
						return true;
					}
				}
				if (j >= 2) {
					if (_candy_map[i][j].type() % 10 == _candy_map[i][j - 1].type() % 10 && _candy_map[i][j].type() % 10 == _candy_map[i][j - 2].type() % 10) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Map::Switch(int i1, int j1, int i2, int j2) {
	Candy xx = _candy_map[i1][j1];
	_candy_map[i1][j1] = _candy_map[i2][j2];
	_candy_map[i2][j2] = xx;
}

bool Map::can_switch_then_switch() {
	int row0 = (idy0 - (400 - 25 * height())) / 50;
	int column0 = (idx0 - (400 - 25 * width())) / 50;
	int row1 = (idy1 - (400 - 25 * height())) / 50;
	int column1 = (idx1 - (400 - 25 * width())) / 50;
	if (!(std::abs(row0 - row1) == 1 && std::abs(column0 - column1) == 0) && !(std::abs(row0 - row1) == 0 && std::abs(column0 - column1) == 1)) {
		return false;
	}
	if (_candy_map[row0][column0].type() < -10 || _candy_map[row1][column1].type() < -10) {
		return false;
	}
	Switch(row0, column0, row1, column1);
	if (_candy_map[row0][column0].type() >= 10 && _candy_map[row1][column1].type() >= 10) {
		return true;
	}
	if (_candy_map[row0][column0].type() == 7 || _candy_map[row1][column1].type() == 7) {
		updateCandyMap();
		return true;
	}
	if (can_change_candy()) {
		updateCandyMap();
		return true;
	}
	Switch(row0, column0, row1, column1);
	return false;
}

bool Map::is_inSquare() {
	int potx = (400 - 25 * width());
	int poty = (400 - 25 * height());
	if (idx0 < potx || idx1 < potx) {
		return 0;
	}
	if (idx0 > potx + 50 * width() || idx1 > potx + 50 * width()) {
		return 0;
	}
	if (idy0 < poty || idy1 < poty) {
		return 0;
	}
	if (idy0 > poty + 50 * height() || idy1 > poty + 50 * height()) {
		return 0;
	}
	return 1;
}

void Map::checkMapStatus() { // 1:normal, 0.2:special
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			if (_candy_map[i][j].type() == -10 || _candy_map[i][j].type() == 99) {
				_candy_map[i][j]._fall_status = 2;
			}
			else if (_candy_map[i][j].type() < 0) {
			}
			else {
				/*if (_candy_map[i][j].type() / 10 == 6) {
					disapear = 1;
					boom_que.push_back({ 1, {i,j} });
				}*/
				if (i >= 2) {
					if (_candy_map[i][j].is_sameColor_candy(_candy_map[i - 1][j]) && _candy_map[i][j].is_sameColor_candy(_candy_map[i - 2][j])) {
						_candy_map[i][j]._fall_status = 1;
						_candy_map[i - 1][j]._fall_status = 1;
						_candy_map[i - 2][j]._fall_status = 1;
						/*for (int k = i - 2; k <= i; k++) {
							if (which_candy[k][j] / 10 == 2) {
								status = delete_row(status, k);
								score += 500;
							}
							if (which_candy[k][j] / 10 == 3) {
								status = delete_column(status, j);
								score += 500;
							}
							if (which_candy[k][j] / 10 == 1) {
								disapear = 1;
								boom_que.push_back({ 2, {k,j} });
							}

						}*/
					}
				}
				if (j >= 2) {
					if (_candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 1]) && _candy_map[i][j].is_sameColor_candy(_candy_map[i][j - 2])) {
						_candy_map[i][j]._fall_status = 0;
						_candy_map[i][j - 1]._fall_status = 0;
						_candy_map[i][j - 2]._fall_status = 0;
						/*for (int k = j - 2; k <= j; k++) {
							if (which_candy[i][k] / 10 == 2) {
								status = delete_row(status, i);
							}
							if (which_candy[i][k] / 10 == 3) {
								status = delete_column(status, k);
							}
							if (which_candy[i][k] / 10 == 1) {
								disapear = 1;
								boom_que.push_back({ 2, {i,k} });
							}
						}*/

					}
				}
			}
		}
	}
	/*TRACE("wryyyyy %d\n", boom_que.size());*/
	//for (auto i : boom_que) {
	//	status = boom(status, i.second.first, i.second.second, i.first);
	//	score += 1000;
	//	if (i.first == 2) {
	//		status[i.second.first][i.second.second] = 1;
	//		which_candy[i.second.first][i.second.second] %= 10;
	//		which_candy[i.second.first][i.second.second] += 60;
	//		update_candy();
	//		disapear = 1;
	//	}
	//}
	//boom_que.clear();
	//int i0 = (idy0 - (400 - 25 * h)) / 50;
	//int j0 = (idx0 - (400 - 25 * w)) / 50;
	//int i1 = (idy1 - (400 - 25 * h)) / 50;
	//int j1 = (idx1 - (400 - 25 * w)) / 50;
	///*TRACE("\n0: %d %d\n1:%d %d\n", i0, j0, i1, j1);*/
	//if (i0 >= 0 && i0 < h
	//	&&i1 >= 0 && i1 < h
	//	&&j0 >= 0 && j0 < w
	//	&&j1 >= 0 && j1 < w
	//	&& (i0 != i1 || j0 != j1)) {
	//	if ((which_candy[i0][j0] / 10 == 2 || which_candy[i0][j0] / 10 == 3) &&
	//		(which_candy[i1][j1] / 10 == 2 || which_candy[i1][j1] / 10 == 3)) {
	//		disapear = 1;
	//		status = delete_row(status, i1);
	//		status = delete_column(status, j1);
	//		return status;
	//	}
	//	else if (((which_candy[i0][j0] / 10 == 2 || which_candy[i0][j0] / 10 == 3) && which_candy[i1][j1] / 10 == 1) ||
	//		((which_candy[i1][j1] / 10 == 2 || which_candy[i1][j1] / 10 == 3) && which_candy[i0][j0] / 10 == 1)) {
	//		disapear = 1;
	//		status = delete_row(status, i1);
	//		status = delete_column(status, j1);
	//		status = delete_row(status, i1 - 1);
	//		status = delete_column(status, j1 - 1);
	//		status = delete_row(status, i1 + 1);
	//		status = delete_column(status, j1 + 1);
	//		return status;
	//	}
	//	else if (which_candy[i0][j0] == 7) {
	//		disapear = 1;
	//		score += 5000;
	//		if (which_candy[i1][j1] < 7 && which_candy[i1][j1] >= 0) {
	//			status[i0][j0] = 0;
	//			int x = which_candy[i1][j1];
	//			for (int i = 0; i < h; i++) {
	//				for (int j = 0; j < w; j++) {
	//					if (which_candy[i][j] % 10 == x) {
	//						status[i][j] = 0;
	//					}
	//				}
	//			}
	//		}
	//		else {

	//		}
	//		return status;
	//	}
	//	else if (which_candy[i1][j1] == 7) {
	//		disapear = 1;
	//		score += 5000;
	//		if (which_candy[i0][j0] < 7 && which_candy[i0][j0] >= 0) {
	//			status[i1][j1] = 0;
	//			int x = which_candy[i0][j0];
	//			for (int i = 0; i < h; i++) {
	//				for (int j = 0; j < w; j++) {
	//					if (which_candy[i][j] % 10 == x) {
	//						status[i][j] = 0;
	//					}
	//				}
	//			}
	//		}
	//		else {

	//		}
	//		return status;
	//	}
	//	for (int i = 0; i < 2; i++) {
	//		int ii = (idy0 - (400 - 25 * h)) / 50;
	//		int jj = (idx0 - (400 - 25 * w)) / 50;
	//		if (i == 1) {
	//			ii = (idy1 - (400 - 25 * h)) / 50;
	//			jj = (idx1 - (400 - 25 * w)) / 50;
	//		}

	//		if (ChocoCandy(mp, ii, jj)) {
	//			status[ii][jj] = 1;

	//			which_candy[ii][jj] = 7;
	//			update_candy();
	//			disapear = 1;
	//			return status;
	//		}
	//		if (LTypeCandy(mp, ii, jj) || TTypeCandy(mp, ii, jj)) {
	//			status[ii][jj] = 1;
	//			which_candy[ii][jj] %= 10;
	//			which_candy[ii][jj] += 10;
	//			disapear = 1;
	//			update_candy();
	//			return status;
	//		}
	//		if (ETypeCandy(mp, ii, jj)) {
	//			status[ii][jj] = 1;
	//			which_candy[ii][jj] %= 10;
	//			which_candy[ii][jj] += 30;
	//			update_candy();
	//			disapear = 1;
	//			return status;
	//		}
	//		if (ITypeCandy(mp, ii, jj)) {
	//			TRACE("AAAAAAAAA %d %d: %d", ii, jj, ITypeCandy(mp, ii, jj));
	//			status[ii][jj] = 1;
	//			which_candy[ii][jj] %= 10;
	//			which_candy[ii][jj] += 20;
	//			disapear = 1;
	//			update_candy();
	//		}

	//	}
	//}




	/*
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (LTypeCandy(mp, i, j) || TTypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 10;
				disapear = 1;
				update_candy();
			}
			if (ITypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 20;
				disapear = 1;
				update_candy();
			}
			if (ETypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 30;
				disapear = 1;
				update_candy();
			}
		}
	}
	*/
}
