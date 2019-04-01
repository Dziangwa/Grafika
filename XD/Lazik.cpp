#include "Lazik.h"



Lazik::Lazik(double x, double y, double z)
	:pos{ x,y,z },
	kolo_1(pos[0] - 40, pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_2(pos[0] - 40, pos[1] + 30, pos[2] - 20, 10, 10),
	kolo_3(pos[0], pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_4(pos[0], pos[1] + 30, pos[2] - 20, 10, 10),
	kolo_5(pos[0] + 40, pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_6(pos[0] + 40, pos[1] + 30, pos[2] - 20, 10, 10)
{
}


Lazik::~Lazik()
{
}

void Lazik::rysujLazik() {
	kolo_1.rysujWalec();
	kolo_2.rysujWalec();
	kolo_3.rysujWalec();
	kolo_4.rysujWalec();
	kolo_5.rysujWalec();
	kolo_6.rysujWalec();
}