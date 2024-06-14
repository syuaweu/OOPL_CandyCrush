#pragma once
#include <mmsystem.h>
#include <ddraw.h>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

using namespace game_framework;

class WinRule {
private:

public:
	WinRule();
	CMovingBitmap condition_icon;
	
	CMovingBitmap score_image[255];
	CMovingBitmap score_edge;
	void Init();
	int all_condition_number = 0;
	int score = 0;
	int moves;
	bool has_conditon_type[3];
	int star_score[3];
	vector<pair<int, int>> condition_number[4];

	void LoadWinCondition();
	void Show();
	int image_index(int x);
	//void ScoreAndMovesCalculate(Map mp);
	bool isGameOver();
	bool isWin();
	void BeginState();
};

