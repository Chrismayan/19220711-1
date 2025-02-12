#pragma once
#include"Pair.h"

#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define OUT 3

class Board {
public:
	const static int DIR[4][2];
	const static int CIR[4][2];

	int board[15][15];	//棋盘

	int winner;
	int turn;			//落子方
	int full, empty;	//已落子  未落子
	Pair premove;		//上一步

public:
	//初始化函数
	void init();

	//落子
	bool move(const Pair &m);

	//判断落子合法
	inline bool judge_Legal(const int x, const int y);

	//判断胜负
	int judge_Win();

	//打印棋盘
	void print();
};