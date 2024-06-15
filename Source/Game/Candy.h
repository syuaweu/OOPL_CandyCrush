#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class Candy {

public:
	CMovingBitmap _candy;
	int _type;
	int _fall_status;
	pair<int, int> _index;
	pair<int, int> _position;
	pair<int, int> _next_position;
	bool _will_be_special_candy;
	bool _is_animating;
	bool _is_produce;
	bool _is_animation_conflict;

	Candy();
	CMovingBitmap candy();
	int type();
	int fall_status();
	int i();
	int j();
	int x();
	int y();
	int next_direction();
	int next_y();
	bool is_special_candy();
	bool is_animating();
	bool is_frosting();
	bool is_spiral();
	bool is_obstacle();
	bool is_fall();
	bool is_remove_obstacle();
	bool can_remove();
	bool is_animation_conflict();
	bool is_produce();

	bool can_dropped();
	bool will_be_special_candy();
	bool is_sameColor_candy(Candy c);
	bool is_sameColor_candy_plus(Candy c);

	void Init();
	void BeginState();
	void updateCandy();
	void changeToBlank();
	void removeObstacleLayer();
	void removeDragon();
};

