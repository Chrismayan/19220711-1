#include "ab.h"

#include <iostream>
#include <queue>
#include <vector>

#include "Board.h"
#include "Pair.h"

ab::ab(const char c[], int deep) {
	this->deep = deep;
	//权值初始化
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

	//权值初始化
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

	if (board_cur.empty == 0) {	 //棋盘已满
		return move_Best;
	}

	//遍历可落子点
	int val;
	int max = MAX;
	int min = MIN;
	Pair move_temp;

	//第一步
	move_temp.x = 7;
	move_temp.y = 7;
	if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
		Board board_new(board_cur);				   //拷贝新棋盘
		board_new.move(move_temp);				   //走一步
		val = Alpha_Beta(board_new, MIN, MAX, 1);  //当前局面的搜索估值
		// 更新落子  黑色选val大的 白色选val小的
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
	}  //之后的每个点

	for (int i = 3; i <= 15; i += 2) {	//每一圈
		move_temp.x++, move_temp.y++;
		for (int dir = 0; dir < 4; dir++) {	   //四个方向
			for (int k = 0; k < i - 1; k++) {  //每颗棋子
				if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
					Board board_new(board_cur);				   //拷贝新棋盘
					board_new.move(move_temp);				   //走一步
					val = Alpha_Beta(board_new, MIN, MAX, 1);  //当前局面的搜索估值
					// 更新落子  黑色选val大的 白色选val小的
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
	//遍历可落子点
	int val;
	Pair move_temp;

	//第一步
	move_temp.x = 7;
	move_temp.y = 7;
	if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
		Board board_new(board_cur);							  //拷贝新棋盘
		board_new.move(move_temp);							  //走一步
		val = Alpha_Beta(board_new, alpha, beta, depth + 1);  //当前局面的搜索估值

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
	}  //之后的每个点

	for (int i = 3; i <= 15; i += 2) {	//每一圈
		move_temp.x++, move_temp.y++;
		for (int dir = 0; dir < 4; dir++) {	   //四个方向
			for (int k = 0; k < i - 1; k++) {  //每颗棋子
				if (board_cur.board[move_temp.x][move_temp.y] == EMPTY) {
					Board board_new(board_cur);							  //拷贝新棋盘
					board_new.move(move_temp);							  //走一步
					val = Alpha_Beta(board_new, alpha, beta, depth + 1);  //当前局面的搜索估值

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
	//遍历每颗棋子
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			//空的点不搜索
			if (board_cur.board[i][j] == EMPTY) {
				continue;
			}
			//比遍历4个方向
			for (int d = 0; d < 4; d++) {
				//遍历5组连续的7颗棋子
				for (int k = -5; k <= -1; k++) {
					part = 0, part_real = 0, part_abs = 0;
					//棋子颜色 拷贝到新数组
					for (int z = 0; z < 6; z++) {
						x = i + Board::DIR[d][0] * (k + z);
						y = j + Board::DIR[d][1] * (k + z);
						if ((x >= 0 && x < 15) && (y >= 0 && y < 15)) {	 //判断坐标合法 使用函数调用会影响性能
							color[z] = board_cur.board[x][y];
						} else {
							color[z] = OUT;
						}
					}
					int part_real = SCOREHASH[color[0]][color[1]][color[2]][color[3]][color[4]][color[5]];
					//评分相加
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
