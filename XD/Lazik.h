#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.
#include "Prostopadloscian.h"
#include "Walec.h"

class Lazik
{
public:
	Lazik(double x, double y, double z);
	~Lazik();

	double pos[3];
	Walec kolo_1;
	Walec kolo_2;
	Walec kolo_3;
	Walec kolo_4;
	Walec kolo_5;
	Walec kolo_6;
	Walec kolo_1a;
	Walec kolo_2a;
	Walec kolo_3a;
	Walec kolo_4a;
	Walec kolo_5a;
	Walec kolo_6a;
	Walec os1;
	//Walec os2;
	Prostopadloscian p1;
	Prostopadloscian p2;
	Prostopadloscian p3;
	Prostopadloscian p4;
	Prostopadloscian p5;
	Prostopadloscian p6;
	Prostopadloscian kadlub1;
	Prostopadloscian kadlub2;
	Prostopadloscian antena;
	Prostopadloscian ramie;
	Prostopadloscian ramie1;

	void rysujLazik();
};

