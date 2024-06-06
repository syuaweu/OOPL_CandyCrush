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
	int _fall_status; // 0:不用掉, 1:本人掉一次糖果+四周障礙物消一層, 2:本人消一層障礙物或掉一次糖果, -1:不能消
	pair<int, int> _index;
	pair<int, int> _position;
	bool _is_special_candy;

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
	bool can_dropped();
	bool can_remove_obstacle();

	void Init();
	void updateCandy();
};

