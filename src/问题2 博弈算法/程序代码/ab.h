#pragma once
#include<thread>
#include"Pair.h"
#include"Board.h"

#define MIN -2147483647
#define MAX 2147483647

class ab {
public:
	int deep;	//����������

public:
	//���캯��
	ab(int deep);
	ab(const char c[], int deep);

	//Ѱ����õ�����
	Pair find_Best_move(Board board_cur);

	//��-������
	int Alpha_Beta(Board board_cur, int alpha, int beta, int depth);

	//������������  ����Ϊ��������Ϊ��
	int assessment(Board& board_cur);

private:
	//�������־���
	int SCOREHASH[4][4][4][4][4][4] = { 0 };

	/*�������� V1.0*/
	//�����������ֺ���
	//static int getScore(int cnt, int gas);
	//������������
	//static void dir1(Board board_cur, Score* res);	//����
	//static void dir2(Board board_cur, Score* res);	//����
	//static void dir31(Board board_cur, Score* res);// ����'\'��
	//static void dir32(Board board_cur, Score* res);// ����'\'��
	//static void dir41(Board board_cur, Score* res);// ����'/'��
	//static void dir42(Board board_cur, Score* res);// ����'/'��
};

