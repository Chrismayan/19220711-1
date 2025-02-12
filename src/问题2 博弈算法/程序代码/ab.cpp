#include "ab.h"

#include <iostream>
#include <queue>
#include <vector>

#include "Board.h"
#include "Pair.h"

ab::ab(const char c[], int deep) {
	this->deep = deep;
	//Ȩֵ��ʼ��
	FILE* fp = fopen(c, "r");
	if (fp == NULL) {
		printf("Data file note exist\n");
		exit(1);
	}
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 4; b++) {
			for (int c = 0; c < 4; c++) {
				for (int d = 0; d < 4; d++) {
					for (int e = 0; e < 4; e++) {
						for (int f = 0; f < 4; f++) {
							fscanf(fp, "%d", &SCOREHASH[a][b][c][d][e][f]);
						}
					}
				}
			}
		}
	}
	fclose(fp);
}

ab::ab(int deep) {
	this->deep = deep;

	//Ȩֵ��ʼ��
	FILE* fp = fopen("dataV2.0.txt", "r");
	if (fp == NULL) {
		printf("Data file note exist\n");
		exit(1);
	}
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 4; b++) {
			for (int c = 0; c < 4; c++) {
				for (int d = 0; d < 4; d++) {
					for (int e = 0; e < 4; e++) {
						for (int f = 0; f < 4; f++) {
							fscanf(fp, "%d", &SCOREHASH[a][b][c][d][e][f]);
						}
					}
				}
			}
		}
	}
	fclose(fp);
}

Pair ab::find_Best_move(Board board_cur) {
	Pair move_Best;

	if (board_cur.empty == 0) {	 //��������
		return move_Best;
	}

	//���������ӵ�
	int val;
	int max = MAX;
	int min = MIN;
	Pair move_temp;

	//��һ��
	move_temp.x = 7;
	move_temp.y = 7;
	if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
		Board board_new(board_cur);				   //����������
		board_new.move(move_temp);				   //��һ��
		val = Alpha_Beta(board_new, MIN, MAX, 1);  //��ǰ�����������ֵ
		// ��������  ��ɫѡval��� ��ɫѡvalС��
		switch (board_cur.turn) {
			case BLACK:
				if (val > min) {
					min = val;
					move_Best = move_temp;
					move_Best.val = min;
				}
				break;
			case WHITE:
				if (val < max) {
					max = val;
					move_Best = move_temp;
					move_Best.val = max;
				}
				break;
		}
	}  //֮���ÿ����

	for (int i = 3; i <= 15; i += 2) {	//ÿһȦ
		move_temp.x++, move_temp.y++;
		for (int dir = 0; dir < 4; dir++) {	   //�ĸ�����
			for (int k = 0; k < i - 1; k++) {  //ÿ������
				if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
					Board board_new(board_cur);				   //����������
					board_new.move(move_temp);				   //��һ��
					val = Alpha_Beta(board_new, MIN, MAX, 1);  //��ǰ�����������ֵ
					// ��������  ��ɫѡval��� ��ɫѡvalС��
					switch (board_cur.turn) {
						case BLACK:
							if (val > min) {
								min = val;
								move_Best = move_temp;
								move_Best.val = min;
							}
							break;
						case WHITE:
							if (val < max) {
								max = val;
								move_Best = move_temp;
								move_Best.val = max;
							}
							break;
					}
				}
				move_temp.x += Board::CIR[dir][0];
				move_temp.y += Board::CIR[dir][1];
			}
		}
	}
	return move_Best;
}

int ab::Alpha_Beta(Board board_cur, int alpha, int beta, int depth) {
	if (depth == this->deep) {
		return assessment(board_cur);
	}
	//���������ӵ�
	int val;
	Pair move_temp;

	//��һ��
	move_temp.x = 7;
	move_temp.y = 7;
	if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
		Board board_new(board_cur);							  //����������
		board_new.move(move_temp);							  //��һ��
		val = Alpha_Beta(board_new, alpha, beta, depth + 1);  //��ǰ�����������ֵ

		switch (board_cur.turn) {
			case BLACK:
				if (val > alpha) {
					alpha = val;
				}
				if (alpha >= beta) {
					return alpha;
				}
				break;
			case WHITE:
				if (val < beta) {
					beta = val;
				}
				if (alpha >= beta) {
					return beta;
				}
				break;
		}
	}  //֮���ÿ����

	for (int i = 3; i <= 15; i += 2) {	//ÿһȦ
		move_temp.x++, move_temp.y++;
		for (int dir = 0; dir < 4; dir++) {	   //�ĸ�����
			for (int k = 0; k < i - 1; k++) {  //ÿ������
				if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
					Board board_new(board_cur);							  //����������
					board_new.move(move_temp);							  //��һ��
					val = Alpha_Beta(board_new, alpha, beta, depth + 1);  //��ǰ�����������ֵ

					switch (board_cur.turn) {
						case BLACK:
							if (val > alpha) {
								alpha = val;
							}
							if (alpha >= beta) {
								return alpha;
							}
							break;
						case WHITE:
							if (val < beta) {
								beta = val;
							}
							if (alpha >= beta) {
								return beta;
							}
							break;
					}
				}
				move_temp.x += Board::CIR[dir][0];
				move_temp.y += Board::CIR[dir][1];
			}
		}
	}

	switch (board_cur.turn) {
		case BLACK:
			return alpha;
		case WHITE:
			return beta;
	}
}

int ab::assessment(Board& board_cur) {
	int res = 0;
	int res_black = 0;
	int res_white = 0;
	int x, y;
	int color[6];
	int part = 0, part_real = 0, part_abs = 0;
	//����ÿ������
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			//�յĵ㲻����
			if (board_cur.board[i][j] == EMPTY) {
				continue;
			}
			//�ȱ���4������
			for (int d = 0; d < 4; d++) {
				//����5��������7������
				for (int k = -5; k <= -1; k++) {
					part = 0, part_real = 0, part_abs = 0;
					//������ɫ ������������
					for (int z = 0; z < 6; z++) {
						x = i + Board::DIR[d][0] * (k + z);
						y = j + Board::DIR[d][1] * (k + z);
						if ((x >= 0 && x < 15) && (y >= 0 && y < 15)) {	 //�ж�����Ϸ� ʹ�ú������û�Ӱ������
							color[z] = board_cur.board[x][y];
						} else {
							color[z] = OUT;
						}
					}
					int part_real = SCOREHASH[color[0]][color[1]][color[2]][color[3]][color[4]][color[5]];
					//�������
					if ((part_real > 0 && board_cur.turn == BLACK) || (part_real < 0 && board_cur.turn == WHITE)) {
						part_real *= 2;
					}
					double abso = abs(part_real);
					if (part_abs < abso) {
						part = part_real;
						part_abs = abs(part);
					}
				}
				res += part;
			}
		}
	}
	return res;
}
