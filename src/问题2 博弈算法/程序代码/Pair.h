#pragma once
class Pair {
   public:
	int x, y;
	int val;

   public:
	Pair( );
	Pair(const int x, const int y);

	//ʹ�������پ����С���ѱȽϺ���
	bool operator<(const Pair& a) const;
};