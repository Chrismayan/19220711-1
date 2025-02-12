#include<iostream>

#include"Board.h"
#include"ab.h"

using namespace std;

void People_vs_Computer() {
	int turn;
	bool legal;
	Pair move;

	ab ab(3);		//ʵ��������AI
	Board board;	//ʵ��������
	board.init();	//���̳�ʼ��

	printf("Chose your color\n    1 for black\n    2 for white\n >");
	scanf("%d", &turn);
	if (turn == 2) {	//AI����
		move = ab.find_Best_move(board);	//����һ��
		legal = board.move(move);			//����
		board.judge_Win();				//�жϻ�ʤ��
		board.print();

		printf("\nmove val:%d\n", move.val);
		printf("AI move:%d %d\n", move.x, move.y);
	}


	while (true) {
		//����һ��
		printf("\nEnter your move>");
		scanf("%d %d", &move.x, &move.y);
		legal = board.move(move);	//����
		board.judge_Win();				//�жϻ�ʤ��

		board.print();
		if (legal) {
			printf("\nYour move:%d %d\n", move.x, move.y);
		}
		else {
			printf("\nillegal move:%d %d\n", move.x, move.y);
		}
		//�Ծֽ���
		if (board.winner != EMPTY) {
			break;
		}


		//AI��һ��
		move = ab.find_Best_move(board);//����һ��
		legal = board.move(move);		//����
		board.judge_Win();				//�жϻ�ʤ��

		board.print();					//��ӡ����
		printf("\nmove val:%d\n", move.val);
		printf("AI move:%d %d\n", move.x, move.y);
		//�Ծֽ���
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

		legal = board.move(move);			//����
		board.judge_Win();				//�жϻ�ʤ��
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