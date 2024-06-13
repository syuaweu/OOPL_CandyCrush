#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class Surface {
private:
	CMovingBitmap _surface;

public:
	int _type;
	pair<int, int> _index;
	pair<int, int> _position;

	Surface();
	CMovingBitmap surface();
	bool is_surface();
	int type();
	int i();
	int j();
	int x();
	int y();

	void Init();
	void updateSurface();
	void changeToBlank();
	void removeJelly();
	void removeLock();
};

