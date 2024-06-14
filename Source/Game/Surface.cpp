#include <stdafx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Surface.h"

using namespace game_framework; // jelly & lock

Surface::Surface() {

}

void Surface::Init() {
	_type = 0; // 0:none, 1:jelly, 2:lock
	_surface.LoadBitmapByString({
			"Resources/texture_pack_original/surface/blank.bmp",
			"Resources/texture_pack_original/surface/jelly.bmp",
			"Resources/texture_pack_original/surface/lock.bmp",
		});
	_surface.SetTopLeft(0, 0);
	_surface.SetFrameIndexOfBitmap(0);
	_index = { 0, 0 };
	_position = { 0, 0 };
}

CMovingBitmap Surface::surface() {
	return _surface;
}

int Surface::type() {
	return _type;
}

int Surface::i() {
	return _index.first;
}

int Surface::j() {
	return _index.second;
}

int Surface::x() {
	return _position.first;
}

int Surface::y() {
	return _position.second;
}

bool Surface::is_surface() {
	if (type() != 0) {
		return true;
	}
	return false;
}

void Surface::updateSurface() {
	_surface.SetTopLeft(x(), y());
	if (type() <= 2 && type() >= 0) {
		_surface.SetFrameIndexOfBitmap(type());
	}
	else {
		_surface.SetFrameIndexOfBitmap(0);
	}
}

void Surface::changeToBlank() {
	_type = 0;
	updateSurface();
}

void Surface::removeJelly() {
	if (type() == 1) {
		changeToBlank();
		return;
	}
}

void Surface::removeLock() {
	if (type() == 2) {
		changeToBlank();
		return;
	}
}