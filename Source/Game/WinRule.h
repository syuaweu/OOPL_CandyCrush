#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Map.h"

using namespace game_framework;

class WinRule {
private:

public:
	WinRule();
	CMovingBitmap condition_icon[10];
	CMovingBitmap game_over;
	CMovingBitmap win;
	CMovingBitmap score_image[250];
	CMovingBitmap score_edge;
	void Init();
	int all_condition_number = 0;
	int score = 0;
	int moves;
	bool has_conditon_type[3];
	int star_score[3];
	vector<pair<int, int>> condition_number[3];
	void LoadWinCondition();
	//void ScoreAndMovesCalculate(Map mp);
	//bool isGameOver();
	//bool isWin();
};

