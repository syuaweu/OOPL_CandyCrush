#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class Candy {
private:
	CMovingBitmap _candy;
	
public:
	int _type;
	pair<int, int> _index;
	pair<int, int> _position;
	bool _is_special_candy;
	Candy();
	CMovingBitmap candy();
	int type();
	int i();
	int j();
	int x();
	int y();
	bool is_special_candy();
	void Init();
	void updateCandy();
};

