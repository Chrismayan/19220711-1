#pragma once
class Pair {
   public:
	int x, y;
	int val;

   public:
	Pair( );
	Pair(const int x, const int y);

	//使用曼哈顿距离的小顶堆比较函数
	bool operator<(const Pair& a) const;
};