#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class Candy {
protected:
	CMovingBitmap _candy;
	int _type;
	pair<int, int> _index;
	pair<int, int> _position;

public:
	Candy();
	CMovingBitmap candy();
	int type();
	int i();
	int j();
	int x();
	int y();
	void Init();
	void updateCandy();
};

