#include<iostream>

#include"Board.h"
#include"ab.h"

using namespace std;

void People_vs_Computer() {
	int turn;
	bool legal;
	Pair move;

	ab ab(3);		//实例化搜索AI
	Board board;	//实例化棋盘
	board.init();	//棋盘初始化

	printf("Chose your color\n    1 for black\n    2 for white\n >");
	scanf("%d", &turn);
	if (turn == 2) {	//AI先行
		move = ab.find_Best_move(board);	//计算一步
		legal = board.move(move);			//落子
		board.judge_Win();				//判断获胜方
		board.print();

		printf("\nmove val:%d\n", move.val);
		printf("AI move:%d %d\n", move.x, move.y);
	}


	while (true) {
		//人走一步
		printf("\nEnter your move>");
		scanf("%d %d", &move.x, &move.y);
		legal = board.move(move);	//落子
		board.judge_Win();				//判断获胜方

		board.print();
		if (legal) {
			printf("\nYour move:%d %d\n", move.x, move.y);
		}
		else {
			printf("\nillegal move:%d %d\n", move.x, move.y);
		}
		//对局结束
		if (board.winner != EMPTY) {
			break;
		}


		//AI走一步
		move = ab.find_Best_move(board);//计算一步
		legal = board.move(move);		//落子
		board.judge_Win();				//判断获胜方

		board.print();					//打印局面
		printf("\nmove val:%d\n", move.val);
		printf("AI move:%d %d\n", move.x, move.y);
		//对局结束
		if (board.winner != EMPTY) {
			break;
		}
	}
}

int Computer_vs_Computer() {
	int turn;
	bool legal;
	Pair move;

	ab AI_1("dataV1.0.txt", 2);
	ab AI_2("dataV2.0.txt", 2);

	Board board;
	board.init();

	turn = BLACK;
	int z = 0;
	getchar();
	while (true) {
		if (turn == BLACK) {
			move = AI_1.find_Best_move(board);
		}
		else {
			move = AI_2.find_Best_move(board);
		}

		legal = board.move(move);			//落子
		board.judge_Win();				//判断获胜方
		board.print();

		if (turn == BLACK) {
			printf("\nmove val:%d\n", move.val);
			printf("AI_1 move:%d %d\n", move.x, move.y);
		}
		else {
			printf("\nmove val:%d\n", move.val);
			printf("AI_2 move:%d %d\n", move.x, move.y);
		}

		if (board.winner != EMPTY) {
			return board.winner;
		}
		turn = turn ^ 1;
		z++;
		if (z == 10) {
			printf("Stop\n");
			getchar();
		}
	}
	
}

int main() {
	People_vs_Computer();
	//printf("%d\n",Computer_vs_Computer());
	//printf("%d", 2 ^ 1);
}