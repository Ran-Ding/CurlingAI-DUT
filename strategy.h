#pragma once
#include "main.h"

extern int min;      //离某条线最近的壶
extern int score;    //离营中心最近的壶
extern int direction_flag;

typedef struct _GAMESTATE {
	int		ShotNum;		// number of Shot
							// if ShotNum = n, next Shot is (n+1)th shot in this End
	int		CurEnd;			// (number of current end) - 1
	int		LastEnd;		// number of final End
	int		Score[8];		// score of each End (if Score < 0: First player in 1st End scored)
	bool	WhiteToMove;	// Which player will shot next
							// if WhiteToMove = 0: First player in 1st End will shot next, 
							//  else (WhiteToMove = 1) : Second player will shot next

	float	body[16][2];	// body[n][0] : x of coordinate of n th stone
							// body[n][1] : y of coordinate of n th stone

}GAMESTATE, * PGAMESTATE;


typedef struct  _ShotInfo
{
	_ShotInfo(float s, float h, float a)
	{
		speed = s;
		h_x = h;
		angle = a;
	};
	float speed;
	float h_x;
	float angle;
}SHOTINFO;

typedef struct _MOTIONINFO
{
	float x_coordinate;
	float y_coordinate;
	float x_velocity;
	float y_velocity;
	float angular_velocity;
}MOTIONINFO;

// positions on sheet
static const float TEE_X   = (float)2.375;    // x of center of house
static const float TEE_Y   = (float)4.880;    // y of center of house
static const float HOUSE_R = (float)1.870;    // radius of house
static const float STONE_R = (float)0.145;    // radius of stone

static const float Fline = (float)10.57;	  //远端前掷线位置

// coordinate (x, y) is in play-area if:
//   (PLAYAREA_X_MIN < x < PLAYAREA_X_MAX && PLAYAREA_Y_MIN < y < PLAYAREA_Y_MAX)
static const float PLAYAREA_X_MIN = (float)0.000 + STONE_R;
static const float PLAYAREA_X_MAX = (float)0.000 + (float)4.750 - STONE_R;
static const float PLAYAREA_Y_MIN = (float)2.650 + STONE_R;
static const float PLAYAREA_Y_MAX = (float)2.650 + (float)8.165 + STONE_R;

float get_dist(float x, float y);
float get_dist(float x1, float y1, float x2, float y2);
bool is_in_House(float x, float y);
void get_ranking(int* rank, const GAMESTATE* const gs);
void getBestShot  (const GAMESTATE* gs, SHOTINFO* vec_ret);



