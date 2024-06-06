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
	int _fall_status;
	pair<int, int> _index;
	pair<int, int> _position;
	bool _is_special_candy;
	bool _will_be_special_candy;

	Candy();
	CMovingBitmap candy();
	int type();
	int fall_status();
	int i();
	int j();
	int x();
	int y();
	bool is_special_candy();
	bool is_frosting();
	bool is_fall();
	bool is_remove_obstacle();
    bool can_remove_obstacle();
	bool can_dropped();
	bool will_be_special_candy();
	bool is_sameColor_candy(Candy c);

	void Init();
	void updateCandy();
};

