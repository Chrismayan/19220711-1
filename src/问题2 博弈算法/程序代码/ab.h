#pragma once
#include<thread>
#include"Pair.h"
#include"Board.h"

#define MIN -2147483647
#define MAX 2147483647

class ab {
public:
	int deep;	//最大搜索深度

public:
	//构造函数
	ab(int deep);
	ab(const char c[], int deep);

	//寻找最好的落子
	Pair find_Best_move(Board board_cur);

	//α-β搜索
	int Alpha_Beta(Board board_cur, int alpha, int beta, int depth);

	//局面评估函数  黑棋为正，白棋为负
	int assessment(Board& board_cur);

private:
	//棋形评分矩阵
	int SCOREHASH[4][4][4][4][4][4] = { 0 };

	/*评估函数 V1.0*/
	//连续棋子评分函数
	//static int getScore(int cnt, int gas);
	//局面评估函数
	//static void dir1(Board board_cur, Score* res);	//横向
	//static void dir2(Board board_cur, Score* res);	//纵向
	//static void dir31(Board board_cur, Score* res);// 左下'\'向
	//static void dir32(Board board_cur, Score* res);// 右上'\'向
	//static void dir41(Board board_cur, Score* res);// 左上'/'向
	//static void dir42(Board board_cur, Score* res);// 右下'/'向
};

