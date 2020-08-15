#include "main.h"


using namespace std;

//  get distance^2 from center of House
float get_dist(float x, float y)
{
	return pow(x - TEE_X, 2) + pow(y - TEE_Y, 2);
}

//  get distance^2 of two cordinates
float get_dist(float x1, float y1, float x2, float y2)
{
	return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

//  is a Stone in House
bool is_in_House(float x, float y)
{
	if (get_dist(x, y) < pow(HOUSE_R + STONE_R, 2)) {
		return true;
	}
	else {
		return false;
	}
}

//  sort Shot number 排序编号 (rank[] = {0, 1, 2 ... 15})
//  by distance from center of House (TEEX, TEEY)vv按离中心的距离
void get_ranking(int *rank, const GAMESTATE* const gs)
{
	// init array
	for (int i = 0; i < 16; i++) {
		rank[i] = i;
	}
	// sort
	int tmp;
	for (int i = 1; i < gs->ShotNum; i++) {
		for (int j = i; j > 0; j--) {
			if (get_dist(gs->body[rank[j]][0], gs->body[rank[j]][1]) < get_dist(gs->body[rank[j - 1]][0], gs->body[rank[j - 1]][1])) {
				// swap
				tmp = rank[j];
				rank[j] = rank[j - 1];
				rank[j - 1] = tmp;
			}
			else {
				break;
			}
		}
	}
}

// make your decision here
int min;      //离某条线最近的壶
int score;    //离营中心最近的壶
int direction_flag; //方向标志位  0：直线  -5：左偏5  5：右偏5  -10：左偏10   10：右偏10  1:目标位置在大本营右方且全部有遮挡  -1:目标位置在大本营左方且全部有遮挡     
				   

void getBestShot(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	float v = 0;
	int w;
	float x,y;
	float s,h;
	static int mode = 0;//开局mode为0，优势2分换lpy，mode为1，优势低于2分换回去，mode为2
	int scorenum = 0;
	int j;
	int xianhou=0;
	for (j = 0; j < gs->CurEnd; j++)
		scorenum += gs->Score[j];
	if (mode == 0 && scorenum >= 2)
		mode = 1;
	if (mode == 0)
	{
		if (gs->ShotNum % 2 == 0)//先手
		{
			First_player5(gs, vec_ret);
		}
		else    //后手
		{
			Second_player5(gs, vec_ret);
		}	
	}
	else
	{
		if (gs->ShotNum == 0 || gs->ShotNum == 1)
			if (xianhou == 1 && gs->Score[gs->CurEnd - 1] < -1 || xianhou == 2 && gs->Score[gs->CurEnd - 1] < 1)
				mode = 2;
		if (mode == 1)
		{
			if (gs->ShotNum % 2 == 0)//先手
			{
				First_player_lpy(gs, vec_ret);
				xianhou = 1;

			}
			else    //后手
			{
				Second_player_3_lpy(gs, vec_ret);
				xianhou = 2;
			}
		}
		else
		{
			if (gs->ShotNum % 2 == 0)//先手
			{
				First_player5(gs, vec_ret);
			}
			else    //后手
			{
				Second_player5(gs, vec_ret);
			}
		}
	}
}