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

	int board[15][15];	//����

	int winner;
	int turn;			//���ӷ�
	int full, empty;	//������  δ����
	Pair premove;		//��һ��

public:
	//��ʼ������
	void init();

	//����
	bool move(const Pair &m);

	//�ж����ӺϷ�
	inline bool judge_Legal(const int x, const int y);

	//�ж�ʤ��
	int judge_Win();

	//��ӡ����
	void print();
};