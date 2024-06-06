/*
 * mygame.h: ??ï¿½ï¿½??ï¿????ï¿½ï¿½????ï¿½ï¿½?ï¿½èº«???class???interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include"Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// ï¿??ç¾©ï¿½??ç¨®ï¿½?ï¿½ï¿½?????ç·¨ï¿½??
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??ï¿½ï¿½????ï¿½ï¿½???????ï¿½ï¿½????ï¿½ï¿½?ï¿½ï¿½?ï¿½ï¿½?ï¿½ä»¶
	// ï¿?????Member function???Implementation??ï¿½ï¿½??ï¿?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// ?????ï¿½ï¿½???????ï¿½ï¿½?????å½¢è¨­ï¿??
		void OnBeginState();							// è¨­ï¿½??ï¿??æ¬¡ï¿½????ï¿½ï¿½????????ï¿?????
		void OnKeyDown(UINT, UINT, UINT); 				// ????????ï¿½ï¿½?ï¿½Up??????ï¿??
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????ï¿??ï¿????????ï¿??
	protected:
		void OnShow();									// é¡¯ç¤º????????????????????ï¿½ï¿½?ï¿½ï¿½??
		void OnMove();
	private:
		void load_background();
		void draw_text();
		void next_level();
		void previous_level();
		void level_1to4(int x,int y);
		void choose_map(int level);
		CMovingBitmap background;
		CMovingBitmap property_status;
		CMovingBitmap show_account;
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??ï¿½ï¿½????ï¿½ï¿½???????ï¿½ï¿½?ï¿½ï¿½????ï¿½ä»¶ï¿??ä¸»ï¿½??????????ï¿½ï¿½??ï¿????ï¿½ï¿½?ï¿½ï¿½??ï¿??
	// ï¿?????Member function???Implementation??ï¿½ï¿½??ï¿?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// è¨­ï¿½??ï¿??æ¬¡ï¿½????ï¿½ï¿½????????ï¿?????
		void OnInit();  								// ?????ï¿½ï¿½???????ï¿½ï¿½?????å½¢è¨­ï¿??
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????ï¿??ï¿????????ï¿??
		void OnLButtonUp(UINT nFlags, CPoint point);	// ??????ï¿??ï¿????????ï¿??
		void OnMouseMove(UINT nFlags, CPoint point);	// ??????ï¿??ï¿????????ï¿?? 
		void OnRButtonDown(UINT nFlags, CPoint point);  // ??????ï¿??ï¿????????ï¿??
		void OnRButtonUp(UINT nFlags, CPoint point);	// ??????ï¿??ï¿????????ï¿??
		void DropOneSquare();
		vector<vector<int>> CheckMapStatus(int mp[9][9], int w, int h);
		void vertical_fall_candy(int i, int j);
		void update_candy();
		void remove_obstacle_layer(int i, int j);
		bool CanDelete();
		void StartDropOneSquare(int i, int j,int direction);
		void previous_map();
		void next_map();
	protected:
		void OnMove();									// ç§»ï¿½???????ï¿½ï¿½??ï¿??
		void OnShow();									// é¡¯ç¤º????????????????????ï¿½ï¿½?ï¿½ï¿½??
	private:
		int phase = 1;
		int sub_phase = 1;
		CMovingBitmap background;
		CMovingBitmap cursor;
		CMovingBitmap character;
		CMovingBitmap chest_and_key;
		CMovingBitmap bee;
		CMovingBitmap ball;
		CMovingBitmap door[3];
		CMovingBitmap candy[9][9];
		CMovingBitmap jelly[9][9];
		CMovingBitmap condition_icon[10];
		CMovingBitmap game_over;
		CMovingBitmap win;
		CMovingBitmap score_image[250];
		CMovingBitmap score_edge;
		int all_condition_number = 0;
		int score = 0;
		int moves;
		bool has_conditon_type[3];
		int star_score[3];
		vector<pair<int, int>> condition_number[3];
		void LoadWinCondition();
		void ScoreAndMovesCalculate(vector<vector<int>> s);
		bool isGameOver();
		bool isWin();

		void show_image_by_phase();
		void show_text_by_phase();
		bool validate_phase_1();
		bool validate_phase_2();
		bool validate_phase_3();
		bool validate_phase_4();
		bool validate_phase_5();
		bool validate_phase_6();
		//---reconstruct object
		Map map;
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??ï¿½ï¿½????ï¿½ï¿½??ï¿???????????(Game Over)
	// ï¿?????Member function???Implementation??ï¿½ï¿½??ï¿?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// è¨­ï¿½??ï¿??æ¬¡ï¿½????ï¿½ï¿½????????ï¿?????
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// ç§»ï¿½???????ï¿½ï¿½??ï¿??
		void OnShow();									// é¡¯ç¤º????????????????????ï¿½ï¿½?ï¿½ï¿½??
	private:
		CMovingBitmap background;
		void load_background();
	};

}