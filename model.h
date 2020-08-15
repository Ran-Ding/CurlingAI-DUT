#pragma once
#include "main.h"


//       angle  _   0    _   10    _    a  ;
//             符号：0 +   角速度      ax+by+c=0
//                   1 -
//右偏 10  坐标函数：y=13.024x+8.73;   速度与位移函数：S=9.193v-9.24;	S^2=pow(x,2) + pow(y-8.73,2)
static const float angle_0_10_a = 13.024;
static const float angle_0_10_b = -1;
static const float angle_0_10_c = 8.73;
static const float angle_0_10_k = 9.193;
static const float angle_0_10_v = 9.24;
//左偏-10  坐标函数：y=-13.029x+8.09;  速度与位移函数：S=9.19v-8.6;     S^2=pow(x,2) + pow(y-8.09,2)
static const float angle_1_10_a = -13.029;
static const float angle_1_10_b = -1;
static const float angle_1_10_c = 8.09;
static const float angle_1_10_k = 9.19;
static const float angle_1_10_v = 8.6;
//右偏 5   坐标函数：y=25.304x+9.48;   速度与位移函数：S=9.06v-9.17;    S^2=pow(x,2) + pow(y-9.48,2)
static const float angle_0_5_a = 25.304;
static const float angle_0_5_b = -1;
static const float angle_0_5_c = 9.48;
static const float angle_0_5_k = 9.06;
static const float angle_0_5_v = 9.17;
//左偏-5   坐标函数：y=-25.086x+8.4;   速度与位移函数：S=9.073v-8.13;   S^2=pow(x,2) + pow(y-8.4,2)
static const float angle_1_5_a = -25.086;
static const float angle_1_5_b = -1;
static const float angle_1_5_c = 8.4;
static const float angle_1_5_k = 9.073;
static const float angle_1_5_v = 8.13;
//直线球 速度与坐标关系 v=3.5388-0.1111y
static const float straight_line_k = -0.1111;
static const float straight_line_b = 3.5388;

Status zuopian_ten  (float x, float y, SHOTINFO* pian);									//左偏函数  角速度-10   弧形球
Status youpian_ten  (float x, float y, SHOTINFO* pian);								    //右偏函数  角速度 10   弧形球
Status zuopian_five (float x, float y, SHOTINFO* pian);					     			//左偏函数  角速度-10   弧形球
Status youpian_five (float x, float y, SHOTINFO* pian);									//右偏函数  角速度 10   弧形球
void   straight_line(float x, float y, SHOTINFO* pian);									//直线球    角速度 0


int    centerline_seek(const GAMESTATE* const gs);									    //寻找离中线最近的壶
int    distance_seek(const GAMESTATE* const gs);										//寻找离营中心最近的壶
int    centerline_x_seek(float x, float y, const GAMESTATE* const gs);					//寻找在某x坐标这条线上的冰壶
int    Play_a_closer_ball(const GAMESTATE* const gs, SHOTINFO* vec_ret);                //打一个离营中心更近的冰壶而且这个冰壶要有保护
int    Play_a_closer_ball2(const GAMESTATE* const gs, SHOTINFO* vec_ret);			    //打一个离营中心更近的冰壶而且这个冰壶要有保护，y动态选择(3.08~6.68)
int	   Play_a_closer_ball3(const GAMESTATE* const gs, SHOTINFO* vec_ret);					//打一个比对方壶离营中心更近的冰壶但不一定有保护，y动态选择(3.08~6.68),x动态选择（0.575~4.175）


float  Distance_from_point_to_line(float x, float y, float a, float b, float c);		//点到直线的距离函数

void   Path_occlusion_judgment1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);      //路径遮挡判断

Status Path_occlusion_judgment_zuoten_d(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);	//路径遮挡判断(左偏10弧线打定)
Status Path_occlusion_judgment_youten_d(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);	//路径遮挡判断(右偏10弧线打定)
Status Path_occlusion_judgment_zuoten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);//路径遮挡判断(左偏10弧线)
Status Path_occlusion_judgment_youten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);//路径遮挡判断(右偏10弧线)
Status Hit1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);		//撞壶
Status Hit2(const GAMESTATE* const gs, SHOTINFO* vec_ret);								//撞壶，清中线
Status Hit3(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);		//撞壶(Hit1改进，加入弧线撞球)
Status Hit_zuoten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);//撞壶(左偏10度打定)
Status Hit_youten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);//撞壶(右偏10度打定)

Status Protect_First(const GAMESTATE* const gs, SHOTINFO* vec_ret);						//判断自己的壶是否离中心最近，如果是则保护，返回OK,否则返回ERROR
Status Protect_First2(const GAMESTATE* const gs, SHOTINFO* vec_ret);					//判断自己的壶是否离中心最近，如果是,且没有保护则加保护，返回OK,否则返回ERROR

Status AddBall(const GAMESTATE* const gs, SHOTINFO* vec_ret);						//

Status Push1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret);	//推壶
void dashuai(const GAMESTATE* const gs, SHOTINFO* vec_ret, int target);