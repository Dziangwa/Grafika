#include "Coin.h"



Coin::Coin(float x, float y, float z, double wysokosc, double promien, const char* color)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	wysokoscWalca = wysokosc;
	promienWalca = promien;
	this->color = color;
}

Coin::~Coin()
{
}
