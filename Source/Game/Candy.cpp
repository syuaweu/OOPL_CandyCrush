#include "stdafx.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Candy.h"

using namespace game_framework;

Candy::Candy() {

}

void Candy::Init() {
	_type = 0;
	_candy.LoadBitmapByString({
		"Resources/texture_pack_original/candy/0.bmp",
		"Resources/texture_pack_original/candy/1.bmp",
		"Resources/texture_pack_original/candy/2.bmp",
		"Resources/texture_pack_original/candy/3.bmp",
		"Resources/texture_pack_original/candy/4.bmp",
		"Resources/texture_pack_original/candy/5.bmp",
		"Resources/texture_pack_original/candy/10.bmp",
		"Resources/texture_pack_original/candy/11.bmp",
		"Resources/texture_pack_original/candy/12.bmp",
		"Resources/texture_pack_original/candy/13.bmp",
		"Resources/texture_pack_original/candy/14.bmp",
		"Resources/texture_pack_original/candy/15.bmp",
		"Resources/texture_pack_original/candy/20.bmp",
		"Resources/texture_pack_original/candy/21.bmp",
		"Resources/texture_pack_original/candy/22.bmp",
		"Resources/texture_pack_original/candy/23.bmp",
		"Resources/texture_pack_original/candy/24.bmp",
		"Resources/texture_pack_original/candy/25.bmp",
		"Resources/texture_pack_original/candy/30.bmp",
		"Resources/texture_pack_original/candy/31.bmp",
		"Resources/texture_pack_original/candy/32.bmp",
		"Resources/texture_pack_original/candy/33.bmp",
		"Resources/texture_pack_original/candy/34.bmp",
		"Resources/texture_pack_original/candy/35.bmp",
		"Resources/texture_pack_original/candy/40.bmp",
		"Resources/texture_pack_original/candy/50.bmp",
		"Resources/texture_pack_original/candy/-1.bmp",
		"Resources/texture_pack_original/candy/-10.bmp",
		"Resources/texture_pack_original/candy/-11.bmp",
		"Resources/texture_pack_original/candy/-12.bmp",
		"Resources/texture_pack_original/candy/-13.bmp",
		"Resources/texture_pack_original/candy/-99.bmp",
		"Resources/texture_pack_original/candy/99.bmp",
		"Resources/texture_pack_original/candy/999.bmp",
		"Resources/texture_pack_original/candy/7.bmp"});
	_candy.SetTopLeft(0, 0);
	_candy.SetFrameIndexOfBitmap(0);
	
	_index = {0, 0};
	_position = {0, 0};
}

CMovingBitmap Candy::candy(){
	return _candy;
}

int Candy::type(){
	return _type;
}

int Candy::i(){
	return _index.first;
}

int Candy::j(){
	return _index.second;
}

int Candy::x(){
	return _position.first;
}

int Candy::y(){
	return _position.second;
}

void Candy::updateCandy() {
	if (this->type() == -1) {
		this->_candy.SetFrameIndexOfBitmap(26);
	}
	else if (this->type() >= 60 && this->type() <= 65) {
		this->_candy.SetFrameIndexOfBitmap(this->type() % 10 + this->type() / 6 / 10 * 6);
	}
	else if (this->type() >= 60) {
		this->_candy.SetFrameIndexOfBitmap(32);
	}
	else if (this->type() <= -10) {
		this->_candy.SetFrameIndexOfBitmap(std::abs(this->type()) + 17);
	}
	else if (this->type() == 7) {
		this->_candy.SetFrameIndexOfBitmap(34);
	}
	else if (this->type() >= 0 && this->type() <= 35) {
		this->_candy.SetFrameIndexOfBitmap(this->type() / 10 * 6 + this->type() % 10);
	}
	else {
		this->_candy.SetFrameIndexOfBitmap(33);
	}
}
