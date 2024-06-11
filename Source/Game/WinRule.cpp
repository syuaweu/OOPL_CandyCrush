#include <stdafx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include<sstream>
#include<fstream>
#include "../Core/Resource.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "WinRule.h"

using namespace game_framework;

WinRule::WinRule() {

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
	for (int i = 0; i < 10; i++) {
		condition_icon[i].LoadBitmapByString({
			"Resources/texture_pack_original/candy/0.bmp",
			"Resources/texture_pack_original/candy/1.bmp",
			"Resources/texture_pack_original/candy/2.bmp",
			"Resources/texture_pack_original/candy/3.bmp",
			"Resources/texture_pack_original/candy/4.bmp",
			"Resources/texture_pack_original/candy/5.bmp",
			"Resources/texture_pack_original/candy/10.bmp",
			"Resources/texture_pack_original/candy/11.bmp",
			"Resources/texture_pack_original/candy/12.bmp",
			"Resources/texture_pack_original/candy/13.bmp",
			"Resources/texture_pack_original/candy/14.bmp",
			"Resources/texture_pack_original/candy/15.bmp",
			"Resources/texture_pack_original/candy/20.bmp",
			"Resources/texture_pack_original/candy/21.bmp",
			"Resources/texture_pack_original/candy/22.bmp",
			"Resources/texture_pack_original/candy/23.bmp",
			"Resources/texture_pack_original/candy/24.bmp",
			"Resources/texture_pack_original/candy/25.bmp",
			"Resources/texture_pack_original/candy/30.bmp",
			"Resources/texture_pack_original/candy/31.bmp",
			"Resources/texture_pack_original/candy/32.bmp",
			"Resources/texture_pack_original/candy/33.bmp",
			"Resources/texture_pack_original/candy/34.bmp",
			"Resources/texture_pack_original/candy/35.bmp",
			"Resources/texture_pack_original/candy/40.bmp",
			"Resources/texture_pack_original/candy/50.bmp",
			"Resources/texture_pack_original/candy/-1.bmp",
			"Resources/texture_pack_original/candy/-10.bmp",
			"Resources/texture_pack_original/candy/-11.bmp",
			"Resources/texture_pack_original/candy/-12.bmp",
			"Resources/texture_pack_original/candy/-13.bmp",
			"Resources/texture_pack_original/candy/-99.bmp",
			"Resources/texture_pack_original/candy/99.bmp",
			"Resources/texture_pack_original/candy/999.bmp",
			"Resources/texture_pack_original/candy/7.bmp",
			"Resources/texture_pack_original/ice/ice1.bmp" });
	}
	
}
void WinRule::LoadWinCondition() {
	TRACE("winnnnn");
	ifstream in;
	int map_name;
	in.open("Resources/init_map/choose_level.txt");
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
	int k = 0;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < int(condition_number[i].size()); j++) {
			TRACE("number:%d\n", condition_number[i][j].first);
			condition_icon[k].SetFrameIndexOfBitmap(image_index(condition_number[i][j].first));
			condition_icon[k].SetTopLeft(400 - (130 * all_condition_number) / 2 + k * 130, 50);
			k++;
		}
	}
}

void WinRule::Show() {
	game_over.ShowBitmap();
	win.ShowBitmap();
	score_edge.ShowBitmap();
	for (int i = 0; i < 250; i++) {
		score_image[i].ShowBitmap();
	}
	for (int i = 0; i < all_condition_number; i++) {
		condition_icon[i].ShowBitmap();
	}
}

int WinRule::image_index(int x) {
	if (x == -1) {
		return 26;
	}
	else if (x >= 60 && x <= 65) {
		return x % 10 + x / 6 / 10 * 6;
	}
	else if (x >= 60) {
		return 32;
	}
	else if (x <= -10) {
		return std::abs(x) + 17;
	}
	else if (x == 7) {
		return 34;
	}
	else if (x >= 0 && x <= 35) {
		return x / 10 * 6 + x % 10;
	}
	else {
		return 33;
	}
}

