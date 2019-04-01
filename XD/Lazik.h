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

	void rysujLazik();
};

