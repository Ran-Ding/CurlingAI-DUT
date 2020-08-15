#pragma once
#include "main.h"


extern int flag1[20];
extern int flag2[10];	//记录我方壶是否被撞飞

void First_player  (const GAMESTATE* const gs, SHOTINFO* vec_ret);									//先手函数
void First_player2(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//先手函数（加保护）
void First_player3(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//先手函数（加保护、加弧线打定）
void First_player4(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//先手函数（加保护、加弧线打定、前置线）
void First_player5(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//先手函数（在4的基础上加入推壶和打一个离中心比对方壶近的壶）
void Second_player (const GAMESTATE* const gs, SHOTINFO* vec_ret);									//后手函数
void Second_player2(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//后手函数
void Second_player3(const GAMESTATE* const gs, SHOTINFO* vec_ret);								//后手函数(2的基础上加入弧线撞球)
void Second_player4(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//后手函数(在3的基础上改动3,4壶的策略)
void Second_player5(const GAMESTATE* const gs, SHOTINFO* vec_ret);									//后手函数(后手函数(在4的基础上修改推壶策略))

void Second_player_3_lpy(const GAMESTATE* const gs, SHOTINFO* vec_ret);
void First_player_lpy(const GAMESTATE* const gs, SHOTINFO* vec_ret);
