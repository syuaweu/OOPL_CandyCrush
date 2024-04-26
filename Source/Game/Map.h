#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stdafx.h"
#include "mygame.h"
#include "Candy.h"

class Map {
private:
	int _width;
	int _height;
	Candy *_map[9][9];
	bool _is_animation_finished;

public:
	Map() {

	}

	Map(int width, int h)
		: _width(width), _height(height) {
		_is_animation_finished = 0;
	}
	int width() const {
		return _width;
	}
	int height() const {
		return _height;
	}
	void fallCandy() {
		if (this->i() == 0 && this->j() == 0) {
			this->_position.first = this->candy.GetLeft();
			this->_position.second = this->candy.GetTop() + 50;
			
		}
		if (this->i() == 0) { //potential bug (fall candy probably not start from i=0)
			return;
		}
		if (this->_map[this->i() - 1][this->j()] >= 0) {
			fallCandy(this->i() - 1, this->j());
			// TRACE("%d %d", i - 1, j);
			return;
		}
		else if (this->j() >= 0) {
			if (this->_map[this->i() - 1][this->j() - 1] >= 0) {
				fallCandy(this->i() - 1, this->j() - 1);
				// TRACE("%d %d", i - 1, j - 1);
				return;
			}
		}
		else if (j <= this->width() - 1) {
			if (this->_map[this->i() - 1][this->j() + 1] >= 0) {
				fallCandy(this->i() - 1, this->j() + 1);
				// TRACE("%d %d", i - 1, j + 1);
				return;
			}
		}
	}
};