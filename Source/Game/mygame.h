/*
 * mygame.h: ??��??�????��????��?�身???class???interface
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
#include "Candy.h"
#include "Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �??義�??種�?��?????編�??
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??��????��???????��????��?��?��?�件
	// �?????Member function???Implementation??��??�?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// ?????��???????��?????形設�??
		void OnBeginState();							// 設�??�??次�????��????????�?????
		void OnKeyUp(UINT, UINT, UINT); 				// ????????��?�Up??????�??
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????�??�????????�??
	protected:
		void OnShow();									// 顯示????????????????????��?��??
	private:
		void load_background();
		void draw_text();
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??��????��???????��?��????�件�??主�??????????��??�????��?��??�??
	// �?????Member function???Implementation??��??�?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設�??�??次�????��????????�?????
		void OnInit();  								// ?????��???????��?????形設�??
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????�??�????????�??
		void OnLButtonUp(UINT nFlags, CPoint point);	// ??????�??�????????�??
		void OnMouseMove(UINT nFlags, CPoint point);	// ??????�??�????????�?? 
		void OnRButtonDown(UINT nFlags, CPoint point);  // ??????�??�????????�??
		void OnRButtonUp(UINT nFlags, CPoint point);	// ??????�??�????????�??
		void DropOneSquare();
		vector<vector<int>> CheckMapStatus(int mp[9][9], int w, int h);
		void vertical_fall_candy(int i, int j);
		void update_candy();
		void remove_obstacle_layer(int i, int j);
		bool CanDelete();
		void StartDropOneSquare(int i, int j,int direction);
	protected:
		void OnMove();									// 移�???????��??�??
		void OnShow();									// 顯示????????????????????��?��??
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
		Candy c;
		Map m;
		void show_image_by_phase();
		void show_text_by_phase();
		bool validate_phase_1();
		bool validate_phase_2();
		bool validate_phase_3();
		bool validate_phase_4();
		bool validate_phase_5();
		bool validate_phase_6();
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??��????��??�???????????(Game Over)
	// �?????Member function???Implementation??��??�?????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設�??�??次�????��????????�?????
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移�???????��??�??
		void OnShow();									// 顯示????????????????????��?��??
	private:
		CMovingBitmap background;
		void load_background();
	};

}