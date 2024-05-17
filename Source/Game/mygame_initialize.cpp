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
int max_stage = 4;
int heart_time = 0;
int heart_number = 5;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}

void CGameStateInit::OnInit()
{	
	
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	
	load_background();
	for (int i = 0; i < 25; i++) {
		ShowInitProgress(i * 4, "");
		Sleep(1);
	}
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnMove()
{	
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
		stage = 5;
		property_status.SetTopLeft(0, -71);
	}
	else if (stage == 5) {
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
		if (stage == 1) {
			level_1to4(mouse_x, mouse_y);
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
	if (stage < 3) {
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

void CGameStateInit::level_1to4(int x,int y) {
	if (x > 384 && y > 562 && x < 459 && y < 630) {
		//level = 1;
		choose_map(1);
	}
	else if (x > 326 && y > 437 && x < 396 && y < 494) {
		choose_map(2);
	}
	else if (x > 362 && y > 357 && x < 431 && y < 398) {
		choose_map(3);
	}
	else if (x > 397 && y > 314 && x < 454 && y < 343) {
		choose_map(4);
	}
}
void CGameStateInit::choose_map(int level) {
	ofstream ofs("Resources/map/choose_level.txt");
	ofs << level;
	ofs.close();
	stage = max_stage;
	background.SetFrameIndexOfBitmap(stage);
}