#include <stdafx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Ice.h"

using namespace game_framework;

Ice::Ice() {

}

void Ice::Init() {
	_layer = 0;
	_ice.LoadBitmapByString({
			"Resources/texture_pack_original/ice/blank.bmp",
			"Resources/texture_pack_original/ice/ice1.bmp",
			"Resources/texture_pack_original/ice/ice2.bmp",
		});
	_ice.SetTopLeft(0, 0);
	_ice.SetFrameIndexOfBitmap(0);
	_index = { 0, 0 };
	_position = { 0, 0 };
}

CMovingBitmap Ice::ice() {
	return _ice;
}

int Ice::layer() {
	return _layer;
}

int Ice::i() {
	return _index.first;
}

int Ice::j() {
	return _index.second;
}

int Ice::x() {
	return _position.first;
}

int Ice::y() {
	return _position.second;
}

bool Ice::isIce() {
	if (layer() != 0) {
		return true;
	}
	return false;
}

void Ice::updateIce() {
	_ice.SetTopLeft(x(), y());
	if (layer() <= 2 && layer() >= 0) {
		_ice.SetFrameIndexOfBitmap(layer());
	}
	else {
		_ice.SetFrameIndexOfBitmap(0);
	}
}
