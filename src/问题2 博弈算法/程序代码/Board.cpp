#include<iostream>

#include"Board.h"
#include"Pair.h"

const int Board::DIR[4][2] = {
	{1,0},	// '|'
	{0,1},	// '����'
	{1,1},	// '\'
	{1,-1}	// '/'
};
const int Board::CIR[4][2] = {
	{-1,0},
	{0,-1},
	{1,0},
	{0,1}
};

void Board::init() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			this->board[i][j] = EMPTY;
		}
	}

	winner = EMPTY;
	turn = BLACK;
	full = 0;
	empty = 225;
}

bool Board::judge_Legal(const int x, const int y) {
	return (x >= 0 && x < 15) && (y >= 0 && y < 15);
}

bool Board::move(const Pair& m) {
	if (!(judge_Legal(m.x, m.y) && board[m.x][m.y] == EMPTY)) {
		return false;
	}
	board[m.x][m.y] = this->turn;
	this->turn ^= 1;	//�������ӷ�
	this->full++;
	this->empty--;
	this->premove = m;	//������һ��
	return true;
}

int Board::judge_Win() {
	int x, y;
	int color, cnt;
	for (int d=0; d < 4; d++) {
		color = EMPTY, cnt = 0;
		for (int k = -4; k <=4; k++) {//���������Ÿ�����
			//����������
			x = this->premove.x + this->DIR[d][0] * k;
			y = this->premove.y + this->DIR[d][1] * k;
			//״̬������
			if (judge_Legal(x, y)) {	//����Ϸ�
				if (board[x][y] == EMPTY) {
					color = EMPTY;
					cnt = 0;
				}
				else {
					if (board[x][y] == color) {
						cnt ++;
					}
					else {
						color = board[x][y];
						cnt = 1;
					}
				}
			}
			else {	//����Ƿ�  ��������
				if (k > 0) {
					break;	//���������̣�����������
				}
			}
			//����5�����ӣ���ֹ
			if (cnt == 5) {
				this->winner = color;
				return color;
			}
		}
	}
	return EMPTY;
}

void Board::print() {
	//����Ļ
	system("cls");	
	
	// ��ӡ����
	printf("   ");
	for (int i = 0; i < 14; i++) {
		printf("%2d ", i);
	}
	printf("14\n");
	for (int i = 0; i < 15; i++) {
		printf("%2d  ", i);
		for (int j = 0; j < 14; j++) {
			switch (board[i][j]) {
			case EMPTY:
				printf("-  ");
				break;
			case BLACK:
				printf("*  ");
				break;
			case WHITE:
				printf("o  ");
				break;
			}
		}
		switch (board[i][14]) {
		case EMPTY:
			printf("-\n");
			break;
		case BLACK:
			printf("*\n");
			break;
		case WHITE:
			printf("o\n");
			break;
		}
	}
	//����Ծֽ��������
	if (winner != EMPTY) {
		switch (turn) {
		case BLACK:
			printf("White win!\n");
			break;
		case WHITE:
			printf("Black win!\n");
		}
	}
}