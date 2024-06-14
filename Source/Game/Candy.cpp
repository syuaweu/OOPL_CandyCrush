#include <stdafx.h>
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
		"Resources/texture_pack_original/candy/40.bmp", //24
		"Resources/texture_pack_original/candy/50.bmp",
		"Resources/texture_pack_original/candy/-1.bmp",
		"Resources/texture_pack_original/candy/-11.bmp",
		"Resources/texture_pack_original/candy/-12.bmp",
		"Resources/texture_pack_original/candy/-13.bmp",
		"Resources/texture_pack_original/candy/-21.bmp",
		"Resources/texture_pack_original/candy/99.bmp", //31
		"Resources/texture_pack_original/candy/-99.bmp",
		"Resources/texture_pack_original/candy/err.bmp" });
	_candy.SetTopLeft(0, 0);
	_candy.SetFrameIndexOfBitmap(0);
	_index = {0, 0};
	_position = {0, 0};
	_next_position = {0, 0};
	_fall_status = 0;
	_will_be_special_candy = 0;
	_is_animating = 0;
}

void Candy::BeginState() {
	_index = {0, 0};
	_next_position = {0, 0};
	_fall_status = 0;
	_is_animating = 0;
}

CMovingBitmap Candy::candy(){
	return _candy;
}

int Candy::type(){
	return _type;
}

int Candy::fall_status() {
	return _fall_status;
}

bool Candy::can_remove() {
	if (type() == -99) {
		return false;
	}
	return true;
}

bool Candy::is_fall() {
	if (fall_status()) {
		return true;
	}
	return false;
}

bool Candy::can_dropped() {
	if (is_frosting()) {
		return false;
	}
	if (type() == -99) {
		return false;
	}
	return true;
}


bool Candy::is_frosting() {
	if (-13 <= type() && type() <= -11) {
		return true;
	}
	return false;
}

bool Candy::is_spiral() {
	if (type() == -1) {
		return true;
	}
	return false;
}

bool Candy::is_obstacle() {
	if (is_frosting() || is_spiral()) {
		return true;
	}
	return false;
}

bool Candy::is_remove_obstacle() {
	if (fall_status() == 1) {
		return true;
	}
	return false;
}

bool Candy::will_be_special_candy() {
	return _will_be_special_candy;
}

bool Candy::is_animating() {
	return _is_animating;
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

int Candy::next_direction() {
	return _next_position.first;
}
int Candy::next_y() {
	return _next_position.second;
}

bool Candy::is_special_candy() {
	if (type() >= 10 && type() < 35) {
		return true;
	}
	return false;
}

void Candy::updateCandy() {
	_candy.SetTopLeft(x(), y());
	_candy.SetFrameIndexOfBitmap(5);
	
	if (type() == -1) {
		_candy.SetFrameIndexOfBitmap(26);
	}
	else if (-13 <= type() && type() <= -11) {
		_candy.SetFrameIndexOfBitmap(std::abs(type()) + 16);
	}
	else if (-21 == type()) {
		_candy.SetFrameIndexOfBitmap(30);
	}
	else if (type() == 7) {
		_candy.SetFrameIndexOfBitmap(24);
	}
	else if (type() >= 0 && type() <= 35) {
		_candy.SetFrameIndexOfBitmap(type() / 10 * 6 + type() % 10);
	}
	else if (type() >= 60 && type() <= 65) {
		_candy.SetFrameIndexOfBitmap(type() % 10 + type() / 6 / 10 * 6);
	}
	else if (type() == 99) {
		_candy.SetFrameIndexOfBitmap(31);
	}
	else if (type() == -99) {
		_candy.SetFrameIndexOfBitmap(32);
	}
	else {
		_candy.SetFrameIndexOfBitmap(33);
	}
}

bool Candy::is_sameColor_candy(Candy c) {
	if (is_obstacle() || !can_remove() || type() == 99) {
		return false;
	}
	if (c.type() >= 0 && c.type() <= 35 && type() >= 0 && type() <= 35) {
		if (c.type() % 10 == type() % 10) {
			return true;
		}
	}
	return false;
}

bool Candy::is_sameColor_candy_plus(Candy c) {
	if (is_obstacle() || !can_remove() || type() == 99) {
		return false;
	}
	if (c.type() >= 0 && c.type() <= 35 && type() >= 0 && type() <= 35) {
		if (c.type() % 10 == type() % 10 && !c.will_be_special_candy()) {
			return true;
		}
	}
	
	return false;
}

void Candy::changeToBlank() {
	_fall_status = 3;
	_type = 99;
	updateCandy();
}

void Candy::removeObstacleLayer() {
	if (type() == -1 || type() == -11) {
		changeToBlank();
		return;
	}
	if (is_obstacle()) {
		_type += 1;
	}
}

//void Candy::removeObstacleLayer() {
//	if (!is_obstacle()) {
//		return;
//	}
//	if (type() == -1 || type() == -11) {
//		changeToBlank();
//		return;
//	}
//	_type += 1;
//}

void Candy::removeDragon() {
	if (type() == -21) {
		changeToBlank();
		return;
	}
}
