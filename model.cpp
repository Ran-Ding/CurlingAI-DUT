#include "main.h"


/*
函数名：youpian_five
功能：  右偏定点打弧线球 角速度5   坐标函数：y=25.304x+9.48;  速度与位移函数：S=9.06v-9.17;    S^2=pow(x,2) + pow(y-9.48,2)
输入：  float x, float y, SHOTINFO* pian 坐标x,y;结构体SHOTINFO
返回值：无
*/
Status youpian_five(float x, float y, SHOTINFO* pian)
{
	double x1, y1, hx, s, v, z;
	x1 = x - 2.375;
	y1 = 32.48 - y;
	hx = x1 - (((-0.66990283806838113 + -3.8047861043220088 * (2.0 / (1.0 + exp(-2.0 *
		(-0.19527782155882262 + -0.27468770799693881 * ((y1 - 22.4027) *
			0.291902621285539 + -1.0)))) - 1.0)) - -1.0) / 7.33137829912024 + 0.5036);
	
	s = pow(x1, 2) + pow(y1 - 15.189345, 2);
	z = pow(s, 0.5);
	v = ((5.6138636236889861 + -13.286527011944949 * (2.0 / (1.0 + exp(-2.0 *
		(0.45388348160066461 + -0.092550206426514042 * ((z - 7.231199738)
			* 0.291753737627811 + -1.0)))) - 1.0)) - -1.0) / 2.66666666666667 + 2.45;
	pian->speed = v;
	pian->h_x = hx;
	pian->angle = 5.0f;	
	if (hx > 2.23)
	{
		pian->h_x = 2.23;
		return ERROR;
	}
	if (hx < -2.23)
	{
		pian->h_x = -2.23;
		return ERROR;
	}
	return OK;
}

/*
函数名：youpian_ten
功能：  右偏定点打弧线球 角速度10   坐标函数：y=13.024x+8.73;  速度与位移函数：S=9.193v-9.24;    S^2=pow(x,2) + pow(y-8.73,2)
输入：  float x, float y, SHOTINFO* pian 坐标x,y;结构体SHOTINFO
返回值：无
*/
Status youpian_ten(float x, float y, SHOTINFO* pian)
{
	double x1, y1, hx, s, v, z;
	x1 = x - 2.375;
	y1 = 32.48 - y;
	hx = x1 - (((-0.8828525817916193 + 5.128344700742173 * (2.0 / (1.0 + exp(-2.0 *
		(0.18151238071735168 + 0.20121139965957194 * ((y1 - 22.3137) *
			0.308765862846204 + -1.0)))) - 1.0)) - -1.0) / 3.98168425243878 + 1.0345);
	
	s = pow(x1, 2) + pow(y1 - 13.456803, 2);
	z = pow(s, 0.5);
	v = ((4.85843523937053 + 14.126793469236782 * (2.0 / (1.0 + exp(-2.0 *
		(-0.36167954368976934 + 0.081480051406872325 * ((z - 8.91710798) *
			0.307976332942742 + -1.0)))) - 1.0)) - -1.0) / 2.85714285714286 + 2.5;

	pian->speed = v;
	pian->h_x = hx;
	pian->angle = 10.0f;
	if (hx > 2.23)
	{
		pian->h_x = 2.23;
		return ERROR;
	}
	if (hx < -2.23)
	{
		pian->h_x = -2.23;
		return ERROR;
	}
	return OK;
}


/*
函数名：zuopian_five
功能：  左偏定点打弧线球 角速度-5    坐标函数：y=-25.086x+8.4;  速度与位移函数：S=9.073v-8.13;    S^2=pow(x,2) + pow(y-8.4,2)
输入：  float x, float y, SHOTINFO* pian 坐标x,y;结构体SHOTINFO
返回值：无
*/
Status zuopian_five(float x, float y, SHOTINFO* pian)
{
	double x1, y1, hx, s, v, z;
	x1 = x - 2.375;
	y1 = 32.48 - y;
	hx = x1 - (((1.5175946488306373 + 5.5105727954427444 * (2.0 / (1.0 + exp(-2.0 *
		(-0.29301235117212115 + -0.19698289077961884 * ((y1 - 22.369) *
		0.290423291948014 + -1.0)))) - 1.0)) - -1.0) / 7.23065798987708 + -0.8281);
	s = pow(x1, 2) + pow(y1 - 13.931251, 2);
	z = pow(s, 0.5);
	v = ((1.5601980055132121 + -6.0516893762426518 * (2.0 / (1.0 + exp(-2.0 *
		(0.27087004688829269 + -0.18084122004675371 * ((z - 8.455753097) *
			0.29023977674891 + -1.0)))) - 1.0)) - -1.0) / 2.66666666666667 + 2.45;

	pian->speed = v;
	pian->h_x = hx;
	pian->angle = -5.0f;
	if (hx > 2.23)
	{
		pian->h_x = 2.23;
		return ERROR;
	}
	if (hx < -2.23)
	{
		pian->h_x = -2.23;
		return ERROR;
	}
	return OK;
}
/*
函数名：zuopian_ten
功能：  左偏定点打弧线球 角速度-10   坐标函数：y=-13.029x+8.09;  速度与位移函数：S=9.19v-8.6;    S^2=pow(x,2) + pow(y-8.09,2)
输入：  float x, float y, SHOTINFO* pian 坐标x,y;结构体SHOTINFO
返回值：无
*/
Status zuopian_ten(float x, float y, SHOTINFO* pian)
{
	double x1, y1, hx, s, v, z;
	x1 = x - 2.375;
	y1 = 32.48 - y;
	hx = x1 - (((3.5395847264689917 + 8.5807290454229239 * (2.0 / (1.0 + exp(-2.0 *
		(-0.44786916506064173 + -0.1405137550267731 * ((y1 - 22.2743) *
			0.308522946394138 + -1.0)))) - 1.0)) - -1.0) / 3.97377309755613 + -1.5781);
	
	s = pow(x1, 2) + pow(y1 - 8.741963, 2);
	z = pow(s, 0.5);
	v = ((0.598216836310407 + -3.6807372786138632 * (2.0 / (1.0 + exp(-2.0 *
		(0.17960302391178926 + -0.28611947959297412 * ((z - 13.57495266) *
			0.307597578049263 + -1.0)))) - 1.0)) - -1.0) / 2.85714285714286 + 2.5;

	pian->speed = v;
	pian->h_x = hx;
	pian->angle = -10.0f;
	if (hx > 2.23)
	{
		pian->h_x = 2.23;
		return ERROR;
	}
	if (hx < -2.23)
	{
		pian->h_x = -2.23;
		return ERROR;
	}
	return OK;
}

/*
函数名：straight_line
功能：  定点打直线球
输入：  float x, float y, SHOTINFO* pian 定点坐标x,y;结构体SHOTINFO
返回值：无
*/
void straight_line(float x, float y, SHOTINFO* pian)
{
	float v;
	v = straight_line_k * y + straight_line_b;
	pian->speed = v;
	pian->h_x = x - 2.375;
	pian->angle = 0.0f;
}


/*
函数名：distance_seek
功能：	寻找离营中心最近的壶
输入：	GAMESTATE* const gs；结构体GAMESTATE
返回值：离营中心最近的壶的序号
*/
int distance_seek(const GAMESTATE* const gs)
{
	int i;
	int a = 0;
	for (i = 0; i < gs->ShotNum; i++)
	{
		if (get_dist(gs->body[i][0], gs->body[i][1]) < get_dist(gs->body[a][0], gs->body[a][1]))
			a = i;
	}
	return a;
}

/*
函数名：distance_seek
功能：	寻找离中线最近的壶
输入：	GAMESTATE* const gs；结构体GAMESTATE
返回值：离中线最近的壶的序号
*/
int centerline_seek(const GAMESTATE* const gs)
{
	int i;
	int a = 0;
	for (i = 0; i < gs->ShotNum; i++)
	{
		if (fabs(gs->body[i][0] - 2.375) < fabs(gs->body[a][0] - 2.375))
			a = i;
	}
	return a;
}

/*
函数名：centerline_x_seek
功能：	寻找离某x坐标这条线最近的冰壶,且纵坐标要大于y
输入：	float x, float y, const GAMESTATE* const gs；坐标x y ,结构体GAMESTATE
返回值：壶的序号
*/
int centerline_x_seek(float x, float y, const GAMESTATE* const gs)
{
	int i;
	int a = 0;
	for (i = 0; i < gs->ShotNum; i++)
	{
		if ((fabs(gs->body[i][0] - x) < fabs(gs->body[a][0] - x)) && (gs->body[i][1] > y))
			a = i;
	}
	return a;
}


/*
函数名：Path_occlusion_judgment1
功能：	路径遮挡判断(直线优先)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞或者靠近的冰壶的序号（目标冰壶）,若是定点打w=16;
返回值：无
*/
void Path_occlusion_judgment1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //是否有遮挡标志位  1：有遮挡
	int st;
	int j = 0;
	int i = 0;
	for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
	{
		if ((fabs(gs->body[i][0] - x) < 0.3) && (i != w) && (gs->body[i][1] > y))
			//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方（目标冰壶：要击飞或者靠近的冰壶）
		{
			flag = 1;
			flag1[j++] = i;
		}
	}
	if (flag == 0)   //直线球无遮挡
	{
		straight_line(x, y, vec_ret);
		direction_flag = 0;
	}
	else            //直线球有遮挡
	{
		if (x > 2.375)   //如果目标冰壶在大本营右方（从发球点看），优先选择两个左偏函数
		{
			flag = 0;
			st = zuopian_five(x, y, vec_ret);     //左偏定点打弧线球 角速度-5 路径
			if (st == OK)
			{
				for (i = 0; i < gs->ShotNum; i++)
				{
					if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_5_a, angle_1_5_b, (angle_1_5_c - angle_1_5_a * vec_ret->h_x)) < 0.32
						&& (i != w) && (gs->body[i][1] > y))
						//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
					{
						flag = 1;
					}
				}
				direction_flag = -5;
			}
			else
				flag = 1;

			if (flag != 0)   // 左偏定点打弧线球 角速度-5 路径上有遮挡
			{
				flag = 0;
				st = zuopian_ten(x, y, vec_ret);  //左偏定点打弧线球 角速度-10 路径
				if (st == OK)
				{
					for (i = 0; i < gs->ShotNum; i++)
					{
						if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_10_a, angle_1_10_b, angle_1_10_c - angle_1_10_a * vec_ret->h_x) < 0.32
							&& (i != w) && (gs->body[i][1] > y))
							//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
						{
							flag = 1;
						}
					}
					direction_flag = -10;
				}
				else
					flag = 1;
				if (flag != 0) //左偏定点打弧线球 角速度-10 路径上有遮挡
				{
					flag = 0;
					st = youpian_five(x, y, vec_ret);     //右偏定点打弧线球 角速度5 路径
					if (st == OK)
					{
						for (i = 0; i < gs->ShotNum; i++)
						{
							if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_5_a, angle_0_5_b, angle_0_5_c - angle_0_5_a * vec_ret->h_x) < 0.32
								&& (i != w) && (gs->body[i][1] > y))
								//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
							{
								flag = 1;
							}
						}
						direction_flag = 5;
					}
					else
						flag = 1;
					if (flag != 0) //右偏定点打弧线球 角速度5 路径上有遮挡
					{
						flag = 0;
						st = youpian_ten(x, y, vec_ret);  //右偏定点打弧线球 角速度10 路径
						if (st == OK)
						{
							for (i = 0; i < gs->ShotNum; i++)
							{
								if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x) < 0.32
									&& (i != w) && (gs->body[i][1] > y))
									//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
								{
									flag = 1;
								}
							}
							direction_flag = 10;
						}
						else
							flag = 1;
						if (flag != 0) //右偏定点打弧线球 角速度10 路径上有遮挡
						{
							///////////////////////////////////////////////////////////////////////////////////////
							direction_flag = 1;
						}
					}
				}
			}
		}
		else             //如果目标冰壶在大本营左方（从发球点看），优先选择两个右偏函数
		{
			flag = 0;
			st = youpian_five(x, y, vec_ret);     //右偏定点打弧线球 角速度5 路径
			if (st == OK)
			{
				for (i = 0; i < gs->ShotNum; i++)
				{
					if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_5_a, angle_0_5_b, angle_0_5_c - angle_0_5_a * vec_ret->h_x) < 0.32
						&& (i != w) && (gs->body[i][1] > y))
						//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
					{
						flag = 1;
					}
				}
				direction_flag = 5;
			}
			else
				flag = 1;
			if (flag != 0) //右偏定点打弧线球 角速度5 路径上有遮挡
			{
				flag = 0;
				st = youpian_ten(x, y, vec_ret);  //右偏定点打弧线球 角速度10 路径
				if (st == OK)
				{
					for (i = 0; i < gs->ShotNum; i++)
					{
						if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x) < 0.32
							&& (i != w) && (gs->body[i][1] > y))
							//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
						{
							flag = 1;
						}
					}
					direction_flag = 10;
				}
				else
					flag = 1;
				if (flag != 0) //右偏定点打弧线球 角速度10 路径上有遮挡
				{
					flag = 0;
					st = zuopian_five(x, y, vec_ret);     //左偏定点打弧线球 角速度-5 路径
					if (st == OK)
					{
						for (i = 0; i < gs->ShotNum; i++)
						{
							if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_5_a, angle_1_5_b, angle_1_5_c - angle_1_5_a * vec_ret->h_x) < 0.32
								&& (i != w) && (gs->body[i][1] > y))
								//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
							{
								flag = 1;
							}
						}
						direction_flag = -5;
					}
					else
						flag = 1;
					if (flag != 0)   //左偏定点打弧线球 角速度-5 路径上有遮挡
					{
						flag = 0;
						st = zuopian_ten(x, y, vec_ret);  //左偏定点打弧线球 角速度-10 路径
						if (st == OK)
						{
							for (i = 0; i < gs->ShotNum; i++)
							{
								if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_10_a, angle_1_10_b, angle_1_10_c - angle_1_10_a * vec_ret->h_x) < 0.32
									&& (i != w) && (gs->body[i][1] > y))
									//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
								{
									flag = 1;
								}
							}
							direction_flag = -10;
						}
						else
							flag = 1;
						if (flag != 0) //左偏定点打弧线球 角速度-10 路径上有遮挡
						{
							/////////////////////////////////////////////////////////////////////////////////
							direction_flag = -1;
						}
					}
				}
			}
		}
	}
}



/*
函数名：Path_occlusion_judgment_zuoten_d
功能：	路径遮挡判断(左偏10弧线打定)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞或者靠近的冰壶的序号（目标冰壶）,若是定点打w=16;
返回值：无
*/
Status Path_occlusion_judgment_zuoten_d(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int st;
	int i = 0;
	double distance; //该y坐标下两曲线的距离,
					 //把三条曲线1(原曲线) 2(加上速度4之后的实际曲线) 3(考虑横向偏移改变后的曲线) 近似为直线，
					 //发球点2 3曲线相交，终点1 2曲线相交，1 3 曲线在任意位置有恒定距离差0.53
					 //所以有某个y坐标下1 2 曲线的距离为 0.53 * ((32.48-gs->body[w][1]) - (32.48-y)) / (32.48-gs->body[w][1]);
	st = zuopian_ten(x, y, vec_ret);  //右偏定点打弧线球 角速度10 路径
	if (st == OK)
	{
		for (i = 0; i < gs->ShotNum; i++)
		{
			//通过判断同一个y坐标下的x的大小，可以知道该点在运动轨迹的哪一侧,左偏大于在外侧，右偏小于在外侧
			if ((gs->body[i][0] - 2.375) > ((((32.48 - gs->body[i][1]) - angle_1_10_c) / angle_1_10_a) + vec_ret->h_x))    //该点在运动轨迹外侧
			{
				distance = 0.53 * ((32.48 - gs->body[w][1]) - (32.48 - gs->body[i][1])) / (32.48 - gs->body[w][1]);
				if ((Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_10_a, angle_1_10_b, angle_1_10_c - angle_1_10_a * vec_ret->h_x) + distance) < 0.3
					&& (i != w) && (gs->body[i][1] > y))
					//与点到直线的距离小于0.35且该冰壶不是目标冰壶并且不在目标冰壶的后方
				{
					return ERROR;
				}
			}
			else  //该点在运动轨迹内侧
			{
				distance = 0.53 * ((32.48 - gs->body[w][1]) - (32.48 - gs->body[i][1])) / (32.48 - gs->body[w][1]);
				if ((Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_10_a, angle_1_10_b, angle_1_10_c - angle_1_10_a * vec_ret->h_x) - distance) < 0.3
					&& (i != w) && (gs->body[i][1] > y))
					//与点到直线的距离小于0.35且该冰壶不是目标冰壶并且不在目标冰壶的后方
				{
					return ERROR;
				}
			}
		}
		return OK;
	}
	else
		return ERROR;
}



/*
函数名：Path_occlusion_judgment_youten_d
功能：	路径遮挡判断(右偏10弧线打定)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞或者靠近的冰壶的序号（目标冰壶）,若是定点打w=16;
返回值：无
*/
Status Path_occlusion_judgment_youten_d(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int st;
	int i = 0;
	float a;
	double distance; //该y坐标下两曲线的距离,
					 //把三条曲线1(原曲线) 2(加上速度4之后的实际曲线) 3(考虑横向偏移改变后的曲线) 近似为直线，
					 //发球点2 3曲线相交，终点1 2曲线相交，1 3 曲线在任意位置有恒定距离差0.53
					 //所以有某个y坐标下1 2 曲线的距离为 0.53 * ((32.48-gs->body[w][1]) - (32.48-y)) / (32.48-gs->body[w][1]);

	st = youpian_ten(x, y, vec_ret);  //右偏定点打弧线球 角速度10 路径
	if (st == OK)
	{
		for (i = 0; i < gs->ShotNum; i++)
		{
			//通过判断同一个y坐标下的x的大小，可以知道该点在运动轨迹的哪一侧,左偏大于在外侧，右偏小于在外侧
			if ((gs->body[i][0] - 2.375) < ((((32.48 - gs->body[i][1]) - angle_0_10_c) / angle_0_10_a) + vec_ret->h_x))    //该点在运动轨迹外侧
			{
				distance = 0.53 * ((32.48 - gs->body[w][1]) - (32.48 - gs->body[i][1])) / (32.48 - gs->body[w][1]);
				if ((Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x) + distance) < 0.3
					&& (i != w) && (gs->body[i][1] > y))
					//与点到直线的距离小于0.35且该冰壶不是目标冰壶并且不在目标冰壶的后方
				{
					return ERROR;
				}
			}
			else      //该点在运动轨迹内侧
			{
				distance = 0.53 * ((32.48 - gs->body[w][1]) - (32.48 - gs->body[i][1])) / (32.48 - gs->body[w][1]);
				if ((Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x) - distance) < 0.3
					&& (i != w) && (gs->body[i][1] > y))
					//与点到直线的距离小于0.35且该冰壶不是目标冰壶并且不在目标冰壶的后方
				{
					a = Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x);
					return ERROR;
				}
			}
		}
		return OK;
	}
	else
		return ERROR;
}




/*
函数名：Path_occlusion_judgment_zuoten
功能：	路径遮挡判断(左偏10弧线)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞或者靠近的冰壶的序号（目标冰壶）,若是定点打w=16;
返回值：无
*/
Status Path_occlusion_judgment_zuoten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //是否有遮挡标志位  1：有遮挡
	int st;
	int i = 0;
	st = zuopian_ten(x, y, vec_ret);  //左偏定点打弧线球 角速度-10 路径
	if (st == OK)
	{
		for (i = 0; i < gs->ShotNum; i++)
		{
			if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_1_10_a, angle_1_10_b, angle_1_10_c - angle_1_10_a * vec_ret->h_x) < 0.32
				&& (i != w) && (gs->body[i][1] > y))
				//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
			{
				flag = 1;
				return ERROR;
			}
		}
		return OK;
	}
	else
		return ERROR;
}


/*
函数名：Path_occlusion_judgment_youten
功能：	路径遮挡判断(右偏10弧线)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞或者靠近的冰壶的序号（目标冰壶）,若是定点打w=16;
返回值：无
*/
Status Path_occlusion_judgment_youten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int st;
	int i = 0;
	st = youpian_ten(x, y, vec_ret);  //右偏定点打弧线球 角速度10 路径
	if (st == OK)
	{
		for (i = 0; i < gs->ShotNum; i++)
		{
			if (Distance_from_point_to_line(gs->body[i][0], gs->body[i][1], angle_0_10_a, angle_0_10_b, angle_0_10_c - angle_0_10_a * vec_ret->h_x) < 0.32
				&& (i != w) && (gs->body[i][1] > y))
				//与点到直线的距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方
			{
				return ERROR;
			}
		}
		return OK;
	}
	else
		return ERROR;
}

/*
函数名：Distance_from_point_to_line
功能：	点到直线的距离函数
输入：	float x, float y, float a, float b, float c   x,y为点的坐标； 直线为ax+by+c=0;
返回值：距离
*/
float Distance_from_point_to_line(float x, float y, float a, float b, float c)
{
	float x1 = x - 2.375;
	float y1 = 32.48 - y;
	float w;
	w= abs(a * x1 + b * y1 + c) / sqrt(pow(a, 2) + pow(b, 2));
	return abs(a * x1 + b * y1 + c) / sqrt(pow(a, 2) + pow(b, 2));
}

/*
函数名：Hit1
功能：	撞壶
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞的冰壶的序号（目标冰壶）;
返回值：无
*/
Status Hit1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //遮挡个数
	int rflag = 0;	//第二次筛选
	int Occ[16] = { 20 };
	int rOcc[16] = { 20 };
	int tg;			//靶子

	int j = 0;
	int i;
	for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
	{
		if ((fabs(gs->body[i][0] - x) < 0.31) && (i != w) && (gs->body[i][1] > y))
			//与x距离小于0.31且该冰壶不是目标冰壶并且不在目标冰壶的后方（目标冰壶：要击飞的冰壶）
		{
			flag += 1;
			Occ[j++] = i;

		}
	}
	if (flag == 0)   //直线球无遮挡,打定
	{
		straight_line(x, y, vec_ret);
		vec_ret->speed += 5;
		return OK;
	}
	else if (flag == 1)
	{
		if ((fabs(gs->body[Occ[0]][0] - x) < 0.2) && (i != w) && (gs->body[Occ[0]][1] > (y + 0.2)))//前方有一个壶挡着，就打这个壶
		{
			straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
			if (Occ[0] % 2 != gs->ShotNum % 2)	//对方的壶
				vec_ret->speed += 9;
			else
				vec_ret->speed += 4;
			return OK;
		}
		else
		{
			if (gs->body[Occ[0]][0] > x)			//挡的壶靠右，往左打
				straight_line(x - 0.08, y, vec_ret);
			else
				straight_line(x + 0.08, y, vec_ret);
			vec_ret->speed += 5;
			return OK;
		}

	}
	else
	{
		j = 0;
		for (i = 0; i < flag; i++)
		{
			if ((fabs(gs->body[Occ[i]][0] - x) < 0.2) && (i != w) && (gs->body[Occ[i]][1] > (y + 0.2)))
			{
				rflag += 1;
				rOcc[j++] = Occ[i];
			}
		}
		if (rflag != 0)
		{
			tg = rOcc[0];
			for (i = 0; i < rflag; i++)
				if (gs->body[rOcc[i]][1] > gs->body[tg][1])	//寻找距离发球点最近的壶
					tg = rOcc[i];
			straight_line(gs->body[tg][0], gs->body[tg][1], vec_ret);
			if (tg % 2 != gs->ShotNum % 2)	//对方的壶
				vec_ret->speed += 9;
			else
				vec_ret->speed += 5;
			return OK;
		}
		else
		{
			Path_occlusion_judgment1(w, x, y, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				straight_line(x, y, vec_ret);
				vec_ret->speed += 8;			//没有找到其他好的方法了，直线开撞
				return ERROR;
			}
			else
			{
				vec_ret->speed += 0.5;
				return OK;
			}
		}

	}
}

/*
函数名：Hit2
功能：	撞壶（清中线）
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret  结构体GAMESTATE,SHOTINFO  ;
返回值：OK(成功清线) or ERROR
*/
Status Hit2(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //遮挡个数
	int Occ[16] = { 20 };
	int tg;			//靶子
	float len;		//距离
	int j = 0;
	int i;
	for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
	{
		if ((fabs(gs->body[i][0] - TEE_X) < 0.3) && gs->body[i][1] > 4.5 && gs->body[i][1] < (Fline-0.1))
			//与中心线距离小于0.32且在前掷线与大本营中心之间
		{
			flag += 1;
			Occ[j++] = i;

		}
	}
	if (flag == 0)   //中线无遮挡,无需开路
	{
		printf("中线无遮挡,无需开路!\n");
		return ERROR;
	}
	else if (flag == 1)
	{
		if (is_in_House(gs->body[Occ[0]][0], gs->body[Occ[0]][1]) == true)//在大本营中
		{
			if (Occ[0] % 2 != gs->ShotNum % 2)	//对方的壶，打定
			{
				straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
				vec_ret->speed += 5;
				return OK;
			}
			else
			{
				printf("自己的壶暂不处理！\n");
				return ERROR;
			}
		}
		else
		{
			if (Occ[0] % 2 != gs->ShotNum % 2)
			{
				if (gs->body[Occ[0]][0] > 2.375)			//挡的壶靠右，往右推zuopian_ten
					youpian_ten(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
				else
					zuopian_ten(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
				vec_ret->speed += 0.5;
				//return OK;
				return ERROR;   //只有一壶暂不处理
			}
			else											//自己的壶往前推
			{
				printf("自己的壶往前推！\n");
				len = gs->body[Occ[0]][1] - 4.88;
				len = len / 0.3;
				straight_line(gs->body[Occ[0]][0], (gs->body[Occ[0]][1] - len), vec_ret);
				return OK;
				//return ERROR; //只有一壶暂不处理
			}
		}

	}
	else                                               //直线上不只一个壶
	{
		tg = Occ[0];
		for (i = 0; i < flag; i++)
			if (gs->body[Occ[i]][1] > gs->body[tg][1])	//寻找距离发球点最近的壶
				tg = Occ[i];
		straight_line(gs->body[tg][0], gs->body[tg][1], vec_ret);
		if (tg % 2 != gs->ShotNum % 2)	//对方的壶
			vec_ret->speed += 9;
		else
			vec_ret->speed += 5;
		return OK;
	}

}

/*
函数名：Hit3
功能：	撞壶(Hit1改进，加入弧线撞球)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞的冰壶的序号（目标冰壶）;
返回值：无
*/
Status Hit3(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //遮挡个数
	int rflag = 0;	//第二次筛选
	int rrflag = 0;	//第三次筛选
	int Occ[16] = { 20 };
	int rOcc[16] = { 20 };
	int rrOcc[16] = { 20 };
	int tg;			//靶子

	int j = 0;
	int i=0;
	for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
	{
		if ((fabs(gs->body[i][0] - x) < 0.31) && (i != w) && (gs->body[i][1] > y))
			//与x距离小于0.31且该冰壶不是目标冰壶并且不在目标冰壶的后方（目标冰壶：要击飞的冰壶）
		{
			flag += 1;
			Occ[j++] = i;

		}
	}
	if (flag == 0)   //直线球无遮挡,打定
	{
		straight_line(x, y, vec_ret);
		vec_ret->speed += 5;
		return OK;
	}
	else if (flag == 1)
	{
		if ((fabs(gs->body[Occ[0]][0] - x) < 0.2) && (i != w) && (gs->body[Occ[0]][1] > (y + 0.2))&& (gs->body[Occ[0]][1] < (y + 2)))//前方有一个壶挡着，就打这个壶
		{
			straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
			if (Occ[0] % 2 != gs->ShotNum % 2)	//对方的壶
				vec_ret->speed += 9;
			else
				vec_ret->speed += 4;
			return OK;
		}
		else
		{
			if (Hit_zuoten(w, x, y, gs, vec_ret) == ERROR)
			{
				if (Hit_youten(w, x, y, gs, vec_ret) == ERROR)
				{
					if (fabs(gs->body[Occ[0]][0] - x) < 0.2)
					{
						straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
						if (Occ[0] % 2 != gs->ShotNum % 2)	//对方的壶
							vec_ret->speed += 9;
						else
							vec_ret->speed += 4;
						return OK;
					}
					else
					{
						if (gs->body[Occ[0]][0] > x)			//挡的壶靠右，往左打
							straight_line(x - 0.08, y, vec_ret);
						else
							straight_line(x + 0.08, y, vec_ret);
						vec_ret->speed += 5;
						return OK;
					}

				}
			}

			return OK;
		}

	}
	else
	{
		j = 0;
		for (i = 0; i < flag; i++)
		{
			if ((fabs(gs->body[Occ[i]][0] - x) < 0.2) && (i != w) && (gs->body[Occ[i]][1] > (y + 0.2)))
			{
				rflag += 1;
				rOcc[j++] = Occ[i];
			}
		}
		if (rflag != 0)
		{
			j = 0;
			for (i = 0; i < rflag; i++)
			{
				if (gs->body[rOcc[i]][1] > (y + 2))
				{
					rrflag += 1;
					rrOcc[j++] = rOcc[i];
				}
			}
			if (rrflag > 0)
			{
				if (Hit_youten(w, x, y, gs, vec_ret) == ERROR)
				{
					if (Hit_zuoten(w, x, y, gs, vec_ret) == ERROR)
					{
						tg = rOcc[0];
						for (i = 0; i < rflag; i++)
							if (gs->body[rOcc[i]][1] > gs->body[tg][1])	//寻找距离发球点最近的壶
								tg = rOcc[i];
						straight_line(gs->body[tg][0], gs->body[tg][1], vec_ret);
						if (tg % 2 != gs->ShotNum % 2)	//对方的壶
							vec_ret->speed += 9;
						else
							vec_ret->speed += 6;
						return OK;
					}
				}
				return OK;
			}
			else
			{
				tg = rOcc[0];
				for (i = 0; i < rflag; i++)
					if (gs->body[rOcc[i]][1] > gs->body[tg][1])	//寻找距离发球点最近的壶
						tg = rOcc[i];
				straight_line(gs->body[tg][0], gs->body[tg][1], vec_ret);
				if (tg % 2 != gs->ShotNum % 2)	//对方的壶
					vec_ret->speed += 9;
				else
					vec_ret->speed += 5;
				return OK;
			}

		}
		else
		{
			if (Hit_youten(w, x, y, gs, vec_ret) == ERROR)
			{
				if (Hit_zuoten(w, x, y, gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(w, x, y, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						straight_line(x, y, vec_ret);
						vec_ret->speed += 8;			//没有找到其他好的方法了，直线开撞
						return ERROR;
					}
					else
					{
						vec_ret->speed += 0.6;
						return ERROR;
					}
				}
			}
			return OK;

		}

	}
	return ERROR;		//以防万一
}


/*
函数名：Hit_zuoten
功能：	撞壶(左偏10度打定)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞的冰壶的序号（目标冰壶）;
返回值：无
*/
Status Hit_zuoten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{

	if (Path_occlusion_judgment_zuoten_d(w, x, y, gs, vec_ret) == OK)
	{
		vec_ret->speed += 4;
		vec_ret->h_x -= 0.53;
		return OK;
	}
	else
	{
		//if (Path_occlusion_judgment_zuoten_d(w, x - 0.01, y + 0.03, gs, vec_ret) == OK)
		//{
		//	vec_ret->speed += 4;
		//	vec_ret->h_x -= 0.53;
		//	return OK;
		//}
		//else
		//{
		//	if (Path_occlusion_judgment_zuoten_d(w, x - 0.02, y + 0.05, gs, vec_ret) == OK)
		//	{
		//		vec_ret->speed += 4;
		//		vec_ret->h_x -= 0.53;
		//		return OK;
		//	}
		//	else
		//	{
				return ERROR;
//			}
//		}
	}
}


/*
函数名：Hit_youten
功能：	撞壶(右偏10度打定)
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞的冰壶的序号（目标冰壶）;
返回值：无
*/
Status Hit_youten(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{

	if (Path_occlusion_judgment_youten_d(w, x, y, gs, vec_ret) == OK)
	{
		vec_ret->speed += 4;
		vec_ret->h_x += 0.53;
		return OK;
	}
	else
	{
		//if (Path_occlusion_judgment_youten_d(w, x + 0.01, y + 0.03, gs, vec_ret) == OK)
		//{
		//	vec_ret->speed += 4;
		//	vec_ret->h_x += 0.53;
		//	return OK;
		//}
		//else
		//{
		//	if (Path_occlusion_judgment_youten_d(w, x + 0.02, y + 0.05, gs, vec_ret) == OK)
		//	{
		//		vec_ret->speed += 4;
		//		vec_ret->h_x += 0.53;
		//		return OK;
		//	}
		//	else
		//	{
				return ERROR;
		//	}
		//}
	}
}



/*
函数名：Play_a_closer_ball
功能：	打一个离营中心更近的冰壶而且这个冰壶要有保护，打在y等于3.5的位置
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：int    1：可以打出这样一个冰壶
*/
int Play_a_closer_ball(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int a;
	int flag = 0;
	int i;
	a = 0;
	for (i = 0; i < gs->ShotNum; i++)
	{
		if ((abs(gs->body[i][0] - 2.375) < 1.3) && (gs->body[i][1] > 5.68)) // 5.68=4.88+0.8
		{
			if (gs->body[i][0] > 2.375)
			{
				if (get_dist(gs->body[i][0] - 0.145, 3.5) < get_dist(gs->body[a][0], gs->body[a][1]))
				{
					Path_occlusion_judgment1(16, gs->body[i][0] - 0.145, 3.5, gs, vec_ret);
					if (fabs(direction_flag) != 1)      //路径无遮挡
					{
						a = i;
						flag = 1;
					}

				}
			}
			else
			{
				if (get_dist(gs->body[i][0] + 0.145, 3.5) < get_dist(gs->body[a][0], gs->body[a][1]))
				{
					Path_occlusion_judgment1(16, gs->body[i][0] + 0.145, 3.5, gs, vec_ret);
					if (fabs(direction_flag) != 1)      //路径无遮挡
					{
						a = i;
						flag = 2;
					}

				}
			}
		}
	}
	if (flag == 1)
	{
		Path_occlusion_judgment1(16, gs->body[a][0] - 0.145, 3.5, gs, vec_ret);
		return OK;
	}
	else if (flag == 2)
	{
		Path_occlusion_judgment1(16, gs->body[a][0] + 0.145, 3.5, gs, vec_ret);
		return OK;
	}
	else
		return ERROR;
}

/*
函数名：Play_a_closer_ball2
功能：	打一个离营中心更近的冰壶而且这个冰壶要有保护，y动态选择(3.08~6.68)
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：int    1：可以打出这样一个冰壶
*/
int Play_a_closer_ball2(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int a;
	int flag = 0;
	int i;
	a = 0;
	float dify = 3;		//y偏移
	float posy = 3.08;	//打的位置的y坐标
	float tempy = 3.08;
	float difx = 0.14;	//x偏移
	float step = 0.3;	//步长
	for (i = 0; i < gs->ShotNum; i++)
	{
		if ((abs(gs->body[i][0] - 2.375) < 1.5) && (gs->body[i][1] > 6))
		{
			if (gs->body[i][0] > 2.375)
			{
				for (tempy = 3.08; tempy <= 6.68; tempy += step)
				{
					if (is_in_House(gs->body[i][0] - difx, tempy))		//先判断是否在大本营内
					{
						if (get_dist(gs->body[i][0] - difx, tempy) < get_dist(gs->body[a][0], posy))
						{
							Path_occlusion_judgment1(16, gs->body[i][0] - difx, tempy, gs, vec_ret);
							if (fabs(direction_flag) != 1)      //路径无遮挡
							{
								a = i;
								posy = tempy;
								flag = 1;
							}

						}
					}

				}

			}
			else
			{
				for (tempy = 3.08; tempy <= 6.68; tempy += step)
				{
					if (is_in_House(gs->body[i][0] + difx, tempy))		//先判断是否在大本营内
					{
						if (get_dist(gs->body[i][0] + difx, tempy) < get_dist(gs->body[a][0], posy))
						{
							Path_occlusion_judgment1(16, gs->body[i][0] + difx, tempy, gs, vec_ret);
							if (fabs(direction_flag) != 1)      //路径无遮挡
							{
								a = i;
								posy = tempy;
								flag = 2;
							}

						}
					}

				}
			}
		}
	}
	if (flag == 1)
	{
		Path_occlusion_judgment1(16, gs->body[a][0] - difx, posy, gs, vec_ret);
		return OK;
	}
	else if (flag == 2)
	{
		Path_occlusion_judgment1(16, gs->body[a][0] + difx, posy, gs, vec_ret);
		return OK;
	}
	else
		return ERROR;
}

/*
函数名：Play_a_closer_ball3
功能：	打一个比对方壶离营中心更近的冰壶但不一定有保护，y动态选择(3.08~6.68),x动态选择（0.575~4.175）
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：int    1：可以打出这样一个冰壶
*/
int Play_a_closer_ball3(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int flag = 0;
	int j = 0;
	float posy = 3.08;	//打的位置的y坐标
	float posx = 0.6;	//打的位置的x坐标
	float tempy = 3.08;
	float tempx = 0.575;	//0.575为x初坐标
	float stepy = 0.3;	//步长
	float stepx = 0.3; //x步长
	get_ranking(rank, gs);
	j = 0;
	while (j < gs->ShotNum)
	{
		if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
			// choose Shot 1. this case your opponent's curling is in the house
			//Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
			posx = gs->body[rank[j]][0];
			posy = gs->body[rank[j]][1];
			break;
		}
		else {
			// choose Shot 2.
			// this case your curling is in the house
			j++;
		}
	}
	if (j >= gs->ShotNum)		//大本营中没有对方的壶
	{
		posx = 0.505;
		posy = 4.88;
		for (tempy = 3.08; tempy <= 6.68; tempy += stepy)
		{
			for (tempx = 0.575; tempx <= 4.2; tempx += stepx)
			{
				if (is_in_House(tempx, tempy))		//先判断是否在大本营内
				{
					if (get_dist(tempx, tempy) < get_dist(posx, posy))
					{
						Path_occlusion_judgment1(16, tempx, tempy, gs, vec_ret);
						if (fabs(direction_flag) != 1)      //路径无遮挡
						{
							posx = tempx;
							posy = tempy;
							flag = 2;
						}
					}

				}
			}
		}
	}
	else
	{
		for (tempy = 3.08; tempy <= 6.68; tempy += stepy)
		{
			for (tempx = 0.575; tempx <= 4.2; tempx += stepx)
			{
				if (is_in_House(tempx, tempy))		//先判断是否在大本营内
				{
					if (get_dist(tempx, tempy) < get_dist(posx, posy))
					{
						Path_occlusion_judgment1(16, tempx, tempy, gs, vec_ret);
						if (fabs(direction_flag) != 1)      //路径无遮挡
						{
							posx = tempx;
							posy = tempy;
							flag = 1;
						}
					}

				}
			}
		}
	}

	if (flag == 1)
	{
		Path_occlusion_judgment1(16, posx, posy, gs, vec_ret);
		return OK;
	}
	else if (flag == 2)
	{
		Path_occlusion_judgment1(16, posx, posy, gs, vec_ret);
		return OK;
	}
	else
		return ERROR;
}


/*
函数名：Protect_First
功能：	判断自己的壶是否离中心最近，如果是则保护，返回OK,否则返回ERROR
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：OK or ERROR
*/
Status Protect_First(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];

	// sort by distance from center
	get_ranking(rank, gs);

	if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]))
	{
		if (rank[0] % 2 != gs->ShotNum % 2)
		{
			return ERROR;
		}
		else
		{
			Path_occlusion_judgment1(16, gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 3.4, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 3.7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, gs->body[rank[0]][0] + 0.14, gs->body[rank[0]][1] + 4, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						return ERROR;
					}
				}
			}
		}
	}
	else
		return ERROR;
	return OK;
}


/*
函数名：Protect_First2
功能：	判断自己的壶是否离中心最近，如果是,且没有保护则加保护，返回OK,否则返回ERROR
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：OK or ERROR
*/
Status Protect_First2(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int flag = 0;
	int i;
	// sort by distance from center
	get_ranking(rank, gs);

	if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]))
	{
		if (rank[0] % 2 != gs->ShotNum % 2)
		{
			return ERROR;
		}
		else
		{
			for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
			{
				if ((fabs(gs->body[i][0] - gs->body[rank[0]][0]) < 0.21) && gs->body[i][1] > gs->body[rank[0]][1])
					//与中心线距离小于0.32且在前掷线与大本营中心之间
				{
					flag += 1;

				}
			}
			if (flag > 0)		//有保护
				return ERROR;
			else
			{
				Path_occlusion_judgment1(16, gs->body[rank[0]][0] - 0.16, gs->body[rank[0]][1] + 2.8, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, gs->body[rank[0]][0] + 0.14, gs->body[rank[0]][1] + 2.4, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, gs->body[rank[0]][0] - 0.14, gs->body[rank[0]][1] + 2, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							return ERROR;
						}
					}
				}
			}

		}
	}
	else
		return ERROR;
	return OK;
}


/*
函数名：AddBall
功能：	判断大本营附近有没有可以被撞进去的自己的壶，可以把自己壶撞进去get_dist(gs->body[j][0], gs->body[j][1]) > pow(HOUSE_R , 2)
输入：	const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：OK or ERROR
*/
Status AddBall(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int flag = 0;
	int i,j;
	int st=0;
	// sort by distance from center
	//get_ranking(rank, gs);
	j = 0;
	while (j < gs->ShotNum)
	{
		if (get_dist(gs->body[j][0], gs->body[j][1]) > pow(HOUSE_R , 2) && (j % 2 == gs->ShotNum % 2)&& gs->body[j][1] > 5 && gs->body[j][1] <=7 && (fabs(gs->body[j][0] - 2.375) < 1.4)) {
			// choose Shot 1. this case your opponent's curling is in the house
			if (gs->body[j][0] > (2.375 + 0.9))							//未进行障碍判断，待优化
			{
				st = Path_occlusion_judgment_zuoten(j, gs->body[j][0], gs->body[j][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[j][0] + 0.145, gs->body[j][1], vec_ret);
			}
			else if (gs->body[j][0] < (2.375 - 0.9))
			{
				st = Path_occlusion_judgment_youten(j, gs->body[j][0], gs->body[j][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[j][0] - 0.145, gs->body[j][1], vec_ret);
			}
			else
				straight_line(gs->body[j][0] - 0.1, gs->body[j][1], vec_ret);
			if (st == ERROR)
			{
				vec_ret->speed += 0.8;
			}
			else
			{
				vec_ret->speed += 0.7;
			}
			
			return OK;
		}
		else {
			// choose Shot 2.
			// this case your curling is in the house
			j++;
		}
	}
	return ERROR;
		

}


/*
函数名：Push1
功能：	推壶
输入：	int w,float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret  坐标x，y；结构体GAMESTATE,SHOTINFO  w为要击飞的冰壶的序号（目标冰壶）;
返回值：无
*/
Status Push1(int w, float x, float y, const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int flag = 0;   //遮挡个数
	int rflag = 0;	//第二次筛选
	int rrflag = 0;	//第三次筛选
	int Occ[16] = { 20 };
	int rOcc[16] = { 20 };
	int rrOcc[16] = { 20 };
	int tg;			//靶子

	int j = 0;
	int i = 0;
	for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
	{
		if ((fabs(gs->body[i][0] - x) < 0.3) && (i != w) && (gs->body[i][1] > y))
			//与x距离小于0.3且该冰壶不是目标冰壶并且不在目标冰壶的后方（目标冰壶：要推走的冰壶）
		{
			flag += 1;
			Occ[j++] = i;

		}
	}
	if (flag == 0)   //直线球无遮挡,打定
	{
		straight_line(x, y, vec_ret);
		if(y<4.88&&y>3)
			vec_ret->speed += 0.7;
		else if (y >= 4.88 && y < 6)
			vec_ret->speed += 1;
		else if (y > 6 && y < 7.5)
			vec_ret->speed += 1.5;
		else
		{
			vec_ret->speed += 1.9;
			return ERROR;
		}
		return OK;
	}
	else if (flag == 1)
	{
		if ((fabs(gs->body[Occ[0]][0] - x) < 0.15) && (i != w) && (gs->body[Occ[0]][1] > (y + 0.2)) && (gs->body[Occ[0]][1] < (y + 2)))//前方有一个壶挡着，就打这个壶
		{
			straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
			if (Occ[0] % 2 != gs->ShotNum % 2)	//对方的壶
				vec_ret->speed += 2.1;
			else
				vec_ret->speed += 2.1;
			return OK;
		}
		else
		{
			straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
			vec_ret->speed += 2.1;
			return ERROR;
		}

	}
	else
	{
		j = 0;
		for (i = 0; i < flag; i++)
		{
			if ((fabs(gs->body[Occ[i]][0] - x) < 0.15) && (i != w) && (gs->body[Occ[i]][1] > (y + 0.2)))
			{
				rflag += 1;
				rOcc[j++] = Occ[i];
			}
		}
		if (rflag != 0)
		{
			j = 0;
			for (i = 0; i < rflag; i++)
			{
				if (gs->body[rOcc[i]][1] > (y + 2))
				{
					rrflag += 1;
					rrOcc[j++] = rOcc[i];
				}
			}
			if (rrflag > 0)
			{
				straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
				vec_ret->speed += 2.4;
				return ERROR;
			}
			else
			{
				tg = rOcc[0];
				for (i = 0; i < rflag; i++)
					if (gs->body[rOcc[i]][1] > gs->body[tg][1])	//寻找距离发球点最近的壶
						tg = rOcc[i];
				straight_line(gs->body[tg][0], gs->body[tg][1], vec_ret);
				if (tg % 2 != gs->ShotNum % 2)	//对方的壶
					vec_ret->speed += 2.5;
				else
					vec_ret->speed += 2.5;
				return OK;
			}

		}
		else
		{
			straight_line(gs->body[Occ[0]][0], gs->body[Occ[0]][1], vec_ret);
			vec_ret->speed += 2.4;
			return ERROR;

		}

	}
	return ERROR;		//以防万一
}
/*
函数名：dashuai
功能：打甩（自己和对方都不留下，如果有保护全部清掉）
输入：两个结构体和目标壶
*/
void dashuai(const GAMESTATE* const gs, SHOTINFO* vec_ret, int target)
{
	int i;
	int flag = -1;
	for (i = 0; i < gs->ShotNum; i++)
	{
		if (fabs(gs->body[i][0] - gs->body[target][0]) < 0.32 && gs->body[i][1] > gs->body[target][1] || fabs(gs->body[i][0] - gs->body[flag][0]) < 0.32 && gs->body[i][1] > gs->body[flag][1] && flag != -1)
		{
			flag = i;
		}
	}
	if (flag == -1)//没有保护
	{
		vec_ret->angle = 0;
		vec_ret->speed = 12;
		vec_ret->h_x = gs->body[target][0] - 2.375;
		if (vec_ret->h_x > 0)
			vec_ret->h_x += 0.15;
		else
			vec_ret->h_x -= 0.15;
	}
	else//有保护,还是不考虑有多重保护的情况
	{
		if (is_in_House(gs->body[flag][0], gs->body[flag][1]) == true)
		{
			vec_ret->angle = 0;
			if (fabs(gs->body[flag][1] - gs->body[target][1]) < 2.1)
			{
				if (fabs((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1])) < 0.3)
					vec_ret->h_x = gs->body[flag][0] - 2.375;
				else if (fabs((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1])) < 0.6)
					vec_ret->h_x = gs->body[flag][0] - 2.375 + 0.3 * (gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]);
				else if ((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]) > 0.6)
					vec_ret->h_x = gs->body[flag][0] - 2.375 + 0.2;
				else if ((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]) < -0.6)
					vec_ret->h_x = gs->body[flag][0] - 2.375 - 0.2;
			}
			else
			{
				vec_ret->h_x = gs->body[flag][0] - 2.375;
			}
			vec_ret->speed = 15;
		}
		else
		{
			/*if (Path_occlusion_judgment_youten_d(target, gs->body[target][0], gs->body[target][1], gs, vec_ret) == OK)
			{
				Hit_youten(target, gs->body[target][0], gs->body[target][1], gs, vec_ret);
				vec_ret->speed += 4;
			}
			else if (Path_occlusion_judgment_zuoten_d(target, gs->body[target][0], gs->body[target][1], gs, vec_ret) == OK)
			{
				Hit_zuoten(target, gs->body[target][0], gs->body[target][1], gs, vec_ret);
				vec_ret->speed += 4;
			}
			else
			{
				vec_ret->angle = 0;
				if (fabs(gs->body[flag][1] - gs->body[target][1]) < 1.5)
				{
					if (fabs((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1])) < 0.6)
						vec_ret->h_x = gs->body[flag][0] - 2.375 + 0.3 * (gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]);
					else if ((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]) > 0.6)
						vec_ret->h_x = gs->body[flag][0] - 2.375 + 0.2;
					else if ((gs->body[flag][0] - gs->body[target][0]) / (gs->body[flag][1] - gs->body[target][1]) < -0.6)
						vec_ret->h_x = gs->body[flag][0] - 2.375 - 0.2;
				}
				else
				{
					vec_ret->h_x = gs->body[flag][0] - 2.375;
				}
				vec_ret->speed = 15;
			}*/
			Hit3(target, gs->body[target][0], gs->body[target][1], gs, vec_ret);
		}
	}
}