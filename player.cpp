#include"main.h"


/*
函数名：First_player_lpy
功能：  先手函数
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/
//int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player_lpy(const GAMESTATE* const gs, SHOTINFO* vec_ret)//先手最多只有第一局
{
	switch (gs->ShotNum)
	{
	case 0:
	{
		straight_line(2.375, 4.88, vec_ret);//先手诱饵，直接进营
		break;
	}
	case 2:
	{
		if (is_in_House(gs->body[1][0], gs->body[1][1]) == true)//上钩了
		{
			dashuai(gs, vec_ret, 1);
		}
		else//没上钩，推走
		{
			straight_line(gs->body[1][0], gs->body[1][1], vec_ret);
			vec_ret->speed += 1.7;
		}
		break;
	}
	case 4:
	{
		if (is_in_House(gs->body[3][0], gs->body[3][1]) == true)//上钩了
		{
			dashuai(gs, vec_ret, 3);
		}
		else//没上钩，推走
		{
			straight_line(gs->body[3][0], gs->body[3][1], vec_ret);
			vec_ret->speed += 1.7;
		}
		break;
	}
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	{
		//int tmp = 1;
		//int j;
		//for (tmp = 1; tmp < gs->ShotNum; tmp += 2)//找到在营内的壶
		//{
		//	if (gs->body[tmp][1] != 0)
		//		break;
		//}
		//for (j = 3; j < gs->ShotNum; j += 2)
		//	if (gs->body[j][1] < gs->body[tmp][1] && is_in_House(gs->body[j][0], gs->body[j][1]) == true)
		//		tmp = j;
		//dashuai(gs, vec_ret, tmp);
		//break;
		int tmp = 1;
		int j;
		for (tmp = 1; tmp < gs->ShotNum; tmp += 2)
		{
			if (gs->body[tmp][1] != 0)
				break;
		}
		for (j = 3; j < gs->ShotNum; j += 2)
			if (get_dist(gs->body[j][0], gs->body[j][1]) < get_dist(gs->body[tmp][0], gs->body[tmp][1]))
				tmp = j;
		if (!(gs->body[tmp][0]==0&&gs->body[tmp][1]==0))
			dashuai(gs, vec_ret, tmp);
		else
			Path_occlusion_judgment1(16, 2.375, 3.2, gs, vec_ret);
		break;
	}
	}
}
/*
函数名：First_player
功能：  先手函数
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/
int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	    //最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 0:	straight_line(2.375 - 0.05, 7, vec_ret); break;
	case 2:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[1] = 1;	//我方第一个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 + 0.5, 6.5, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 - 0.55, 6.5, gs, vec_ret);
				if (fabs(direction_flag) == 1)
					straight_line(2.375 + 0.5, 6.5, vec_ret);
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 4:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[2] = 1;	//我方第2个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 - 0.8, 6.5, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.8, 6.5, gs, vec_ret);
				if (fabs(direction_flag) == 1)
					straight_line(2.375 - 1, 5.5, vec_ret);
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 6:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[3] = 1;	//我方第3个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
			{
				if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
									zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
								else if (gs->body[1][0] < (2.375 - 1))
									youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
								else
									straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
							}
						}
					}
					vec_ret->speed += 0.5;
				}
				else          //自己的壶，防守
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(gs->body[rank[0]][0] + 0.21, gs->body[rank[0]][1] + 1, vec_ret);//未进行障碍判断，待优化
							}
						}
					}
				}

			}
			else
			{
				straight_line(2.375 - 0.8, 5.5, vec_ret);
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 8:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[4] = 1;	//我方第4个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
			{
				if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
									zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
								else if (gs->body[1][0] < (2.375 - 1))
									youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
								else
									straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
							}
						}
					}
					if (flag1[0] == 0)		//打直线
						vec_ret->speed += 5;
					else
						vec_ret->speed += 0.6;
				}
				else          //自己的壶，防守
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 0.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(gs->body[rank[0]][0] - 0.21, gs->body[rank[0]][1] + 1.2, vec_ret);//未进行障碍判断，待优化
							}
						}
					}
				}

			}
			else
			{
				straight_line(2.375 + 0.8, 5.3, vec_ret);
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 10:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[5] = 1;	//我方第5个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 5;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1;	//推
						}
					}
					else
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							straight_line((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
					}

				}
				else
				{
					if (flag1[0] == 0)		//打直线
						vec_ret->speed += 5;
					else
						vec_ret->speed += 0.6;
				}

			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					youpian_ten((2.375 - 0.15), 4, vec_ret);	//不然直线入营（有待改进）
			}

		}
		else    //大本营中无壶
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				zuopian_ten((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 12:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[6] = 1;	//我方第6个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 5;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1;	//推
						}
					}
					else
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							straight_line((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
					}

				}
				else
					vec_ret->speed += 0.6;
			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					youpian_ten((2.375 - 0.15), 4, vec_ret);	//不然直线入营（有待改进）
			}

		}
		else    //大本营中无壶
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				zuopian_ten((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 14:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[7] = 1;	//我方第7个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 5;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1.5;	//推
						}
					}
					else
					{
						straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
						vec_ret->speed += 7;	//打飞
					}

				}
				else
					vec_ret->speed += 0.6;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 6.88, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.1, 6.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.1, 6.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								zuopian_ten((2.375 + 0.1), 5, vec_ret);	//不然左偏入营（有待改进）
						}
					}
				}
			}

		}
		else    //大本营中无壶
		{
			Path_occlusion_judgment1(16, 2.375 + 0.05, 6.6, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.1, 6.6, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.1, 6.6, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							youpian_ten((2.375 - 0.1), 5, vec_ret);	//不然右偏入营（有待改进）
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}


/*
函数名：First_player2
功能：  先手函数（加保护）
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
wsp*/
//int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player2(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	    //最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 0:	straight_line(2.375 - 0.05, 7.65, vec_ret); break;
	case 2:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, 2.375+0.09,4.88, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			if (get_dist(gs->body[1][0], gs->body[1][1]) < 0.26)   //对方的壶在中心，推开
			{
				Path_occlusion_judgment1(16, gs->body[1][0], gs->body[1][1], gs, vec_ret);
				if (fabs(direction_flag) != 1)
				{
					vec_ret->speed += 0.4;
				}
				else
				{
					
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (fabs(direction_flag) != 1)
						{
							vec_ret->speed += 0.3;
						}
						else
						{
							Path_occlusion_judgment1(16, 2.375 + 0.5, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.55, 6.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(2.375 + 0.5, 6.5, vec_ret);
							}
						}

					}
				}
			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.5, 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.55, 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line(2.375 + 0.5, 6.5, vec_ret);
					}


				}
			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 4:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 - 0.8, 6.65, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.8, 6.65, gs, vec_ret);
					if (fabs(direction_flag) == 1)
						straight_line(2.375 - 1, 6.45, vec_ret);
				}

			}

		}
	
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 6:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1]+0.1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else if (gs->body[1][0] < (2.375 - 1))
												zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else
												straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
										}
									}
							
								}
							}
						}
						vec_ret->speed += 0.5;
					}
					else          //自己的壶，暂不处理
					{
						Path_occlusion_judgment1(16, 2.375 + 0.05, 6.75, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.05, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 + 0.8, 4.9, vec_ret);
											}
										}
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4,4.9, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.4, 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375 + 0.8, 4.9, vec_ret);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 8:	if (gs->body[gs->ShotNum - 2][1] < 3)
			flag2_F[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else if (gs->body[1][0] < (2.375 - 1))
												zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else
												straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
										}
									}

								}
							}
						}
						vec_ret->speed += 0.5;
					}
					else          //自己的壶，防守
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
										straight_line(gs->body[rank[0]][0] + 0.21, gs->body[rank[0]][1] + 2.3, vec_ret);//未进行障碍判断，待优化
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375 - 0.8, 5.5, vec_ret);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 10:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[5] = 1;	//我方第5个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
			{
				if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
					if (fabs(direction_flag) == 1)				//如果都被挡了
					{
						if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
						{
							if (flag1[0] % 2 != gs->ShotNum % 2) {
								// choose Shot 1. this case your opponent's curling is in the house
								straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
								vec_ret->speed += 9;	//打飞
							}
							else {
								// choose Shot 2.
								// this case your curling is in the house
								straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
								vec_ret->speed += 5;	//打定
							}
						}
						else
						{
							if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								straight_line((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
						}

					}
					else
					{
						if (flag1[0] == 0)		//打直线
							vec_ret->speed += 5;
						else
							vec_ret->speed += 0.6;
					}

				}
				else
				{
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
						youpian_ten((2.375 - 0.2), 6.7, vec_ret);	//不然直线入营（有待改进）
				}

			}
			else    //大本营中无壶
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					zuopian_ten((2.375 + 0.2), 5, vec_ret);	//不然直线入营（有待改进）
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 12:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
			{
				if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
				{
					Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
					if (fabs(direction_flag) == 1)				//如果都被挡了
					{
						if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
						{
							if (flag1[0] % 2 != gs->ShotNum % 2) {
								// choose Shot 1. this case your opponent's curling is in the house
								straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
								vec_ret->speed += 9;	//打飞
							}
							else {
								// choose Shot 2.
								// this case your curling is in the house
								straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
								vec_ret->speed += 5;	//打定
							}
						}
						else
						{
							if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								straight_line((2.375 + 0.15), 4, vec_ret);	//不然直线入营（有待改进）
						}

					}
					else
					{
						if (flag1[0] == 0)		//打直线
							vec_ret->speed += 5;
						else
							vec_ret->speed += 0.6;
					}

				}
				else
				{
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
						youpian_ten((2.375 + 0.2), 6.7, vec_ret);	//不然直线入营（有待改进）
				}

			}
			else    //大本营中无壶
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					zuopian_ten((2.375 - 0.2), 5, vec_ret);	//不然直线入营（有待改进）
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 14:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[7] = 1;	//我方第7个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 6;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1.5;	//推
						}
					}
					else
					{
						straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
						vec_ret->speed += 7;	//打飞
					}

				}
				else
					vec_ret->speed += 0.6;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 6.76, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Protect_First2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.15, 6.7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.2, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									zuopian_ten((2.375 + 0.1), 5, vec_ret);	//不然左偏入营（有待改进）
							}
						}
					}

				}
			}

		}
		else    //大本营中无壶
		{
			Path_occlusion_judgment1(16, 2.375 + 0.05, 6.7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.1, 6.7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.1, 6.7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							youpian_ten((2.375 - 0.1), 6.65, vec_ret);	//不然右偏入营（有待改进）
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}


/*
函数名：First_player3
功能：  先手函数（加保护、加弧线打定）
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
wsp*/
//int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player3(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	    //最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 0:	straight_line(2.375 - 0.05, 7.65, vec_ret); break;
	case 2:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, 2.375 + 0.09, 4.88, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			if (get_dist(gs->body[1][0], gs->body[1][1]) < 0.26)   //对方的壶在中心，推开
			{
				Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1], gs, vec_ret);
				if (fabs(direction_flag) != 1)
				{
					vec_ret->speed += 0.4;
				}
				else
				{

					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (fabs(direction_flag) != 1)
						{
							vec_ret->speed += 0.3;
						}
						else
						{
							Path_occlusion_judgment1(16, 2.375 + 0.5, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.55, 6.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(2.375 + 0.5, 6.5, vec_ret);
							}
						}

					}
				}
			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.5, 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.55, 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line(2.375 + 0.5, 6.5, vec_ret);
					}


				}
			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 4:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 - 0.8, 6.65, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.8, 6.65, gs, vec_ret);
					if (fabs(direction_flag) == 1)
						straight_line(2.375 - 1, 6.45, vec_ret);
				}

			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 6:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，先撞，撞不了再推开
					{
						if (Hit3(0, gs->body[0][0], gs->body[0][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												{
													if(youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret)==ERROR)
														straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												}
												else if (gs->body[1][0] < (2.375 - 1))
												{
													if (zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret) == ERROR)
														straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												}
												else
													straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											}
										}

									}
								}
							}
							vec_ret->speed += 0.5;
						}
				
					}
					else          //自己的壶，暂不处理
					{
						Path_occlusion_judgment1(16, 2.375 + 0.05, 6.75, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.05, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 + 0.8, 4.9, vec_ret);
											}
										}
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 4.9, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.4, 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375 + 0.8, 4.9, vec_ret);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 8:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else if (gs->body[1][0] < (2.375 - 1))
												zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else
												straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
										}
									}

								}
							}
						}
						vec_ret->speed += 0.5;
					}
					else          //自己的壶，防守
					{
						if (Protect_First(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
											straight_line(gs->body[rank[0]][0] + 0.21, gs->body[rank[0]][1] + 2.3, vec_ret);//未进行障碍判断，待优化
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 , 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.8, 5.5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 10:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[5] = 1;	//我方第5个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.1, 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.6, 6.4, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.8, 6.4, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.1, 4.88, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375, 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.2, 5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 12:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.3, 5.1, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.6, 6.2, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.8, 6.2, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.3, 5.1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 1, 6.2, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.2, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375+0.25, 5.5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.25, 5.5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}


		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 14:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[7] = 1;	//我方第7个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 6;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1.5;	//推
						}
					}
					else
					{
						straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
						vec_ret->speed += 7;	//打飞
					}

				}
				else
					vec_ret->speed += 0.6;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 6.74, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Protect_First2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.15, 6.7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.2, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								{
									if (Protect_First2(gs, vec_ret) == ERROR)
									{
										zuopian_ten((2.375 + 0.1), 5, vec_ret);	//不然左偏入营（有待改进）
									}
								}
									
							}
						}
					}

				}
			}

		}
		else    //大本营中无壶
		{
			Path_occlusion_judgment1(16, 2.375 + 0.05, 6.7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.1, 6.7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.1, 6.7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							youpian_ten((2.375 - 0.1), 6.65, vec_ret);	//不然右偏入营（有待改进）
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}


/*
函数名：First_player4
功能：  先手函数（加保护、加弧线打定、前置线）
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
wsp*/
//int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player4(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	    //最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 0:	straight_line(2.375 - 0.05, 7.1, vec_ret); break;
	case 2:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, 2.375 + 0.4, 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			if (get_dist(gs->body[1][0], gs->body[1][1]) < 0.26)   //对方的壶在中心，推开
			{
				Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1], gs, vec_ret);
				if (fabs(direction_flag) != 1)
				{
					vec_ret->speed += 0.4;
				}
				else
				{

					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (fabs(direction_flag) != 1)
						{
							vec_ret->speed += 0.5;
						}
						else
						{
							Path_occlusion_judgment1(16, 2.375 + 0.5, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.55, 6.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(2.375 + 0.5, 6.5, vec_ret);
							}
						}

					}
				}
			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.5, 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.55, 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line(2.375 + 0.5, 6.5, vec_ret);
					}


				}
			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 4:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 - 0.4, 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.8, 6.65, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						straight_line(2.375 - 1, 6.45, vec_ret);
					}
				}


			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 6:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，先撞，撞不了再推开
					{
						if (Hit3(0, gs->body[0][0], gs->body[0][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												{
													if (youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret) == ERROR)
														straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												}
												else if (gs->body[1][0] < (2.375 - 1))
												{
													if (zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret) == ERROR)
														straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												}
												else
													straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											}
										}

									}
								}
							}
							vec_ret->speed += 0.5;
						}

					}
					else          //自己的壶，暂不处理
					{
						Path_occlusion_judgment1(16, 2.375 + 0.05, 6.75, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.05, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 + 0.8, 4.9, vec_ret);
											}
										}
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 4.9, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.4, 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375 + 0.8, 4.9, vec_ret);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 8:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
												youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else if (gs->body[1][0] < (2.375 - 1))
												zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											else
												straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
										}
									}

								}
							}
						}
						vec_ret->speed += 0.5;
					}
					else          //自己的壶，防守
					{
						if (Protect_First(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
											straight_line(gs->body[rank[0]][0] + 0.21, gs->body[rank[0]][1] + 2.3, vec_ret);//未进行障碍判断，待优化
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375, 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.8, 5.5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 10:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[5] = 1;	//我方第5个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.1, 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.6, 6.4, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.8, 6.4, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.1, 4.88, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375, 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.2, 5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}


		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 12:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.3, 5.1, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.6, 6.2, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.8, 6.2, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.3, 5.1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 1, 6.2, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.2, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.25, 5.5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375 - 0.25, 5.5, vec_ret);
											}
										}
									}
								}
							}
						}
					}
				}
			}


		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 14:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[7] = 1;	//我方第7个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
				if (fabs(direction_flag) == 1)				//如果都被挡了
				{
					if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
					{
						if (flag1[0] % 2 != gs->ShotNum % 2) {
							// choose Shot 1. this case your opponent's curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 6;	//打定
						}
						else {
							// choose Shot 2.
							// this case your curling is in the house
							straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
							vec_ret->speed += 1.5;	//推
						}
					}
					else
					{
						straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
						vec_ret->speed += 7;	//打飞
					}

				}
				else
					vec_ret->speed += 0.6;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 6.74, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Protect_First2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.15, 6.7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.2, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								{
									if (Protect_First2(gs, vec_ret) == ERROR)
									{
										zuopian_ten((2.375 + 0.1), 5, vec_ret);	//不然左偏入营（有待改进）
									}
								}

							}
						}
					}

				}
			}

		}
		else    //大本营中无壶
		{
			Path_occlusion_judgment1(16, 2.375 + 0.05, 6.7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.1, 6.7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.1, 6.7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							youpian_ten((2.375 - 0.1), 6.65, vec_ret);	//不然右偏入营（有待改进）
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}


/*
函数名：First_player5
功能：  先手函数（在4的基础上加入推壶和打一个离中心比对方壶近的壶）
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
wsp*/
//int flag2_F[10] = { 0 };	//记录我方壶是否被撞飞
void First_player5(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	    //最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 0:	straight_line(2.375 - 0.05, 7.1, vec_ret); break;
	case 2:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, 2.375 + 0.4, 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			if (get_dist(gs->body[1][0], gs->body[1][1]) < 0.26)   //对方的壶在中心，推开
			{
				Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1], gs, vec_ret);
				if (fabs(direction_flag) != 1)
				{
					vec_ret->speed += 0.4;
				}
				else
				{

					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (fabs(direction_flag) != 1)
						{
							vec_ret->speed += 0.5;
						}
						else
						{
							Path_occlusion_judgment1(16, 2.375 + 0.5, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.55, 6.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
									straight_line(2.375 + 0.5, 6.5, vec_ret);
							}
						}

					}
				}
			}
			else
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.5, 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.55, 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line(2.375 + 0.5, 6.5, vec_ret);
					}


				}
			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 4:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, 2.375 - 0.4, 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.8, 6.65, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						straight_line(2.375 - 1, 6.45, vec_ret);
					}
				}


			}

		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 6:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，先撞，撞不了再推开
					{
						if (Hit3(0, gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret) == ERROR)
						{
							if (Push1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret) == ERROR)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
													{
														if (youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret) == ERROR)
															straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
													}
													else if (gs->body[1][0] < (2.375 - 1))
													{
														if (zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret) == ERROR)
															straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
													}
													else
														straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												}
											}

										}
									}
								}
								vec_ret->speed += 0.5;
							}
	
						}

					}
					else          //自己的壶，暂不处理
					{
						Path_occlusion_judgment1(16, 2.375 + 0.05, 6.75, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.05, 6.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (AddBall(gs, vec_ret) == ERROR)
												{
													if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
													{
														straight_line(2.375 + 0.8, 4.9, vec_ret);
													}
												}
												
												
											}
										}
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 4.9, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.4, 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (AddBall(gs, vec_ret) == ERROR)
											{
												if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
												{
													straight_line(2.375 + 0.8, 4.9, vec_ret);
												}
											}
											
											
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 8:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
				{
					if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，推开
					{
						if (Push1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1], gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1], gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.1, gs->body[rank[0]][1] + 0.1, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
													youpian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												else if (gs->body[1][0] < (2.375 - 1))
													zuopian_ten(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
												else
													straight_line(gs->body[rank[0]][0], gs->body[rank[0]][1], vec_ret);
											}
										}

									}
								}
							}
							vec_ret->speed += 0.7;
						}

					}
					else          //自己的壶，防守
					{
						if (Protect_First(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.15, gs->body[rank[0]][1] + 1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] - 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0] + 0.2, gs->body[rank[0]][1] + 1, gs, vec_ret);
										if (fabs(direction_flag) == 1)
											straight_line(gs->body[rank[0]][0] + 0.21, gs->body[rank[0]][1] + 2.3, vec_ret);//未进行障碍判断，待优化
									}
								}
							}
						}
					}

				}
				else
				{
					Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.4, 5.3, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375, 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (AddBall(gs, vec_ret) == ERROR)
												{
													if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
													{
														straight_line(2.375 - 0.8, 5.5, vec_ret);
													}
												}
												
												
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 10:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[5] = 1;	//我方第5个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 + 0.1, 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.6, 6.4, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 + 0.8, 6.4, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.1, 4.88, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375, 5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{

												if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
												{
													straight_line(2.375 - 0.2, 5, vec_ret);
												}
												
											}
										}
									}
								}
							}
						}
					}
				}
			}


		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 12:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)		//找到对方最优的壶打掉
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
					break;
				}
				else {
					// choose Shot 2.
					// this case your curling is in the house
					j++;
				}
			}
			if (j >= gs->ShotNum)
			{
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.3, 5.1, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, 2.375 - 0.6, 6.2, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.8, 6.2, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.3, 5.1, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 1, 6.2, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 1, 6.2, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.25, 5.5, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
												{
													straight_line(2.375 - 0.25, 5.5, vec_ret);
												}
												
											}
										}
									}
								}
							}
						}
					}
				}
			}


		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 14:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2_F[7] = 1;	//我方第7个壶被撞飞
		if (is_in_House(gs->body[rank[0]][0], gs->body[rank[0]][1]) == true)
		{
			if (rank[0] % 2 != gs->ShotNum % 2)	//距离大本营最近的是对方的壶，打定
			{
				if (Hit3(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret) == ERROR)
				{
					if (Push1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(rank[0], gs->body[rank[0]][0], gs->body[rank[0]][1], gs, vec_ret);
						if (fabs(direction_flag) == 1)				//如果都被挡了
						{

							if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
							{
								if (flag1[0] % 2 != gs->ShotNum % 2) {
									// choose Shot 1. this case your opponent's curling is in the house
									straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									vec_ret->speed += 6;	//打定
								}
								else {
									// choose Shot 2.
									// this case your curling is in the house
									straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									vec_ret->speed += 1.5;	//推
								}
							}
							else
							{
								straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
								vec_ret->speed += 7;	//打飞
							}

						}
						else
							vec_ret->speed += 0.6;
					}

				}

			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 6.74, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					if (Protect_First2(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.15, 6.7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.2, 6.7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
								{
									if (Protect_First2(gs, vec_ret) == ERROR)
									{
										if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
										{
											zuopian_ten((2.375 + 0.1), 5, vec_ret);	//不然左偏入营（有待改进）
										}
										
									}
								}

							}
						}
					}

				}
			}

		}
		else    //大本营中无壶
		{
			Path_occlusion_judgment1(16, 2.375 + 0.05, 6.7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, 2.375 + 0.1, 6.7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, 2.375 - 0.1, 6.7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							youpian_ten((2.375 - 0.1), 6.65, vec_ret);	//不然右偏入营（有待改进）
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}




/*
函数名：Second_player
功能：  后手函数
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/
int flag1[20] = { 0 };	//直线球被挡记录
int flag2[10] = { 0 };	//记录我方壶是否被撞飞
void Second_player(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	//最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	int st = 0;					//左偏右偏成功判断
	// sort by distance from center
	get_ranking(rank, gs);
	switch (gs->ShotNum)
	{
	case 1:	Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 + 0.7), 6, vec_ret);
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 3:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[1] = 1;	//我方第一个壶被撞飞

		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									straight_line((2.375 - 0.7), 6, vec_ret);
								}
							}
						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 5:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[2] = 1;	//我方第2个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);	//往营里打
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
						if (fabs(direction_flag) == 1)				//如果都被挡了
						{
							if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
							{
								if (flag1[0] % 2 != gs->ShotNum % 2) {
									// choose Shot 1. this case your opponent's curling is in the house
									straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									vec_ret->speed += 5;	//打定
								}
								else {
									// choose Shot 2.
									// this case your curling is in the house
									if (gs->body[flag1[0]][0] > 2.375)
										zuopian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									else
										youpian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									vec_ret->speed += 0.5;
								}
							}
							else
								straight_line((2.375 + 0.35), 4, vec_ret);	//不然直线入营（有待改进）
						}


					}
				}

			}
		}


		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 7:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[3] = 1;	//我方第3个壶被撞飞
		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);	//往营里打
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
						if (fabs(direction_flag) == 1)				//如果都被挡了
						{
							if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
							{
								if (flag1[0] % 2 != gs->ShotNum % 2) {
									// choose Shot 1. this case your opponent's curling is in the house
									Hit1(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);
								}
								else {
									// choose Shot 2.
									// this case your curling is in the house
									if (gs->body[flag1[0]][0] > 2.375)
										zuopian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									else
										youpian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
									vec_ret->speed += 0.5;
								}
							}
							else
								straight_line((2.375 - 0.35), 4, vec_ret);	//不然直线入营（有待改进）
						}


					}
				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 9:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[4] = 1;	//我方第4个壶被撞飞
		j = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
				// choose Shot 1. this case your opponent's curling is in the house
				Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
				{
					if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
					{
						st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
					}
					else if (gs->body[1][0] < (2.375 - 1))
					{
						st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
					}
					else
						straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
					vec_ret->speed += 0.6;
				}
				else if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))
				{
					if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
					{
						st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
					}
					else if (gs->body[3][0] < (2.375 - 1))
					{
						st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
					}
					else
						straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
					vec_ret->speed += 0.6;
				}
				else
					Path_occlusion_judgment1(16, 2.375 + 0.3, 4.88, gs, vec_ret);		//往营中心打，待优化
			}

		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 11:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[5] = 1;	//我方第5个壶被撞飞

	//while (j < gs->ShotNum)
	//{
	//	if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
	//		// choose Shot 1. this case your opponent's curling is in the house
	//		Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
	//		break;
	//	}
	//	else {
	//		// choose Shot 2.
	//		// this case your curling is in the house
	//		j++;
	//	}
	//}
		if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))//我方第3个壶不在大本营中就打到大本营里
		{
			if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
			{
				st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
			}
			else if (gs->body[3][0] < (2.375 - 1))
			{
				st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
			}
			else
				straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
			vec_ret->speed += 0.6;
		}
		else if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))
		{
			if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
			{
				st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
			}
			else if (gs->body[1][0] < (2.375 - 1))
			{
				st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
			}
			else
				straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
			vec_ret->speed += 0.6;
		}
		else
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					straight_line(2.375 - 0.32, 4.88 + 1.8, vec_ret);		//打在大本营边缘
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 13:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[6] = 1;	//我方第6个壶被撞飞
		if (Hit2(gs, vec_ret) == ERROR)	//优先清中线
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
					{
						if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
						{
							st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
						}
						else if (gs->body[1][0] < (2.375 - 1))
						{
							st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
						}
						else
							straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
						vec_ret->speed += 0.6;
					}
					else if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))
					{
						if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
						{
							st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
						}
						else if (gs->body[3][0] < (2.375 - 1))
						{
							st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
						}
						else
							straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
						vec_ret->speed += 0.6;
					}
					else        //保护自己距离中心最近的壶
					{
						j = 0;
						while (j < gs->ShotNum)
						{
							if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 == gs->ShotNum % 2)) {
								// choose Shot 1. this case your opponent's curling is in the house
								Path_occlusion_judgment1(16, gs->body[rank[j]][0] - 0.145, gs->body[rank[j]][1] + 2.9, gs, vec_ret);
								if (fabs(direction_flag) != 1)
									break;
							}
							else {
								// choose Shot 2.
								// this case your curling is in the house
								j++;
							}
						}
						if (j >= gs->ShotNum)	//如果大本营中没有自己的壶
						{
							if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							{
								straight_line(2.375 + 0.32, 4.88 + 1.8, vec_ret);		//打在大本营边缘
							}
						}
					}

				}
			}

		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 15:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[7] = 1;	//我方第7个壶被撞飞
		j = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
				// choose Shot 1. this case your opponent's curling is in the house
				flag_end += 1;
				endflag[i++] = rank[j];
			}
			j++;
		}
		if (flag_end == 0)		//大本营中没有对方的壶
		{
			if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
			{
				if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
					zuopian_ten(gs->body[3][0], gs->body[3][1], vec_ret);
				else if (gs->body[3][0] < (2.375 - 1))
					youpian_ten(gs->body[3][0], gs->body[3][1], vec_ret);
				else
					straight_line(gs->body[3][0], gs->body[3][1], vec_ret);
				vec_ret->speed += 0.5;
			}
			else if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))
			{
				if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
					zuopian_ten(gs->body[1][0], gs->body[1][1], vec_ret);
				else if (gs->body[1][0] < (2.375 - 1))
					youpian_ten(gs->body[1][0], gs->body[1][1], vec_ret);
				else
					straight_line(gs->body[1][0], gs->body[1][1], vec_ret);
				vec_ret->speed += 0.5;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line((2.375 + 1), 4.88, vec_ret);  //待优化
					}
				}
			}

		}
		else if (flag_end == 1)		//打定它
		{
			for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
			{
				if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
					//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
					break;
			}
			if (i >= gs->ShotNum)	//无遮挡
			{
				straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
				vec_ret->speed += 5;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.2), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.2), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									straight_line(2.38, 4.88, vec_ret);  //待优化
									vec_ret->speed += 2;
								}

							}
						}
					}
				}
			}
		}
		else
		{
			Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.2), 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.2), 4.9, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								straight_line(2.38, 4.88, vec_ret);  //待优化
								vec_ret->speed += 5;
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}



/*
函数名：Second_player2
功能：  后手函数(相比前一版加入保护自方壶的策略)
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/

void Second_player2(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	//最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	int st = 0;					//左偏右偏成功判断
	// sort by distance from center
	get_ranking(rank, gs);
	straight_line((2.375 + 0.7), 6, vec_ret);
	switch (gs->ShotNum)
	{
	case 1:	Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 + 0.7), 6, vec_ret);
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 3:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[1] = 1;	//我方第一个壶被撞飞

		if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
		{
			Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									straight_line((2.375 - 0.7), 6, vec_ret);
								}
							}
						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 5:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);	//往营里打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
							if (fabs(direction_flag) == 1)				//如果都被挡了
							{
								if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
								{
									if (flag1[0] % 2 != gs->ShotNum % 2) {
										// choose Shot 1. this case your opponent's curling is in the house
										straight_line(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
										vec_ret->speed += 5;	//打定
									}
									else {
										// choose Shot 2.
										// this case your curling is in the house
										if (gs->body[flag1[0]][0] > 2.375)
											zuopian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
										else
											youpian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
										vec_ret->speed += 0.5;
									}
								}
								else
									straight_line((2.375 + 0.35), 4, vec_ret);	//不然直线入营（有待改进）
							}


						}
					}

				}
			}
		}



		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 7:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);	//往营里打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
							if (fabs(direction_flag) == 1)				//如果都被挡了
							{
								if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
								{
									if (flag1[0] % 2 != gs->ShotNum % 2) {
										// choose Shot 1. this case your opponent's curling is in the house
										Hit1(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);
									}
									else {
										// choose Shot 2.
										// this case your curling is in the house
										if (gs->body[flag1[0]][0] > 2.375)
											zuopian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
										else
											youpian_ten(gs->body[flag1[0]][0], gs->body[flag1[0]][1], vec_ret);
										vec_ret->speed += 0.5;
									}
								}
								else
									straight_line((2.375 - 0.35), 4, vec_ret);	//不然直线入营（有待改进）
							}


						}
					}

				}
			}
		}


		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 9:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[4] = 1;	//我方第4个壶被撞飞
		j = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
				// choose Shot 1. this case your opponent's curling is in the house
				Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
				{
					if (gs->body[1][0] > (2.375 + 1))
					{
						st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
					}
					else if (gs->body[1][0] < (2.375 - 1))
					{
						st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
					}
					else
						straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
					vec_ret->speed += 0.6;
				}
				else if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))
				{
					if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
					{
						st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
					}
					else if (gs->body[3][0] < (2.375 - 1))
					{
						st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
						if (st == ERROR)
							straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
					}
					else
						straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
					vec_ret->speed += 0.6;
				}
				else
					Path_occlusion_judgment1(16, 2.375 + 0.3, 4.88, gs, vec_ret);		//往营中心打，待优化
			}

		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	
	case 11:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[5] = 1;	//我方第5个壶被撞飞

	//while (j < gs->ShotNum)
	//{
	//	if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
	//		// choose Shot 1. this case your opponent's curling is in the house
	//		Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
	//		break;
	//	}
	//	else {
	//		// choose Shot 2.
	//		// this case your curling is in the house
	//		j++;
	//	}
	//}
		if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))//我方第3个壶不在大本营中就打到大本营里
		{
			if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
			{
				st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
			}
			else if (gs->body[3][0] < (2.375 - 1))
			{
				st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
			}
			else
				straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
			vec_ret->speed += 0.6;
		}
		else if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))
		{
			if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
			{
				st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
			}
			else if (gs->body[1][0] < (2.375 - 1))
			{
				st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
				if (st == ERROR)
					straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
			}
			else
				straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
			vec_ret->speed += 0.6;
		}
		else
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (Protect_First2(gs, vec_ret) == ERROR)
					{
						straight_line(2.375 - 0.32, 4.88 + 1.8, vec_ret);		//打在大本营边缘
					}

				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 13:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[6] = 1;	//我方第6个壶被撞飞
		if (Hit2(gs, vec_ret) == ERROR)	//优先清中线
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
					{
						if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
						{
							st = Path_occlusion_judgment_zuoten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[1][0] + 0.145, gs->body[1][1], vec_ret);
						}
						else if (gs->body[1][0] < (2.375 - 1))
						{
							st = Path_occlusion_judgment_youten(1, gs->body[1][0], gs->body[1][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[1][0] - 0.145, gs->body[1][1], vec_ret);
						}
						else
							straight_line(gs->body[1][0] + 0.1, gs->body[1][1], vec_ret);
						vec_ret->speed += 0.6;
					}
					else if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))
					{
						if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
						{
							st = Path_occlusion_judgment_zuoten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[3][0] + 0.145, gs->body[3][1], vec_ret);
						}
						else if (gs->body[3][0] < (2.375 - 1))
						{
							st = Path_occlusion_judgment_youten(3, gs->body[3][0], gs->body[3][1] + 0.1, gs, vec_ret);
							if (st == ERROR)
								straight_line(gs->body[3][0] - 0.145, gs->body[3][1], vec_ret);
						}
						else
							straight_line(gs->body[3][0] - 0.1, gs->body[3][1], vec_ret);
						vec_ret->speed += 0.6;
					}
					else        //保护自己距离中心最近的壶
					{
						j = 0;
						while (j < gs->ShotNum)
						{
							if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 == gs->ShotNum % 2)) {
								// choose Shot 1. this case your opponent's curling is in the house
								Path_occlusion_judgment1(16, gs->body[rank[j]][0] - 0.145, gs->body[rank[j]][1] + 2.9, gs, vec_ret);
								if (fabs(direction_flag) != 1)
									break;
							}
							else {
								// choose Shot 2.
								// this case your curling is in the house
								j++;
							}
						}
						if (j >= gs->ShotNum)	//如果大本营中没有自己的壶
						{
							if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
							{
								straight_line(2.375 + 0.32, 4.88 + 1.8, vec_ret);		//打在大本营边缘
							}
						}
					}

				}
			}

		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 15:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[7] = 1;	//我方第7个壶被撞飞
		j = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
				// choose Shot 1. this case your opponent's curling is in the house
				flag_end += 1;
				endflag[i++] = rank[j];
			}
			j++;
		}
		if (flag_end == 0)		//大本营中没有对方的壶
		{
			if (is_in_House(gs->body[3][0], gs->body[3][1]) == false && gs->body[3][1] > 5 && (fabs(gs->body[3][0] - 2.375) < 1.4))//我方第一个壶不在大本营中就打到大本营里
			{
				if (gs->body[3][0] > (2.375 + 1))							//未进行障碍判断，待优化
					zuopian_ten(gs->body[3][0], gs->body[3][1], vec_ret);
				else if (gs->body[3][0] < (2.375 - 1))
					youpian_ten(gs->body[3][0], gs->body[3][1], vec_ret);
				else
					straight_line(gs->body[3][0], gs->body[3][1], vec_ret);
				vec_ret->speed += 0.5;
			}
			else if (is_in_House(gs->body[1][0], gs->body[1][1]) == false && gs->body[1][1] > 5 && (fabs(gs->body[1][0] - 2.375) < 1.4))
			{
				if (gs->body[1][0] > (2.375 + 1))							//未进行障碍判断，待优化
					zuopian_ten(gs->body[1][0], gs->body[1][1], vec_ret);
				else if (gs->body[1][0] < (2.375 - 1))
					youpian_ten(gs->body[1][0], gs->body[1][1], vec_ret);
				else
					straight_line(gs->body[1][0], gs->body[1][1], vec_ret);
				vec_ret->speed += 0.5;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
							straight_line((2.375 + 1), 4.88, vec_ret);  //待优化
					}
				}
			}

		}
		else if (flag_end == 1)		//打定它
		{
			for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
			{
				if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
					//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
					break;
			}
			if (i >= gs->ShotNum)	//无遮挡
			{
				straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
				vec_ret->speed += 5;
			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.2), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.2), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									straight_line(2.38, 4.88, vec_ret);  //待优化
									vec_ret->speed += 2;
								}

							}
						}
					}
				}
			}
		}
		else
		{
			Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.2), 4.9, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.2), 4.9, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								straight_line(2.38, 4.88, vec_ret);  //待优化
								vec_ret->speed += 5;
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}



/*
函数名：Second_player3
功能：  后手函数(在2的基础上加入弧线撞球)
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/

void Second_player3(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	//最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	int st = 0;					//左偏右偏成功判断
	int flagkey = 0;//最后一个壶判断是否打定
	int keyflag[20] = { 20 };
	int key = 0;
	int k = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	//straight_line((2.375 + 0.7), 6, vec_ret);
	switch (gs->ShotNum)
	{
	case 1:	Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 + 0.7), 6, vec_ret);
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 3:	if (gs->body[gs->ShotNum - 2][1] < 3)
			flag2[1] = 1;	//我方第一个壶被撞飞
			Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
										straight_line((2.375 - 0.7), 6, vec_ret);
								}
							}
						}
					}
				}
			}
			
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 5:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);	//往营里打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
							if (fabs(direction_flag) == 1)				//如果都被挡了
							{
								if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
								{
									if (flag1[0] % 2 != gs->ShotNum % 2) {
										// choose Shot 1. this case your opponent's curling is in the house
										Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
									}
									else {
										// choose Shot 2.
										Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																if (AddBall(gs, vec_ret) == ERROR)
																{
																	straight_line(2.375 + 0.8, 4.9, vec_ret);
																}
																
															}
														}
													}
												}
											}
										}
									}
								}
								else
								{
									if (AddBall(gs, vec_ret) == ERROR)
									{
										straight_line((2.375 + 0.35), 4, vec_ret);	//不然直线入营（有待改进）
									}
								}
									
							}


						}
					}

				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 7:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (AddBall(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);	//往营里打
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
								if (fabs(direction_flag) == 1)				//如果都被挡了
								{
									if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
									{
										if (flag1[0] % 2 != gs->ShotNum % 2) {
											// choose Shot 1. this case your opponent's curling is in the house
											Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
										}
										else {
											// choose Shot 2.
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
																if (fabs(direction_flag) == 1)
																{
																	straight_line(2.375 - 0.8, 4.9, vec_ret);
																}
															}
														}
													}
												}
											}
										}
									}
									else
									{
										straight_line((2.375 - 0.35), 4, vec_ret);	//不然直线入营（有待改进）
									}

								}


							}
						}

					}
				}
			}
		}


		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 9:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.3, 4.88, gs, vec_ret);		//往营中心打，待优化
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.3, 4.9, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														straight_line((2.375 + 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
													}
												}
											}
										}
									}
								}
							}

						}
						
					}
						
				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;

	case 11:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[5] = 1;	//我方第5个壶被撞飞

	//while (j < gs->ShotNum)
	//{
	//	if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
	//		// choose Shot 1. this case your opponent's curling is in the house
	//		Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
	//		break;
	//	}
	//	else {
	//		// choose Shot 2.
	//		// this case your curling is in the house
	//		j++;
	//	}
	//}
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
						straight_line(2.375 - 0.38, 4.88 + 1.8, vec_ret);		//打在大本营边缘
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 13:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Hit2(gs, vec_ret) == ERROR)	//优先清中线
			{
				j = 0;
				while (j < gs->ShotNum)
				{
					if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
						// choose Shot 1. this case your opponent's curling is in the house
						Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						if (AddBall(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.35, 4.88, gs, vec_ret);		//往营中心打，待优化
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.35, 4.9, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.6, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.4, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															straight_line((2.375 - 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
														}
													}
												}
											}
										}
									}
								}

							}

						}

					}
				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 15:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[7] = 1;	//我方第7个壶被撞飞
		j = 0;
		i = 0;
		k = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true) 
			{
				// choose Shot 1. this case your opponent's curling is in the house
				if (rank[j] % 2 != gs->ShotNum % 2)
				{
					flag_end += 1;
					endflag[i++] = rank[j];
				}
				else
				{
					flagkey += 1;
					keyflag[k++] = rank[j];
				}
			}
			j++;
		}

		if (flag_end == 0)		//大本营中没有对方的壶
		{
			if (AddBall(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 5.5, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.8), 5.5, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.3, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.3, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 1.1), 4.3, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X + 1.1), 4.3, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X - 1.1), 6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, (TEE_X + 1.1), 6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, (TEE_X + 1.7), 4.88, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, (TEE_X - 1.7), 4.88, gs, vec_ret);
																{
																	straight_line((2.375 - 1.5), 4.48, vec_ret);  //待优化
																}
															}
														}
													}
												}
											}
										}
									}
								}
									
							}
						}
							
							
					}
				}
			}

		}
		else if (flag_end == 1)		//
		{
			key = 0;
			if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2))||(gs->body[endflag[0]][1]<=4.88 && fabs(gs->body[endflag[0]][0] - 2.375) < 1.1))
			{
				for (i = 0; i < flagkey; i++)
				{
					if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1])) <= (get_dist(gs->body[keyflag[i]][0], gs->body[keyflag[i]][1])))
						key += 1;
				}
			}
			if (key > 0)
			{
				for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
				{
					if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
						//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
						break;
				}
				if (i >= gs->ShotNum)	//无遮挡
				{
					straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
					vec_ret->speed += 5;
				}
				else
				{
					if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
					{
						if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375, 4.88, vec_ret);  //待优化
												vec_ret->speed += 2;
											}

										}
									}
								}
							}
						}
					}
				}

			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2))
					{
						for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
						{
							if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
								//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
								break;
						}
						if (i >= gs->ShotNum)	//无遮挡
						{
							straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
							vec_ret->speed += 5;
						}
						else
						{
							if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
							{
								if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
								{
									Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														straight_line(2.375, 4.88, vec_ret);  //待优化
														vec_ret->speed += 2;
													}

												}
											}
										}
									}
								}
							}
						}
					}
					else
					{
						Path_occlusion_judgment1(16, 2.375, 4.8, gs, vec_ret);		//往营中心打
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375, 4.88, vec_ret);  //待优化
											vec_ret->speed += 2;
										}

									}
								}
							}
						}
					}
				}
			}

		}
		else
		{
			Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
			if (fabs(direction_flag) == 1)
			{
				if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(0.3, 2))
				{
					for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
					{
						if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
							//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
							break;
					}
					if (i >= gs->ShotNum)	//无遮挡
					{
						straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
						vec_ret->speed += 5;
					}
					else
					{
						if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
							{
								Path_occlusion_judgment1(16, 2.375, 4.76, gs, vec_ret);		//往营中心打
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													if (Hit3(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
													{
														straight_line(2.375, 4.88, vec_ret);  //待优化
														vec_ret->speed += 2;
													}
							
												}

											}
										}
									}
								}
							}
						}
					}
				}
				else
				{
					Path_occlusion_judgment1(16, 2.4, 4.8, gs, vec_ret);		//往营中心打
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										straight_line(2.375, 4.88, vec_ret);  //待优化
										vec_ret->speed += 2;
									}

								}
							}
						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}




/*
函数名：Second_player4
功能：  后手函数(在3的基础上改动3,4壶的策略)
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/

void Second_player4(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j=0;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	//最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	int st = 0;					//左偏右偏成功判断
	int flagkey = 0;//最后一个壶判断是否打定
	int keyflag[20] = { 20 };
	int key = 0;
	int k = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	//straight_line((2.375 + 0.7), 6, vec_ret);
	switch (gs->ShotNum)
	{
	case 1:	Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 + 0.7), 6, vec_ret);
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 3:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, (TEE_X - 0.6), 7, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X - 0.7), 7, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.8), 7, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.6), 7, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.7), 7, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 7, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 - 0.7), 6, vec_ret);
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 5:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.5), 5.3, gs, vec_ret);	//往营里打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
							if (fabs(direction_flag) == 1)				//如果都被挡了
							{
								if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
								{
									if (flag1[0] % 2 != gs->ShotNum % 2) {
										// choose Shot 1. this case your opponent's curling is in the house
										Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
									}
									else {
										// choose Shot 2.
										Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																if (AddBall(gs, vec_ret) == ERROR)
																{
																	straight_line(2.375 + 0.8, 4.9, vec_ret);
																}

															}
														}
													}
												}
											}
										}
									}
								}
								else
								{
									if (AddBall(gs, vec_ret) == ERROR)
									{
										straight_line((2.375 + 0.35), 4, vec_ret);	//不然直线入营（有待改进）
									}
								}

							}


						}
					}

				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 7:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (AddBall(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.5), 5.3, gs, vec_ret);	//往营里打
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
								if (fabs(direction_flag) == 1)				//如果都被挡了
								{
									if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
									{
										if (flag1[0] % 2 != gs->ShotNum % 2) {
											// choose Shot 1. this case your opponent's curling is in the house
											Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
										}
										else {
											// choose Shot 2.
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
																if (fabs(direction_flag) == 1)
																{
																	straight_line(2.375 - 0.8, 4.9, vec_ret);
																}
															}
														}
													}
												}
											}
										}
									}
									else
									{
										straight_line((2.375 - 0.35), 4, vec_ret);	//不然直线入营（有待改进）
									}

								}


							}
						}

					}
				}
			}
		}


		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 9:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.3, 4.88, gs, vec_ret);		//往营中心打，待优化
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.3, 4.9, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														straight_line((2.375 + 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
													}
												}
											}
										}
									}
								}
							}

						}

					}

				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;

	case 11:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[5] = 1;	//我方第5个壶被撞飞

	//while (j < gs->ShotNum)
	//{
	//	if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
	//		// choose Shot 1. this case your opponent's curling is in the house
	//		Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
	//		break;
	//	}
	//	else {
	//		// choose Shot 2.
	//		// this case your curling is in the house
	//		j++;
	//	}
	//}
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
						straight_line(2.375 - 0.38, 4.88 + 1.8, vec_ret);		//打在大本营边缘
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 13:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Hit2(gs, vec_ret) == ERROR)	//优先清中线
			{
				j = 0;
				while (j < gs->ShotNum)
				{
					if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
						// choose Shot 1. this case your opponent's curling is in the house
						Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						if (AddBall(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.35, 4.88, gs, vec_ret);		//往营中心打，待优化
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.35, 4.9, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.6, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.4, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															straight_line((2.375 - 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
														}
													}
												}
											}
										}
									}
								}

							}

						}

					}
				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 15:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[7] = 1;	//我方第7个壶被撞飞
		j = 0;
		i = 0;
		k = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true)
			{
				// choose Shot 1. this case your opponent's curling is in the house
				if (rank[j] % 2 != gs->ShotNum % 2)
				{
					flag_end += 1;
					endflag[i++] = rank[j];
				}
				else
				{
					flagkey += 1;
					keyflag[k++] = rank[j];
				}
			}
			j++;
		}

		if (flag_end == 0)		//大本营中没有对方的壶
		{
			if (AddBall(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.88, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 5.5, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.8), 5.5, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.3, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.3, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 1.1), 4.3, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X + 1.1), 4.3, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X - 1.1), 6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, (TEE_X + 1.1), 6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, (TEE_X + 1.7), 4.88, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, (TEE_X - 1.7), 4.88, gs, vec_ret);
																{
																	straight_line((2.375 - 1.5), 4.48, vec_ret);  //待优化
																}
															}
														}
													}
												}
											}
										}
									}
								}

							}
						}


					}
				}
			}

		}
		else if (flag_end == 1)		//
		{
			key = 0;
			if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2)) || (gs->body[endflag[0]][1] <= 4.88 && fabs(gs->body[endflag[0]][0] - 2.375) < 1.1))
			{
				for (i = 0; i < flagkey; i++)
				{
					if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1])) <= (get_dist(gs->body[keyflag[i]][0], gs->body[keyflag[i]][1])))
						key += 1;
				}
			}
			if (key > 0)
			{
				for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
				{
					if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
						//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
						break;
				}
				if (i >= gs->ShotNum)	//无遮挡
				{
					straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
					vec_ret->speed += 5;
				}
				else
				{
					if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
					{
						if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												straight_line(2.375, 4.88, vec_ret);  //待优化
												vec_ret->speed += 2;
											}

										}
									}
								}
							}
						}
					}
				}

			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2))
					{
						for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
						{
							if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
								//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
								break;
						}
						if (i >= gs->ShotNum)	//无遮挡
						{
							straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
							vec_ret->speed += 5;
						}
						else
						{
							if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
							{
								if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
								{
									Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														straight_line(2.375, 4.88, vec_ret);  //待优化
														vec_ret->speed += 2;
													}

												}
											}
										}
									}
								}
							}
						}
					}
					else
					{
						Path_occlusion_judgment1(16, 2.375, 4.8, gs, vec_ret);		//往营中心打
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											straight_line(2.375, 4.88, vec_ret);  //待优化
											vec_ret->speed += 2;
										}

									}
								}
							}
						}
					}
				}
			}

		}
		else
		{
			Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
			if (fabs(direction_flag) == 1)
			{
				if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(0.3, 2))
				{
					for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
					{
						if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
							//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
							break;
					}
					if (i >= gs->ShotNum)	//无遮挡
					{
						straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
						vec_ret->speed += 5;
					}
					else
					{
						if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
							{
								Path_occlusion_judgment1(16, 2.375, 4.76, gs, vec_ret);		//往营中心打
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													if (Hit3(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
													{
														straight_line(2.375, 4.88, vec_ret);  //待优化
														vec_ret->speed += 2;
													}

												}

											}
										}
									}
								}
							}
						}
					}
				}
				else
				{
					Path_occlusion_judgment1(16, 2.4, 4.8, gs, vec_ret);		//往营中心打
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										straight_line(2.375, 4.88, vec_ret);  //待优化
										vec_ret->speed += 2;
									}

								}
							}
						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}

/*
函数名：Second_player5
功能：  后手函数(在4的基础上修改推壶策略)
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/

void Second_player5(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	int rank[16];
	int j = 0;
	int flag_end = 0;				//最后一球记录大本营中对方的壶的个数
	int endflag[20] = { 20 };	//最后一球记录大本营中对方的壶的序号
	int i = 0;	//别乱用
	int st = 0;					//左偏右偏成功判断
	int flagkey = 0;//最后一个壶判断是否打定
	int keyflag[20] = { 20 };
	int key = 0;
	int k = 0;	//别乱用
	// sort by distance from center
	get_ranking(rank, gs);
	//straight_line((2.375 + 0.7), 6, vec_ret);
	switch (gs->ShotNum)
	{
	case 1:	Path_occlusion_judgment1(16, (TEE_X + 0.6), 6.95, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X + 0.7), 6.95, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X + 0.8), 6.95, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.6), 6.95, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X - 0.7), 6.95, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 6.95, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 + 0.7), 6, vec_ret);
							}

						}
					}
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 3:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[1] = 1;	//我方第一个壶被撞飞
		Path_occlusion_judgment1(16, (TEE_X - 0.6), 6.95, gs, vec_ret);
		if (fabs(direction_flag) == 1)
		{
			Path_occlusion_judgment1(16, (TEE_X - 0.7), 6.95, gs, vec_ret);
			if (fabs(direction_flag) == 1)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.8), 6.95, gs, vec_ret);
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.6), 6.95, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.7), 6.95, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 6.95, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
									straight_line((2.375 - 0.7), 6, vec_ret);
							}
						}
					}
				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 5:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[2] = 1;	//我方第2个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, (TEE_X - 0.5), 5.3, gs, vec_ret);	//往营里打
				if (fabs(direction_flag) == 1)
				{
					Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.5), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
							if (fabs(direction_flag) == 1)				//如果都被挡了
							{
								if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
								{
									if (flag1[0] % 2 != gs->ShotNum % 2) {
										// choose Shot 1. this case your opponent's curling is in the house
										Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
									}
									else {
										// choose Shot 2.
										Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																if (AddBall(gs, vec_ret) == ERROR)
																{
																	straight_line(2.375 + 0.8, 4.9, vec_ret);
																}

															}
														}
													}
												}
											}
										}
									}
								}
								else
								{
									if (AddBall(gs, vec_ret) == ERROR)
									{
										if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
										{
											straight_line((2.375 + 0.35), 4, vec_ret);	//不然直线入营（有待改进）
										}
										
									}
								}

							}


						}
					}

				}
			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 7:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[3] = 1;	//我方第3个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
			{
				if (AddBall(gs, vec_ret) == ERROR)
				{
					Path_occlusion_judgment1(16, (TEE_X + 0.5), 5.3, gs, vec_ret);	//往营里打
					if (fabs(direction_flag) == 1)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.8), 5, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.5), 4.88, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.8), 5, gs, vec_ret);
								if (fabs(direction_flag) == 1)				//如果都被挡了
								{
									if (is_in_House(gs->body[flag1[0]][0], gs->body[flag1[0]][1]))//这个球挡住了我的直线
									{
										if (flag1[0] % 2 != gs->ShotNum % 2) {
											// choose Shot 1. this case your opponent's curling is in the house
											Hit3(flag1[0], gs->body[flag1[0]][0], gs->body[flag1[0]][1], gs, vec_ret);	//打定
										}
										else {
											// choose Shot 2.
											Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
																if (fabs(direction_flag) == 1)
																{
																	if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
																	{
																		straight_line(2.375 - 0.8, 4.9, vec_ret);
																	}
																	
																}
															}
														}
													}
												}
											}
										}
									}
									else
									{
										if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
										{
											straight_line((2.375 - 0.35), 4, vec_ret);	//不然直线入营（有待改进）
										}
										
									}

								}


							}
						}

					}
				}
			}
		}


		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 9:	if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[4] = 1;	//我方第4个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.375 + 0.3, 4.88, gs, vec_ret);		//往营中心打，待优化
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.3, 4.9, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 - 0.4, 6.7, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.7, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
														{
															straight_line((2.375 + 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
														}
														
													}
												}
											}
										}
									}
								}
							}

						}

					}

				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;

	case 11:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[5] = 1;	//我方第5个壶被撞飞

	//while (j < gs->ShotNum)
	//{
	//	if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
	//		// choose Shot 1. this case your opponent's curling is in the house
	//		Hit1(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
	//		break;
	//	}
	//	else {
	//		// choose Shot 2.
	//		// this case your curling is in the house
	//		j++;
	//	}
	//}
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			j = 0;
			while (j < gs->ShotNum)
			{
				if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
					// choose Shot 1. this case your opponent's curling is in the house
					Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
				if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
				{
					if (AddBall(gs, vec_ret) == ERROR)
						straight_line(2.375 - 0.38, 4.88 + 1.8, vec_ret);		//打在大本营边缘
				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 13:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[6] = 1;	//我方第6个壶被撞飞
		if (Protect_First2(gs, vec_ret) == ERROR)
		{
			if (Hit2(gs, vec_ret) == ERROR)	//优先清中线
			{
				j = 0;
				while (j < gs->ShotNum)
				{
					if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true && (rank[j] % 2 != gs->ShotNum % 2)) {
						// choose Shot 1. this case your opponent's curling is in the house
						Hit3(rank[j], gs->body[rank[j]][0], gs->body[rank[j]][1], gs, vec_ret);
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
					if (Play_a_closer_ball2(gs, vec_ret) == ERROR)
					{
						if (AddBall(gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375 - 0.35, 4.88, gs, vec_ret);		//往营中心打，待优化
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, 2.375 + 0.35, 4.9, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, 2.375 + 0.4, 6.6, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, 2.375 - 0.4, 6.6, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, 2.375 + 0.6, 6.6, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, 2.375 - 0.6, 6.6, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, 2.375 - 1, 6.4, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, 2.375 + 1, 6.4, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
															{
																straight_line((2.375 - 0.8), 4.88, vec_ret);	//不然直线入营（有待改进）
															}
															
														}
													}
												}
											}
										}
									}
								}

							}

						}

					}
				}

			}
		}

		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	case 15:if (gs->body[gs->ShotNum - 2][1] < 3)
		flag2[7] = 1;	//我方第7个壶被撞飞
		j = 0;
		i = 0;
		k = 0;
		while (j < gs->ShotNum)
		{
			if (is_in_House(gs->body[rank[j]][0], gs->body[rank[j]][1]) == true)
			{
				// choose Shot 1. this case your opponent's curling is in the house
				if (rank[j] % 2 != gs->ShotNum % 2)
				{
					flag_end += 1;
					endflag[i++] = rank[j];
				}
				else
				{
					flagkey += 1;
					keyflag[k++] = rank[j];
				}
			}
			j++;
		}

		if (flag_end == 0)		//大本营中没有对方的壶
		{
			if (AddBall(gs, vec_ret) == ERROR)
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.88, gs, vec_ret);
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.88, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.8), 5.5, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.8), 5.5, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.8), 4.3, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.8), 4.3, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X - 1.1), 4.3, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X + 1.1), 4.3, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, (TEE_X - 1.1), 6, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															Path_occlusion_judgment1(16, (TEE_X + 1.1), 6, gs, vec_ret);
															if (fabs(direction_flag) == 1)
															{
																Path_occlusion_judgment1(16, (TEE_X + 1.7), 4.88, gs, vec_ret);
																if (fabs(direction_flag) == 1)
																{
																	Path_occlusion_judgment1(16, (TEE_X - 1.7), 4.88, gs, vec_ret);
																	{
																		straight_line((2.375 - 1.5), 4.48, vec_ret);  //待优化
																	}
																}
															}
														}
													}
												}
											}
										}
									}

								}
							}


						}
					}

				}
			}

		}
		else if (flag_end == 1)		//
		{
			key = 0;
			if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2)) || (gs->body[endflag[0]][1] <= 4.88 && fabs(gs->body[endflag[0]][0] - 2.375) < 1.1))
			{
				for (i = 0; i < flagkey; i++)
				{
					if ((get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1])) <= (get_dist(gs->body[keyflag[i]][0], gs->body[keyflag[i]][1])))
					{
						if(fabs(gs->body[endflag[0]][0]- gs->body[keyflag[i]][0])>0.31)
							key += 1;
					}
						
				}
			}
			if (key > 0)
			{
				for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
				{
					if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.31) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
						//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
						break;
				}
				if (i >= gs->ShotNum)	//无遮挡
				{
					straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
					vec_ret->speed += 5;
				}
				else
				{
					if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
					{
						if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
							if (fabs(direction_flag) == 1)
							{
								if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													if (Push1(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)//推壶
													{
														straight_line(2.375, 4.88, vec_ret);  //待优化
														vec_ret->speed += 2;
													}

												}

											}
										}
									}
								}

							}
						}
					}
				}

			}
			else
			{
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
				if (fabs(direction_flag) == 1)
				{
					if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
					{
						if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(HOUSE_R - 1, 2))
						{
							for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
							{
								if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.32) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
									//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
									break;
							}
							if (i >= gs->ShotNum)	//无遮挡
							{
								straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
								vec_ret->speed += 5;
							}
							else
							{
								if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
								{
									if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
									{
										Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
														if (fabs(direction_flag) == 1)
														{
															if (Push1(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)//推壶
															{
																straight_line(2.375, 4.88, vec_ret);  //待优化
																vec_ret->speed += 2;
															}
														}

													}
												}
											}
										}
									}
								}
							}
						}
						else
						{
							Path_occlusion_judgment1(16, 2.375, 4.8, gs, vec_ret);		//往营中心打
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												if (Push1(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)//推壶
												{
													straight_line(2.375, 4.88, vec_ret);  //待优化
													vec_ret->speed += 2;
												}
											}

										}
									}
								}
							}
						}
					}

				}
			}

		}
		else
		{
			Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);		//往营中心打
			if (fabs(direction_flag) == 1)
			{
				if (get_dist(gs->body[endflag[0]][0], gs->body[endflag[0]][1]) < pow(0.3, 2))
				{
					for (i = 0; i < gs->ShotNum; i++)     //直线球有无遮挡判断
					{
						if ((fabs(gs->body[i][0] - gs->body[endflag[0]][0]) < 0.31) && (i != endflag[0]) && (gs->body[i][1] > gs->body[endflag[0]][1]))
							//与x距离小于0.32且该冰壶不是目标冰壶并且不在目标冰壶的后方，说明有遮挡
							break;

					}
					if (i >= gs->ShotNum)	//无遮挡
					{
						straight_line(gs->body[endflag[0]][0], gs->body[endflag[0]][1], vec_ret);
						vec_ret->speed += 5;
					}
					else
					{
						if (Hit_zuoten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
						{
							if (Hit_youten(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
							{
								if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
								{
									Path_occlusion_judgment1(16, 2.375, 4.76, gs, vec_ret);		//往营中心打
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
											if (fabs(direction_flag) == 1)
											{
												Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
												if (fabs(direction_flag) == 1)
												{
													Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
													if (fabs(direction_flag) == 1)
													{
														if (Push1(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)//推壶
														{
															if (Hit3(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)
															{
																straight_line(2.375, 4.88, vec_ret);  //待优化
																vec_ret->speed += 2;
															}
														}


													}

												}
											}
										}
									}
								}
	
							}
						}
					}
				}
				else
				{
					if (Play_a_closer_ball3(gs, vec_ret) == ERROR)
					{
						Path_occlusion_judgment1(16, 2.4, 4.8, gs, vec_ret);		//往营中心打
						if (fabs(direction_flag) == 1)
						{
							Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.8, gs, vec_ret);
							if (fabs(direction_flag) == 1)
							{
								Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.8, gs, vec_ret);
								if (fabs(direction_flag) == 1)
								{
									Path_occlusion_judgment1(16, (TEE_X + 0.1), 4.75, gs, vec_ret);
									if (fabs(direction_flag) == 1)
									{
										Path_occlusion_judgment1(16, (TEE_X - 0.1), 4.75, gs, vec_ret);
										if (fabs(direction_flag) == 1)
										{
											if (Push1(endflag[0], gs->body[endflag[0]][0], gs->body[endflag[0]][1], gs, vec_ret) == ERROR)//推壶
											{
												straight_line(2.375, 4.88, vec_ret);  //待优化
												vec_ret->speed += 2;
											}
										}

									}
								}
							}
						}
					}

				}
			}
		}
		for (j = 0; j < 20; j++)
			flag1[j] = 0;
		break;
	default:straight_line(2.38, 4.88, vec_ret);
		vec_ret->speed += 1;
	}
}
/*lpy清场的得一分*/
/*
函数名：Second_player_lpy
功能：  后手函数
输入：  const GAMESTATE* const gs, SHOTINFO* vec_ret
返回值：无
*/
void Second_player_3_lpy(const GAMESTATE* const gs, SHOTINFO* vec_ret)
{
	switch (gs->ShotNum)
	{
	case 1:
	{
		if (is_in_House(gs->body[0][0], gs->body[0][1]))
			dashuai(gs, vec_ret, 0);
		else
		{
			straight_line(gs->body[0][0], gs->body[0][1], vec_ret);
			vec_ret->speed += 1.7;
		}
		break;
	}
	case 3:
	{
		if (is_in_House(gs->body[2][0], gs->body[2][1]))
			dashuai(gs, vec_ret, 2);
		else
		{
			straight_line(gs->body[2][0], gs->body[2][1], vec_ret);
			vec_ret->speed += 1.7;
		}
		break;
	}
	case 5:
	{
		if (is_in_House(gs->body[4][0], gs->body[4][1]))
			dashuai(gs, vec_ret, 2);
		else
		{
			straight_line(gs->body[4][0], gs->body[4][1], vec_ret);
			vec_ret->speed += 1.7;
		}
		break;
	}
	case 7:
	case 9:
	case 11:
	case 13:
	{
		int tmp = 0;
		int j;
		for (tmp = 0; tmp < gs->ShotNum; tmp += 2)
		{
			if (gs->body[tmp][1] != 0)
				break;
		}
		for (j = 2; j < gs->ShotNum; j += 2)
			if (get_dist(gs->body[j][0], gs->body[j][1]) < get_dist(gs->body[tmp][0], gs->body[tmp][1]))
				tmp = j;
		if (!(gs->body[tmp][0] == 0 && gs->body[tmp][1] == 0))
			dashuai(gs, vec_ret, tmp);
		else
			Path_occlusion_judgment1(16, 2.375, 3.2, gs, vec_ret);
		break;
	}
	case 15:
	{
		if (get_dist(gs->body[14][0], gs->body[14][1]) < HOUSE_R * 1 / 3)
		{
			Hit3(14, gs->body[14][0], gs->body[14][1], gs, vec_ret);
		}
		else
		{
			if (fabs(gs->body[14][0] - 2.375) < 0.32)
				Path_occlusion_judgment1(16, 2.875, 4.88, gs, vec_ret);
			else
				Path_occlusion_judgment1(16, 2.375, 4.88, gs, vec_ret);
		}
	}
	}
}