#include <stdafx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include<sstream>
#include<fstream>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "Level.h"

using namespace game_framework;

Level::Level() {

}
void WinRule::Init() {
	game_over.LoadBitmapByString({ "resources/texture_pack_original/bg_screens/gameover.bmp" });
	game_over.SetTopLeft(0, -800);
	game_over.SetFrameIndexOfBitmap(0);
	win.LoadBitmapByString({
		"resources/texture_pack_original/bg_screens/win1.bmp",
		"resources/texture_pack_original/bg_screens/win2.bmp" ,
		"resources/texture_pack_original/bg_screens/win3.bmp" });
	win.SetTopLeft(0, -800);
	win.SetFrameIndexOfBitmap(0);
	for (int i = 0; i < 250; i++) {
		score_image[i].LoadBitmapByString({ "resources/texture_pack_original/bg_screens/score.bmp" });
		score_image[i].SetTopLeft(20, 100);
		score_image[i].SetFrameIndexOfBitmap(0);
	}
	score_edge.LoadBitmapByString({ "resources/texture_pack_original/bg_screens/score_edge.bmp" });
	score_edge.SetTopLeft(18, 98);
	score_edge.SetFrameIndexOfBitmap(0);
}
void WinRule::LoadWinCondition() {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	in.open("Resources/win_rules/" + to_string(map_name) + ".txt");
	in >> moves;
	for (int i = 0; i < 3; i++) {
		in >> star_score[i];
	}
	for (int i = 0; i < 3; i++) {
		in >> has_conditon_type[i];
		if (has_conditon_type[i]) {
			int t, n;
			in >> t;
			while (t != -1) {
				all_condition_number += 1;
				in >> n;
				condition_number[i].push_back({ t,n });
				in >> t;
			}
		}
	}
	in.close();
}