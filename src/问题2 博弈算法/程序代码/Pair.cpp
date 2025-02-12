#include<math.h>
#include"Pair.h"

Pair::Pair() {
	x = -1; 
	y = -1;
	val = 0;
}

Pair::Pair(const int x,const int y) {
	this->x = x;
	this->y = y;
	this->val = 0;
}

bool Pair::operator<(const Pair& a)const {
	return (abs(x - 7) + abs(y - 7)) > (abs(a.x - 7) + abs(a.y - 7));
}
