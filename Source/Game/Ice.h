#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class Ice {
private:
	CMovingBitmap _ice;

public:
	int _layer;
	pair<int, int> _index;
	pair<int, int> _position;

	Ice();
	CMovingBitmap ice();
	int layer();
	int i();
	int j();
	int x();
	int y();

	void Init();
	void updateIce();
};

