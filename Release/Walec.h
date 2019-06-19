#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.

class Walec
{
public:
	Walec();
	Walec(float x, float y, float z, double wysokosc, double promien, const char* color);
	~Walec();

	GLfloat pos[3];
	double wysokoscWalca;
	double promienWalca;
	double x, y, z;
	const char* color;
	//s
	void rysujWalec();
	void ustawPozycje(float x, float y, float z);
};

