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

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	ifstream in;
	char w_or_l;
	in.open("Resources/win_or_loose.txt");
	in >> w_or_l;
	in.close();
	
	if (w_or_l=='W' && win.GetTop() < 0) {
		win.SetTopLeft(0, win.GetTop() + 40);
	}

	if (w_or_l == 'L' && game_over.GetTop() < 0) {
		game_over.SetTopLeft(0, game_over.GetTop() + 40);
	}
	
	
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	game_over.LoadBitmapByString({ "resources/texture_pack_original/bg_screens/gameover.bmp" });
	win.LoadBitmapByString({
		"resources/texture_pack_original/bg_screens/win1.bmp",
		"resources/texture_pack_original/bg_screens/win2.bmp" ,
		"resources/texture_pack_original/bg_screens/win3.bmp" });
	game_over.SetTopLeft(0, -800);
	game_over.SetFrameIndexOfBitmap(0);
	win.SetTopLeft(0, -800);
	win.SetFrameIndexOfBitmap(2);

}

void CGameStateOver::OnShow()
{
	game_over.ShowBitmap();
	win.ShowBitmap();
}

void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}


void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x = point.x;
	int y = point.y;
	if (x >= 130 && x <= 370 && y >= 631 && y <= 714) {
		ofstream ofs("Resources/retry.txt");
		ofs << 1;
		ofs.close();
		win.SetTopLeft(0, -800);
		game_over.SetTopLeft(0, -800);
		GotoGameState(GAME_STATE_INIT);
	}
	if (x >= 420 && x <= 660 && y >= 631 && y <= 714) {
		win.SetTopLeft(0, -800);
		game_over.SetTopLeft(0, -800);
		ofstream ofs("Resources/retry.txt");
		ofs << 0;
		ofs.close();
		GotoGameState(GAME_STATE_INIT);
	}
	
}