#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.

class Prostopadloscian
{
public:
	Prostopadloscian(double x, double y, double z,
		double dlugosc, double szerokosc, double wysokosc, double ang, int kolor);
	~Prostopadloscian();

	double wymiary[3];
	double pos[3];

	int color;
	double angle;
	const int szer = 1;
	const int wys = 2;
	const int dlug = 0;

	void rysujPro();

	GLfloat Jabko[6][3] = {
	{0,0,0},
	{0.59,0.294,0},
	{1,0,0},
	{0,1,0},
	{0,0,1},
	{1,1,0}
	};
};
