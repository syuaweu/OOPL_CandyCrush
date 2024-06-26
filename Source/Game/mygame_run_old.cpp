#include <stdafx.h>
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
#include<sstream>
#include <vector>
#include<math.h>
#include<utility>
#include <fstream>
#include<queue>
#include<algorithm>
using namespace std;
using namespace game_framework;
int idx0 = 0, idx1 = 0;
int idy0 = 0, idy1 = 0;
bool which_mou = 0;
vector<std::pair<int, std::pair<int, int>>> boom_que;
int boom_arr[9][9] = {};
int w = 5, h = 5;
bool is_animation_finished = 1;

int which_candy[9][9] = { 0 };
int which_jelly[9][9] = { 0 };
vector<vector<int>> mp;
vector<vector<int>> jellymp;
int c_x = 0;
int c_y = 0;
std::vector<std::vector<std::pair<int, int>>> candy_xy_position(9);
vector<vector<int>> LoadMap(int *row, int *column) {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	in.open("Resources/map/" + to_string(map_name) + ".txt");
	in >> *row >> *column;
	vector<vector<int>> map(10);
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *column; j++) {
			int x = 0;
			in >> x;
			map[i].push_back(x);
		}
	}
	in.close();

	return map;
}

void CGameStateRun::LoadWinCondition() {
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

vector<vector<int>> LoadStatus(int *row, int *column) {

	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	in.open("Resources/map/" + to_string(map_name) + ".txt");
	in >> *row >> *column;
	vector<vector<int>> map(10);
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *column; j++) {
			int x = 0;
			in >> x;
		}
	}
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *column; j++) {
			int x = 0;
			in >> x;
			map[i].push_back(x);
		}
	}
	in.close();

	return map;
}

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	
	vector<vector<int>> mp = LoadMap(&h, &w);
	vector<vector<int>> jellymp = LoadStatus(&h, &w);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			candy[i][j].LoadBitmapByString({
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
				"Resources/texture_pack_original/candy/7.bmp"
				});
			candy[i][j].SetTopLeft((400 - 25 * w) + j * 50, (400 - 25 * h) + i * 50);
			which_candy[i][j] = mp[i][j];
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			jelly[i][j].LoadBitmapByString({
				"Resources/texture_pack_original/ice/blank.bmp",
				"Resources/texture_pack_original/ice/ice1.bmp",
				"Resources/texture_pack_original/ice/ice2.bmp",
				});
			jelly[i][j].SetTopLeft((400 - 25 * w) + j * 50, (400 - 25 * h) + i * 50);
			which_jelly[i][j] = jellymp[i][j];
		}
	}
	is_animation_finished = 1;
	update_candy();
	/*cursor.LoadBitmapByString({ "Resources/texture_pack_original/cursor.bmp" }, RGB(255, 255, 255));
	cursor.SetTopLeft((400 - 25 * w), (400 - 25 * h));*/
	for (int i = 0; i < h; i++) {
		std::vector<std::pair<int, int>> inner_vector(9);
		for (int j = 0; j < w; j++) {
			inner_vector.push_back(std::make_pair(0, 0));
		}
		candy_xy_position[i] = inner_vector;
	}

	/*character.LoadBitmapByString({ "resources/giraffe.bmp" });
	character.SetTopLeft(0, 0);*/
}



int rnd_number(int start, int end) {
	int min = start;
	int max = end;
	int x = rand() % (max - min + 1) + min;

	return x;
}

bool CheckInitCandy(int arr[9][9], int h, int w) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (arr[i][j] == 99 || arr[i][j] == -10) {
				return true;
			}
			if (arr[i][j] < 0) {
			}
			else {
				if (i >= 2) {
					if (arr[i][j] % 10 == arr[i - 1][j] % 10 && arr[i][j] % 10 == arr[i - 2][j] % 10) {
						return true;
					}
				}
				if (j >= 2) {
					if (arr[i][j] % 10 == arr[i][j - 1] % 10 && arr[i][j] % 10 == arr[i][j - 2] % 10) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void delay(int ms) {
	int set_clock = clock() + ms;
	int now = clock();
	while (now < set_clock) {
		now = clock();
	}
}

bool LTypeCandy(int mp[9][9], int now_h, int now_w) {
if (now_h < 0 || now_w < 0) {
		return false;
	}
	if (now_w >= 2 && now_h < h - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 2] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 2][now_w] % 10) {
			return true;
		}
	}
	if (now_w < w - 2 && now_h < h - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 2] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 2][now_w] % 10) {
			return true;
		}
	}
	if (now_w >= 2 && now_h >= 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 2] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 2][now_w] % 10) {
			return true;
		}
	}
	if (now_w < w - 2 && now_h >= 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 2] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 2][now_w] % 10) {
			return true;
		}
	}
	return false;
}

bool ITypeCandy(int mp[9][9], int now_h, int now_w) {
	if (now_h < 0 || now_w < 0) {
		return false;
	}
	if (now_h >= 2 && now_h < h - 1 ) {
		if (mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 2][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10) {
			return true;
		}
	}
	if (now_h >= 1 && now_h < h - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 2][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10) {
			return true;
		}
	}
	return false;
}

bool TTypeCandy(int mp[9][9], int now_h, int now_w) {
	if (now_h < 0 || now_w < 0) {
		return false;
	}
	if (now_w < w - 2 && now_h >= 1 && now_h < h - 1) {
		if (mp[now_h][now_w] %10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 2]) {
			return true;
		}
	}
	if (now_w >= 2 && now_h >= 1 && now_h < h - 1) {
		if (mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 2] % 10) {
			return true;
		}
	}
	if (now_h >= 2 && now_w >= 1 && now_w < w - 1) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 2][now_w] % 10) {
			return true;
		}
	}
	if (now_h < h - 2 && now_w >= 1 && now_w < w - 1) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 2][now_w] % 10) {
			return true;
		}
	}
	return false;
}

bool ETypeCandy(int mp[9][9], int now_h, int now_w) {
		if (now_h < 0 || now_w < 0) {
		return false;
	}
	if (now_w > 0 && now_w < w - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 2] % 10) {
			return true;
		}
	}
	if (now_w > 1 && now_w < w - 1) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 2] % 10) {
			return true;
		}
	}
	return false;
}
bool ChocoCandy(int mp[9][9], int now_h, int now_w) {
	if (now_h < 0 || now_w < 0) {
		return false;
	}
	if (now_h >= 2 && now_h < h - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h - 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h - 2][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 1][now_w] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h + 2][now_w] % 10) {
			return true;
		}
	}
	if (now_w >= 2 && now_w < w - 2) {
		if (mp[now_h][now_w] % 10 == mp[now_h][now_w - 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w - 2] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 1] % 10
			&& mp[now_h][now_w] % 10 == mp[now_h][now_w + 2] % 10) {
			return true;
		}
	}
	return false;
}

vector < vector<int>> delete_row(vector<vector<int>> st,int r) {
	if (r >= h || r < 0) {
		return st;
	}
	for (int i = 0; i < w; i++) {
		st[r][i] = 0;
	}
	return st;
}
vector < vector<int>> delete_column(vector<vector<int>> st, int c) {
	if (c >= w || c < 0) {
		return st;
	}
	for (int i = 0; i < w; i++) {
		st[i][c] = 0;
	}
	return st;
}
vector < vector<int>> boom(vector<vector<int>> st, int ii, int jj, int x) {
	if (ii >= h || ii < 0 || jj >= w || jj < 0) {
		return st;
	}
	for (int i = ii - 1; i <= ii + 1; i++) {
		for (int j = jj - 1; j <= jj + 1; j++) {
			if (i >= h || i < 0 || j >= w || j < 0) {
				continue;
			}
			//TRACE("AAAAA %d %d || %d %d\n",i,j,ii,jj);
			st[i][j] = 0;
		}
		
	}
	//TRACE("24242424 %d\n", st[2][4]);
	return st;
}

int image_index(int x) {
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

void CGameStateRun::update_candy() {
	if (is_animation_finished == false) {
		return;
	}
	for (int i = h - 1; i >= 0; i--) {
		for (int j = w - 1; j >= 0; j--) {
			if (which_candy[i][j] == -1) {
				candy[i][j].SetFrameIndexOfBitmap(26);
			}
			else if (which_candy[i][j] >= 60 && which_candy[i][j] <= 65) {
				candy[i][j].SetFrameIndexOfBitmap(which_candy[i][j] % 10 + which_candy[i][j] / 6 / 10 * 6);
			}
			else if (which_candy[i][j] >= 60) {
				candy[i][j].SetFrameIndexOfBitmap(32);
			}
			else if (which_candy[i][j] <= -10 && which_candy[i][j] >= -20) {
				candy[i][j].SetFrameIndexOfBitmap(std::abs(which_candy[i][j]) + 17);
			}
			else if (which_candy[i][j] == 7) {
				candy[i][j].SetFrameIndexOfBitmap(34);
			}
			else if (which_candy[i][j] >= 0 && which_candy[i][j] <= 35) {
				candy[i][j].SetFrameIndexOfBitmap(which_candy[i][j] / 10 * 6 + which_candy[i][j] % 10);
			}
			else {
				candy[i][j].SetFrameIndexOfBitmap(33);
			}
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			candy[i][j].SetTopLeft((400 - 25 * w) + j * 50, (400 - 25 * h) + i * 50);
		}
	}
	for (int i = h - 1; i >= 0; i--) {
		for (int j = w - 1; j >= 0; j--) {
			if (which_jelly[i][j] == 1){
				jelly[i][j].SetFrameIndexOfBitmap(1);
			}
			else if(which_jelly[i][j] == 2){
				jelly[i][j].SetFrameIndexOfBitmap(2);
			}
			else{
				jelly[i][j].SetFrameIndexOfBitmap(0);
			}
		}
	}
}

void CGameStateRun::ScoreAndMovesCalculate(vector<vector<int>> s) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (s[i][j] == 0) {
				score += 40;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l<int(condition_number[k].size()); l++) {
						if (condition_number[k][l].first >= 10 && condition_number[k][l].first <= 35) {
							if (which_candy[i][j]/10 == condition_number[k][l].first/10) {
								condition_number[k][l].second -= 1;
							}
						}
						else {
							if (which_candy[i][j] == condition_number[k][l].first) {
								condition_number[k][l].second -= 1;
							}
						}
						
					}
				}
			}
		}
	}
	for (int i = 0; i < 250; i++) {
		if (i < 250 * score / star_score[2]) {
			score_image[i].SetTopLeft(20 + i, 100);
		}
	}
}
bool CGameStateRun::isGameOver() {
	if (moves > 0) {
		return false;
	}
	return true;
}
bool CGameStateRun::isWin() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j<int(condition_number[i].size()); j++) {
			if (condition_number[i][j].second > 0) {
				return false;
			}
		}
	}
	if (score < star_score[0]) {
		return false;
	}
	return true;
}
bool disapear = 0;

vector<vector<int>> CGameStateRun::CheckMapStatus(int mp[9][9], int w, int h) { // 1:normal, 0.2:special
	vector<vector<int>> status(9);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			status[i].push_back(1);
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (which_candy[i][j] == -10 || which_candy[i][j] == 99) {
				status[i][j] = 2;
			}
			else if (mp[i][j] < 0) {
			}
			else {
				if (which_candy[i][j] / 10 == 6) {
					disapear = 1;
					boom_que.push_back({ 1, {i,j} });
				}
				if (i >= 2) {
					if (mp[i][j] % 10 == mp[i - 1][j] % 10 && mp[i][j] % 10 == mp[i - 2][j] % 10) {
						status[i][j] = 0;
						status[i - 1][j] = 0;
						status[i - 2][j] = 0;
						for (int k = i - 2; k <= i; k++) {
							if (which_candy[k][j] / 10 == 2) {
								status=delete_row(status, k);
								score += 500;
							}
							if (which_candy[k][j] / 10 == 3) {
								status = delete_column(status, j);
								score += 500;
							}
							if (which_candy[k][j] / 10 == 1) {
								disapear = 1;
								boom_que.push_back({ 2, {k,j} });
							}
							
						}
					}
				}
				if (j >= 2) {
					if (mp[i][j] % 10 == mp[i][j - 1] % 10 && mp[i][j] % 10 == mp[i][j - 2] % 10) {
						status[i][j] = 0;
						status[i][j - 1] = 0;
						status[i][j - 2] = 0;
						for (int k = j - 2; k <= j; k++) {
							if (which_candy[i][k] / 10 == 2) {
								status = delete_row(status, i);
							}
							if (which_candy[i][k] / 10 == 3) {
								status = delete_column(status, k);
							}
							if (which_candy[i][k] / 10 == 1) {
								disapear = 1;
								boom_que.push_back({ 2, {i,k} });
							}
						}
						
					}
				}
			}
		}
	}
	/*TRACE("wryyyyy %d\n", boom_que.size());*/
	for (auto i : boom_que) {
		status = boom(status, i.second.first, i.second.second, i.first);
		score += 1000;
		if (i.first == 2) {
			status[i.second.first][i.second.second] = 1;
			which_candy[i.second.first][i.second.second] %= 10;
			which_candy[i.second.first][i.second.second] += 60;
			update_candy();
			disapear = 1;
		}
	}
	boom_que.clear();
	int i0 = (idy0 - (400 - 25 * h)) / 50;
	int j0 = (idx0 - (400 - 25 * w)) / 50;
	int i1 = (idy1 - (400 - 25 * h)) / 50;
	int j1 = (idx1 - (400 - 25 * w)) / 50;
	/*TRACE("\n0: %d %d\n1:%d %d\n", i0, j0, i1, j1);*/
	if (i0 >= 0 && i0 < h
		&&i1 >= 0 && i1 < h
		&&j0>=0 && j0 < w
		&&j1>=0 && j1 < w
		&&(i0!=i1||j0!=j1)) {
		if ((which_candy[i0][j0] / 10 == 2 || which_candy[i0][j0] / 10 == 3) &&
			(which_candy[i1][j1] / 10 == 2 || which_candy[i1][j1] / 10 == 3)) {
			disapear = 1;
			status = delete_row(status, i1);
			status = delete_column(status, j1);
			return status;
		}
		else if (((which_candy[i0][j0] / 10 == 2 || which_candy[i0][j0] / 10 == 3) && which_candy[i1][j1] / 10 == 1) ||
			((which_candy[i1][j1] / 10 == 2 || which_candy[i1][j1] / 10 == 3) && which_candy[i0][j0] / 10 == 1)) {
			disapear = 1;
			status = delete_row(status, i1);
			status = delete_column(status, j1);
			status = delete_row(status, i1 - 1);
			status = delete_column(status, j1 - 1);
			status = delete_row(status, i1 + 1);
			status = delete_column(status, j1 + 1);
			return status;
		}
		else if (which_candy[i0][j0] == 7) {
			disapear = 1;
			score += 5000;
			if (which_candy[i1][j1] < 7 && which_candy[i1][j1] >= 0) {
				status[i0][j0] = 0;
				int x = which_candy[i1][j1];
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						if (which_candy[i][j] % 10 == x) {
							status[i][j] = 0;
						}
					}
				}
			}
			else {

			}
			return status;
		}
		else if (which_candy[i1][j1] == 7) {
			disapear = 1;
			score += 5000;
			if (which_candy[i0][j0] < 7 && which_candy[i0][j0] >= 0) {
				status[i1][j1] = 0;
				int x = which_candy[i0][j0];
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						if (which_candy[i][j] % 10 == x) {
							status[i][j] = 0;
						}
					}
				}
			}
			else {

			}
			return status;
		}
		for (int i = 0; i < 2; i++) {
			int ii = (idy0 - (400 - 25 * h)) / 50;
			int jj = (idx0 - (400 - 25 * w)) / 50;
			if (i == 1) {
				ii = (idy1 - (400 - 25 * h)) / 50;
				jj = (idx1 - (400 - 25 * w)) / 50;
			}

			if (ChocoCandy(mp, ii, jj)) {
				status[ii][jj] = 1;

				which_candy[ii][jj] = 7;
				update_candy();
				disapear = 1;
				return status;
			}
			if (LTypeCandy(mp, ii, jj) || TTypeCandy(mp, ii, jj)) {
				status[ii][jj] = 1;
				which_candy[ii][jj] %= 10;
				which_candy[ii][jj] += 10;
				disapear = 1;
				update_candy();
				return status;
			}
			if (ETypeCandy(mp, ii, jj)) {
				status[ii][jj] = 1;
				which_candy[ii][jj] %= 10;
				which_candy[ii][jj] += 30;
				update_candy();
				disapear = 1;
				return status;
			}
			if (ITypeCandy(mp, ii, jj)) {
				TRACE("AAAAAAAAA %d %d: %d", ii, jj, ITypeCandy(mp, ii, jj));
				status[ii][jj] = 1;
				which_candy[ii][jj] %= 10;
				which_candy[ii][jj] += 20;
				disapear = 1;
				update_candy();
			}

		}
	}
	
	
	
	
	/*
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (LTypeCandy(mp, i, j) || TTypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 10;
				disapear = 1;
				update_candy();
			}
			if (ITypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 20;
				disapear = 1;
				update_candy();
			}
			if (ETypeCandy(mp, i, j)) {
				status[i][j] = 1;
				which_candy[i][j] %= 10;
				which_candy[i][j] += 30;
				disapear = 1;
				update_candy();
			}
		}
	}
	*/
	return status;
}



void CGameStateRun::StartDropOneSquare(int i, int j, int direction) {
	TRACE("start%d\n", which_candy[0][0]);
	TRACE("StartDropOneSquare%d %d %d\n",i,j,direction);
	if (candy_xy_position[i][j].first == 0 && candy_xy_position[i][j].second == 0) {
		is_animation_finished = 0;
	}
	candy_xy_position[i][j].first = direction;
	candy_xy_position[i][j].second = candy[i][j].GetTop() + 50;
	if (i == 0) { //potential bug (fall candy probably not start from i=0)
		return;
	}
	if (which_candy[i - 1][j] >= -5 || which_candy[i - 1][j] == -10) {
		StartDropOneSquare(i - 1, j, 0);
		// TRACE("%d %d", i - 1, j);
		return;
	}
	if (j > 0) {
		if (which_candy[i - 1][j - 1] >= -5) {
			StartDropOneSquare(i - 1, j - 1, -1);
			// TRACE("%d %d", i - 1, j - 1);
			return;
		}
	}
	if (j <= w - 1) {
		if (which_candy[i - 1][j + 1] >= -5) {
			StartDropOneSquare(i - 1, j + 1, 1);
			// TRACE("%d %d", i - 1, j + 1);
			return;
		}
	}
}

void CGameStateRun::DropOneSquare() {
	TRACE("drop%d\n", which_candy[0][0]);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (candy_xy_position[i][j].second != 0 || candy_xy_position[i][j].first != 0) {
				candy[i][j].SetTopLeft(candy[i][j].GetLeft() - candy_xy_position[i][j].first * 5, candy[i][j].GetTop() + 5);
				if (candy[i][j].GetTop() == candy_xy_position[i][j].second) {
					candy_xy_position[i][j].first = 0;
					candy_xy_position[i][j].second = 0;
					is_animation_finished = 1;
				}
			}
		}
	}
}


//vector<vector<int>> UpdateMap(vector<vector<int>> mp, int i, int j) {
//	for (int k = i; k > 0; k--) {
//		mp[k][j] = mp[k - 1][j];
//	}
//	mp[0][j] = rnd_number(0, 5);
//	return mp;
//}

void CGameStateRun::vertical_fall_candy(int i, int j) {
	if (i == 0) {
		which_candy[i][j] = rnd_number(0, 3);
		return;
	}
	if (which_candy[i - 1][j] >= -5 || which_candy[i - 1][j] == -10) {
		which_candy[i][j] = which_candy[i - 1][j];
		vertical_fall_candy(i - 1, j);
		return;
	}
	if (j > 0) {
		if (which_candy[i - 1][j - 1] >= -5) {
			which_candy[i][j] = which_candy[i - 1][j - 1];
			vertical_fall_candy(i - 1, j - 1);
			return;
		}
	}
	if (j <= w - 1) {
		if (which_candy[i - 1][j + 1] >= -5) {
			which_candy[i][j] = which_candy[i - 1][j + 1];
			vertical_fall_candy(i - 1, j + 1);
			return;
		}
	}
	which_candy[i][j] = -10;
}

void CGameStateRun::remove_obstacle_layer(int i, int j) {
	if (which_jelly[i][j] != 0) {
		which_jelly[i][j] -= 1;
		score += 1000;
	}
	if (i > 0) {
		if (which_candy[i - 1][j] > -15 && which_candy[i - 1][j] < 0 && which_candy[i - 1][j] != -10 && which_candy[i - 1][j] != 99) {
			which_candy[i - 1][j] += 1;
		}
	}
	if (j > 0) {
		if (which_candy[i][j - 1] > -15 && which_candy[i][j - 1] < 0 && which_candy[i][j - 1] != -10 && which_candy[i][j - 1] != 99) {
			which_candy[i][j - 1] += 1;
		}
	}
	if (i < h - 1) {
		if (which_candy[i + 1][j] > -15 && which_candy[i + 1][j] < 0 && which_candy[i + 1][j] != -10 && which_candy[i + 1][j] != 99) {
			which_candy[i + 1][j] += 1;
		}
	}
	if (j < w - 1) {
		if (which_candy[i][j + 1] > -15 && which_candy[i][j + 1] < 0 && which_candy[i][j + 1] != -10 && which_candy[i][j + 1] != 99) {
			which_candy[i][j + 1] += 1;
		}
	}
}

void CGameStateRun::OnMove()
{	
	vector<vector<int>> status = CheckMapStatus(which_candy, w, h);
	DropOneSquare();
	if ((CheckInitCandy(which_candy, h, w) || disapear) && is_animation_finished) {
		
		ScoreAndMovesCalculate(status);
		disapear = 0;
		TRACE("is_animation_finished%d %d %d\n", CheckInitCandy(which_candy, h, w),disapear, is_animation_finished);
		update_candy();
		bool isFallCandy = false;
		for (int j = 0; j < w; j++) { // status2: fall one layer
			for (int i = 0; i < h; i++) 
			{
				if (status[i][j] == 2) {
					TRACE("StartDropOneSquare:%d %d\n",i,j);
					isFallCandy = true;
					StartDropOneSquare(i, j, 0);
					vertical_fall_candy(i, j);
				}
				if (isFallCandy == true) {
					update_candy();
					return;
				}
			}
			if (isFallCandy == true) {
				update_candy();
				return;
			}
		}
		
		// status: 0 => 2
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (status[i][j] == 0) {
					TRACE("changeStatus\n");
					candy[i][j].SetFrameIndexOfBitmap(32);
					which_candy[i][j] = 99;
					remove_obstacle_layer(i, j);
				}
			}
		}
		idx0 = 0, idx1 = 0;
		idy0 = 0, idy1 = 0;
		which_mou = 0;
	}
	if (is_animation_finished) {
		update_candy();
	}
	if (isGameOver() && game_over.GetTop() < 0) {
		game_over.SetTopLeft(0, game_over.GetTop() + 40);
	}

	if (isWin()) {
		if (score >= star_score[2]) {
			win.SetFrameIndexOfBitmap(2);
		}
		else if (score >= star_score[1]) {
			win.SetFrameIndexOfBitmap(1);
		}
		else {
			win.SetFrameIndexOfBitmap(0);
		}
		if (win.GetTop() < 0) {
			win.SetTopLeft(0, win.GetTop() + 40);
		}
	}
}

void CGameStateRun::OnInit()
{
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
	background.LoadBitmapByString({
		"resources/texture_pack_original/bg_screens/3.bmp",
		"resources/texture_pack_original/bg_screens/2.bmp",
		"resources/texture_pack_original/bg_screens/1.bmp",
		"resources/texture_pack_original/bg_screens/0.bmp",
		});
	background.SetTopLeft(0, 0);
	vector<vector<int>> mp = LoadMap(&h, &w);
	vector<vector<int>> jellymp = LoadStatus(&h, &w);
	LoadWinCondition();

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);
	bee.SetAnimation(10, false);

	ball.LoadBitmapByString({ "resources/ball-3.bmp", "resources/ball-3.bmp", "resources/ball-2.bmp", "resources/ball-1.bmp", "resources/ball-ok.bmp" });
	ball.SetTopLeft(150, 430);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			candy[i][j].LoadBitmapByString({
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
				"Resources/texture_pack_original/candy/7.bmp"
				});
			candy[i][j].SetTopLeft((400 - 25 * w) + j * 50, (400 - 25 * h) + i * 50);
			which_candy[i][j] = mp[i][j];
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			jelly[i][j].LoadBitmapByString({
				"Resources/texture_pack_original/ice/blank.bmp",
				"Resources/texture_pack_original/ice/ice1.bmp",
				"Resources/texture_pack_original/ice/ice2.bmp",
				});
			jelly[i][j].SetTopLeft((400 - 25 * w) + j * 50, (400 - 25 * h) + i * 50);
			which_jelly[i][j] = jellymp[i][j];
		}
	}
	is_animation_finished = 1;
	update_candy();
	/*cursor.LoadBitmapByString({ "Resources/texture_pack_original/cursor.bmp" }, RGB(255, 255, 255));
	cursor.SetTopLeft((400 - 25 * w), (400 - 25 * h));*/
	for (int i = 0; i < h; i++) {
		std::vector<std::pair<int, int>> inner_vector(9);
		for (int j = 0; j < w; j++) {
			inner_vector.push_back(std::make_pair(0, 0));
		}
		candy_xy_position[i] = inner_vector;
	}
	
	/*character.LoadBitmapByString({ "resources/giraffe.bmp" });
	character.SetTopLeft(0, 0);*/
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < int(condition_number[i].size()); j++) {
			condition_icon[k].LoadBitmapByString({
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
				"Resources/texture_pack_original/ice/ice1.bmp"});
			condition_icon[k].SetFrameIndexOfBitmap(image_index(condition_number[i][j].first));
			condition_icon[k].SetTopLeft(400 - (130 * all_condition_number) / 2 + k * 130, 50);
			k++;
		}
	}
	for (int i = 0; i < all_condition_number; i++) {
		
		
	}
	

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		previous_map();
	}
	if (nChar == VK_RIGHT) {
		next_map();
	}
}
void CGameStateRun::previous_map() {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	if (map_name - 1 > 0) {
		ofstream ofs("Resources/map/choose_level.txt");
		ofs << map_name - 1;
		ofs.close();
	}
	GotoGameState(GAME_STATE_INIT);
}
void CGameStateRun::next_map() {
	ifstream in;
	int map_name;
	in.open("Resources/map/choose_level.txt");
	in >> map_name;
	in.close();
	if (map_name + 1 <= 30) {
		ofstream ofs("Resources/map/choose_level.txt");
		ofs << map_name + 1;
		ofs.close();
	}
	GotoGameState(GAME_STATE_INIT);
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void swtch(int now_x, int now_y, int pr_x, int pr_y) {
	int xx = which_candy[now_y][now_x];
	which_candy[now_y][now_x] = which_candy[pr_y][pr_x];
	which_candy[pr_y][pr_x] = xx;
	
}

bool CGameStateRun::CanDelete() {
	int row0 = (idy0 - (400 - 25 * h)) / 50;
	int column0 = (idx0 - (400 - 25 * w)) / 50;
	int row1 = (idy1 - (400 - 25 * h)) / 50;
	int column1 = (idx1 - (400 - 25 * w)) / 50;
	if (!(std::abs(row0 - row1) == 1 && std::abs(column0 - column1) == 0) && !(std::abs(row0 - row1) == 0 && std::abs(column0 - column1) == 1)) {
		return false;
	}
	if (which_candy[row0][column0] < -10 || which_candy[row1][column1] < -10) {
		return false;
	}
	swtch(column0, row0
		, column1, row1);
	if (which_candy[row0][column0] >= 10 && which_candy[row1][column1] >= 10) {
		return true;
	}
	if (which_candy[row0][column0] == 7 || which_candy[row1][column1] == 7) {
		update_candy();
		return true;
	}
	if (CheckInitCandy(which_candy, w, h)) {
		update_candy();
		return true;
	}
	swtch(column0, row0
		, column1, row1);
	return false;
}
bool inSquare() {
	int potx = (400 - 25 * w);
	int poty = (400 - 25 * h);
	if (idx0 < potx || idx1 < potx) {
		return 0;
	}
	if (idx0 > potx + 50 * w || idx1 > potx + 50 * w) {
		return 0;
	}
	if (idy0 < poty || idy1 < poty) {
		return 0;
	}
	if (idy0 > poty + 50 * h || idy1 > poty + 50 * h) {
		return 0;
	}
	return 1;
}

bool oneInSquare() {
	int potx = (400 - 25 * w);
	int poty = (400 - 25 * h);

	if (which_mou) {
		if (idx0 < potx || idx0 > potx + 50 * w || idy0 < poty || idy0 > poty + 50 * h) {
			return 0;
		}
		return 1;
	}
	else {
		if (idx1 < potx || idx1 > potx + 50 * w || idy1 < poty || idy1 > poty + 50 * h) {
			return 0;
		}
		return 1;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
	idx1 = point.x;
	idy1 = point.y;
	if (!inSquare()||!CanDelete()) {
		idx0 = idx1;
		idy0 = idy1;	
	}
	else {
		moves -= 1;
	}

	/*if (oneInSquare()) {
		cursor.SetTopLeft((point.x - (400 - 25 * w)) / 50 * 50 + (400 - 25 * w),
			(point.y - (400 - 25 * h)) / 50 * 50 + (400 - 25 * h));
		cursor.ShowBitmap();
	}*/


}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
{

}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)
{


}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();
	show_text_by_phase();
	game_over.ShowBitmap();
	win.ShowBitmap();
	
}

void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {
		background.SetFrameIndexOfBitmap((phase - 1) * 2 + (sub_phase - 1));
		background.ShowBitmap();
		/*character.ShowBitmap();*/

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				jelly[i][j].ShowBitmap();
				candy[i][j].ShowBitmap();
				
			}
		}

		for (int i = 0; i < all_condition_number; i++) {
			condition_icon[i].ShowBitmap();
		}

		
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				candy[i][j].ShowBitmap();
			}
		}
		score_edge.ShowBitmap();
		for (int i = 0; i < 250; i++) {
			score_image[i].ShowBitmap();
		}
		
		

		/*cursor.ShowBitmap();*/

		if (phase == 3 && sub_phase == 1) {
			chest_and_key.ShowBitmap();
		}
		if (phase == 4 && sub_phase == 1) {
			bee.ShowBitmap();
		}
		if (phase == 5 && sub_phase == 1) {
			for (int i = 0; i < 3; i++) {
				door[i].ShowBitmap();
			}
		}
		if (phase == 6 && sub_phase == 1) {
			ball.ShowBitmap();
		}
	}
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 21, "", RGB(0, 0, 0), 800);
	CTextDraw::Print(pDC, 237, 128, "");
	CTextDraw::Print(pDC, 55, 163, "");
	for (int i = 0; i < 3; i++) {
		CTextDraw::Print(pDC, 20+250*star_score[i]/star_score[2], 60, "¡¹");
	}
	//CTextDraw::Print(pDC, 50, 60, to_string(score));
	CTextDraw::Print(pDC, 50, 30, to_string(moves));
	/*CTextDraw::Print(pDC, 50, 50, "timer:" + to_string(clock()));*/
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < int(condition_number[i].size()); j++) {
			CTextDraw::Print(pDC, 400 - (130 * all_condition_number) / 2 + k * 130 + 60, 50, to_string(condition_number[i][j].second>0? condition_number[i][j].second:0));
		}
	}
	CDDraw::ReleaseBackCDC();
}

bool CGameStateRun::validate_phase_1() {
	/*return character.GetImageFileName() == "resources/giraffe.bmp";*/
	return 0;
}

bool CGameStateRun::validate_phase_2() {
	
	return 0;
}

bool CGameStateRun::validate_phase_3() {
	
	return 0;
}

bool CGameStateRun::validate_phase_4() {
	return bee.IsAnimation() && bee.GetFrameSizeOfBitmap() == 2;
}

bool CGameStateRun::validate_phase_5() {
	bool check_all_door_is_open = true;
	for (int i = 0; i < 3; i++) {
		check_all_door_is_open &= (door[i].GetFrameIndexOfBitmap() == 1);
	}
	return check_all_door_is_open;
}

bool CGameStateRun::validate_phase_6() {
	return ball.IsAnimationDone() && !ball.IsAnimation() && ball.GetFrameIndexOfBitmap() == ball.GetFrameSizeOfBitmap() - 1;
}