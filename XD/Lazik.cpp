#include "Lazik.h"



Lazik::Lazik(double x, double y, double z)
	:pos{ x,y,z },
	kolo_1(pos[0] - 40, pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_2(pos[0] - 40, pos[1] + 30, pos[2] - 20, 10, 10),
	kolo_3(pos[0], pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_4(pos[0], pos[1] + 30, pos[2] - 20, 10, 10),
	kolo_5(pos[0] + 40, pos[1] - 30, pos[2] - 20, 10, 10),
	kolo_6(pos[0] + 40, pos[1] + 30, pos[2] - 20, 10, 10),
	kolo_1a(pos[0] - 40, pos[1] - 23.75, pos[2] - 20, 2.5, 2.5),
	kolo_2a(pos[0] - 40, pos[1] + 23.75, pos[2] - 20, 2.5, 2.5),
	kolo_3a(pos[0], pos[1] - 23.75, pos[2] - 20, 2.5, 2.5),
	kolo_4a(pos[0], pos[1] + 23.75, pos[2] - 20, 2.5, 2.5),
	kolo_5a(pos[0] + 40, pos[1] - 23.75, pos[2] - 20, 2.5, 2.5),
	kolo_6a(pos[0] + 40, pos[1] + 23.75, pos[2] - 20, 2.5, 2.5),
	p1(pos[0] - 40, pos[1] - 22.5, pos[2] - 22.5, 40*sqrt(3)/3, 5, 5, 3.14 / 6),
	p2(pos[0] - 40, pos[1] + 17.5, pos[2] - 22.5, 40*sqrt(3)/3, 5, 5, 3.14 / 6),
	p3(pos[0] - 20, pos[1] - 22.5, pos[2] + 20*sqrt(3)/3 - 22.5, 40 * sqrt(3) / 3, 5, 5, 3.14 * 2 - 3.14/6),
	p4(pos[0] - 20, pos[1] + 17.5, pos[2] + 20*sqrt(3)/3 - 22.5, 40 * sqrt(3) / 3, 5, 5, 3.14 * 2 - 3.14/6),
	p5(pos[0] + 20, pos[1] - 22.5, pos[2], 22 * sqrt(2), 5, 5, 3.14 * 2 - 3.14 / 4),
	p6(pos[0] + 20, pos[1] + 17.5, pos[2], 22 * sqrt(2), 5, 5, 3.14 * 2 - 3.14 / 4),
	os1(pos[0] - 20, pos[1], pos[2] + 20*sqrt(3)/3 - 20, 35, 2.5),
	os2(pos[0] + 22, pos[1], pos[2], 35, 2.5),
	kadlub1(pos[0] - 30, pos[1] - 17.5, pos[2] + 20 * sqrt(3) / 3 - 20, 70, 35, 13, 0),
	kadlub2(pos[0], pos[1] - 17.5, pos[2] + 20 * sqrt(3) / 3 - 7, 40, 35, 20, 0),
	antena(pos[0] + 30, pos[1] + 10, pos[2] + 20 * sqrt(3) / 3 + 13, 30, 2.5, 2.5, 3.14 / 2),
	ramie(pos[0] - 15, pos[1] - 2.5, pos[2] + 3, 40, 5, 5, 3.14*3/4),
	ramie1(pos[0] - 15 - 20*sqrt(2), pos[1] - 2.5, pos[2] + 3 + 20*sqrt(2), 50, 5, 5, 3.14 + 3.14/6)
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
	kolo_1a.rysujWalec();
	kolo_2a.rysujWalec();
	kolo_3a.rysujWalec();
	kolo_4a.rysujWalec();
	kolo_5a.rysujWalec();
	kolo_6a.rysujWalec();
	p1.rysujPro();
	p2.rysujPro();
	p3.rysujPro();
	p4.rysujPro();
	p5.rysujPro();
	p6.rysujPro();
	os1.rysujWalec();
	os2.rysujWalec();
	kadlub1.rysujPro();
	kadlub2.rysujPro();
	antena.rysujPro();
	ramie.rysujPro();
	ramie1.rysujPro();
}