#pragma once
#include "Walec.h"

class Coin : public Walec
{
public:
	Coin(float x, float y, float z, double wysokosc, double promien, const char* color);
	~Coin();
	bool taken = true;
};

