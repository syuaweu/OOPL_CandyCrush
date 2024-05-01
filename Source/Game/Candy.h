#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stdafx.h"
#include "mygame.h"

class Candy {
protected:
	game_framework::CMovingBitmap _candy;
	int _type;
	pair<int, int> _index;
	pair<int, int> _position;

public:
	Candy() {

	}

	Candy(game_framework::CMovingBitmap candy, int type, pair<int, int> index, pair<int, int> position)
	: _candy(candy), _type(type), _index(index), _position(position){
	}

	game_framework::CMovingBitmap candy() const {
		return _candy;
	}

	int type() const {
		return _type;
	}

	int i() const {
		return _index.first;
	}

	int j() const {
		return _index.second;
	}

	int x() const {
		return _position.first;
	}

	int y() const {
		return _position.second;
	}

	void updateCandy() {
		if (this->type() == -1) {
			this->candy.SetFrameIndexOfBitmap(26);
		}
		else if (this->type() >= 60 && this->type() <= 65) {
			this->candy.SetFrameIndexOfBitmap(this->type() % 10 + this->type() / 6 / 10 * 6);
		}
		else if (this->type() >= 60) {
			this->candy.SetFrameIndexOfBitmap(32);
		}
		else if (this->type() <= -10) {
			this->candy.SetFrameIndexOfBitmap(std::abs(this->type()) + 17);
		}
		else if (this->type() == 7) {
			this->candy.SetFrameIndexOfBitmap(34);
		}
		else if (this->type() >= 0 && this->type() <= 35) {
			this->candy.SetFrameIndexOfBitmap(this->type() / 10 * 6 + this->type() % 10);
		}
		else {
			this->candy.SetFrameIndexOfBitmap(33);
		}
	}
};

