/*
 * mygame.h: ??¬æ??æ¡???²é????²æ?¬èº«???class???interface
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


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// å®?ç¾©å??ç¨®é?³æ?????ç·¨è??
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??ºé????²ç???????²é????­ç?«é?¢ç?©ä»¶
	// æ¯????Member function???Implementation??½è??å¼????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// ?????²ç???????¼å?????å½¢è¨­å®?
		void OnBeginState();							// è¨­å??æ¯?æ¬¡é????©æ????????è®????
		void OnKeyUp(UINT, UINT, UINT); 				// ????????µç?¤Up??????ä½?
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????æ»?é¼???????ä½?
	protected:
		void OnShow();									// é¡¯ç¤º????????????????????²ç?«é??
	private:
		void load_background();
		void draw_text();
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	// ??????class??ºé????²ç???????²å?·è????©ä»¶ï¼?ä¸»è??????????²ç??å¼???½å?¨é??è£?
	// æ¯????Member function???Implementation??½è??å¼????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// è¨­å??æ¯?æ¬¡é????©æ????????è®????
		void OnInit();  								// ?????²ç???????¼å?????å½¢è¨­å®?
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // ??????æ»?é¼???????ä½?
		void OnLButtonUp(UINT nFlags, CPoint point);	// ??????æ»?é¼???????ä½?
		void OnMouseMove(UINT nFlags, CPoint point);	// ??????æ»?é¼???????ä½? 
		void OnRButtonDown(UINT nFlags, CPoint point);  // ??????æ»?é¼???????ä½?
		void OnRButtonUp(UINT nFlags, CPoint point);	// ??????æ»?é¼???????ä½?
		void DropOneSquare();
		vector<vector<int>> CheckMapStatus(int mp[9][9], int w, int h);
		void vertical_fall_candy(int i,int j);
		void update_candy();
		void remove_obstacle_layer(int i, int j);
		bool CanDelete();
	protected:
		void OnMove();									// ç§»å???????²å??ç´?
		void OnShow();									// é¡¯ç¤º????????????????????²ç?«é??
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
		CMovingBitmap candy[5][5];

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
	// ??????class??ºé????²ç??çµ??????????(Game Over)
	// æ¯????Member function???Implementation??½è??å¼????
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// è¨­å??æ¯?æ¬¡é????©æ????????è®????
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
	protected:
		void OnMove();									// ç§»å???????²å??ç´?
		void OnShow();									// é¡¯ç¤º????????????????????²ç?«é??
	private:
		CMovingBitmap background;
		void load_background();
	};

}