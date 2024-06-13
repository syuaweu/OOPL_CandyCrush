#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <fstream>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;
bool isAccountSettingOpen = 0;
bool isGameOn = 0;
int stage = 0;
int max_stage = 11;
int heart_time = 0;
int heart_number = 5;
int level[10][6][5] = {
		{
			{1, 384, 562, 459, 630},
			{2, 326, 437, 396, 494},
			{3, 362, 257, 431, 398},
			{4, 397, 314, 454, 343},
			{5, 348, 308, 406, 322}
		},
		{
			{4, 391, 673, 464, 743},
			{5, 335, 525, 406, 588},
			{6, 349, 409, 419, 464},
			{7, 392, 338, 458, 373},
			{8, 352, 307, 412, 327}
		},
		{
			{7, 392, 680, 468, 753},
			{8, 342, 530, 415, 593},
			{9, 343, 412, 415, 466},
			{10, 396, 342, 460, 378}
		},
		{
			{11, 359, 664, 438, 737},
			{12, 330, 496, 401, 560},
			{13, 342, 380, 409, 427},
			{14, 396, 342, 465, 346},
			{15, 355, 304, 415, 318}
		},
		{
			{15, 345, 681, 420, 755},
			{16, 314, 510, 385, 575},
			{17, 389, 389, 455, 437},
			{18, 391, 322, 455, 354},
			{19, 337, 304, 394, 322}
		},
		{
			{17, 387, 696, 463, 771},
			{18, 391, 526, 464, 592},
			{19, 327, 403, 395, 454},
			{20, 367, 337, 430, 368}
		},
		{
			{21, 361, 687, 436, 759},
			{22, 392, 567, 465, 639},
			{23, 427, 474, 499, 534},
			{24, 333, 348, 455, 448},
			{25, 337, 304, 394, 384},
			{26, 311, 313, 370, 345}
		},
		{
			{25, 319, 684, 393, 752},
			{26, 296, 569, 368, 639},
			{27, 353, 474, 421, 534},
			{28, 411, 402, 479, 452},
			{29, 400, 353, 464, 391},
			{30, 351, 325, 411, 351}
		},
		{
			{31, 293, 668, 369, 741},
			{32, 330, 556, 403, 624},
			{33, 388, 388, 468, 520},
			{34, 411, 402, 456, 438},
			{35, 367, 339, 431, 375}
		},
		{
			{36, 360, 694, 438, 762},
			{37, 366, 577, 441, 643},
			{38, 397, 483, 469, 542},
			{39, 361, 407, 430, 458},
			{40, 330, 356, 393, 393}
		}
};
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}

void CGameStateInit::OnInit()
{	
	load_background();
	for (int i = 0; i < 25; i++) {
		ShowInitProgress(i * 4, "");
		Sleep(1);
	}
}

void CGameStateInit::OnBeginState()
{
	bool retry;
	ifstream in;
	in.open("Resources/retry.txt");
	in >> retry;
	in.close();
	if (!retry) {
		if(stage != 0){
			stage = 0;
			next_level();
		}
	}
	
}

void CGameStateInit::OnMove()
{	
	TRACE("Stage: %d\n", stage);
	if (stage == 0) {
		if (isAccountSettingOpen == 1 && show_account.GetTop() < 0) {
			show_account.SetTopLeft(0, show_account.GetTop() + 40);
		}
		else if (isAccountSettingOpen == 0 && show_account.GetTop() > -800) {
			show_account.SetTopLeft(0, show_account.GetTop() - 40);
		}
	}
	if (stage > 0 && stage < max_stage) {
		property_status.SetTopLeft(0, 0);
	}
	if (stage == max_stage) {
		stage = max_stage + 1;
		property_status.SetTopLeft(0, -71);
	}
	else if (stage == max_stage + 1) {
		Sleep(1000);
		GotoGameState(GAME_STATE_RUN);
	}
	
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (isGameOn == 0) {
		next_level();
		isGameOn = 1;
	}
	if (nChar == VK_UP) {
		next_level();
	}
	if (nChar == VK_DOWN) {
		previous_level();
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{	
	int mouse_x = point.x;
	int mouse_y = point.y;
	if (isGameOn == 0){
		if (mouse_x > 276 && mouse_y > 366 && mouse_x < 516 && mouse_y < 443 && isAccountSettingOpen == 0) {
			next_level();
			isGameOn = 1;
		}
		else if (mouse_x > 218 && mouse_y > 458 && mouse_x < 537 && mouse_y < 532 && isAccountSettingOpen == 0) {
			isAccountSettingOpen = 1;
		}
		else if(mouse_x > 618 && mouse_y > 0 && mouse_x < 716 && mouse_y < 83 && isAccountSettingOpen == 1){
			isAccountSettingOpen = 0;
		}
	}
	else {
		if (0 < stage && stage < max_stage) {
			pressLevel(stage, mouse_x, mouse_y);
		}
	}
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	show_account.ShowBitmap();
	property_status.ShowBitmap();
	draw_text();
}

void CGameStateInit::load_background() {

	background.LoadBitmapByString({ "Resources/texture_pack_original/bg_screens/start.bmp",
									"Resources/texture_pack_original/level/1to4.bmp",
									"Resources/texture_pack_original/level/4to8.bmp",
									"Resources/texture_pack_original/level/7to10.bmp",
									"Resources/texture_pack_original/level/11to14.bmp",
									"Resources/texture_pack_original/level/15to18.bmp",
									"Resources/texture_pack_original/level/17to20.bmp",
									"Resources/texture_pack_original/level/21to26.bmp",
									"Resources/texture_pack_original/level/25to30.bmp",
									"Resources/texture_pack_original/level/31to35.bmp",
									"Resources/texture_pack_original/level/36to40.bmp",
									"Resources/texture_pack_original/bg_screens/loding.bmp" });
	background.SetTopLeft(0, 0);
	show_account.LoadBitmapByString({ "Resources/texture_pack_original/bg_screens/account_setting.bmp" }, RGB(255,255,255));
	show_account.SetTopLeft(0, -800);
	property_status.LoadBitmapByString({ "Resources/texture_pack_original/property/status.bmp" });
	property_status.SetTopLeft(0, -71);
}

void CGameStateInit::draw_text() {

}

void CGameStateInit::next_level(){
	if (stage < max_stage - 1) {
		stage += 1;
		background.SetFrameIndexOfBitmap(stage);
	}
}
void CGameStateInit::previous_level() {
	if (stage > 1) {
		stage -= 1;
		background.SetFrameIndexOfBitmap(stage);
	}
}

void CGameStateInit::pressLevel(int stage, int x, int y) {
	stage = stage - 1;
	int length = sizeof(level[stage]) / sizeof(level[stage][0]);;
	for (int i = 0; i < length; i++) {
		if (x > level[stage][i][1] && y > level[stage][i][2] && x < level[stage][i][3] && y < level[stage][i][4]) {
			chooseLevel(level[stage][i][0]);
		}
	}
}

void CGameStateInit::chooseLevel(int level) {
	//ofstream ofs1("Resources/map/choose_level.txt");
	//ofs1 << level;
	//ofs1.close();
	ofstream ofs("Resources/init_map/choose_level.txt");
	ofs << level;
	ofs.close();
	stage = max_stage;
	background.SetFrameIndexOfBitmap(stage);
}