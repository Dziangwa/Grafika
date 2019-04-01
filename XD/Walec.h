#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.

class Walec
{
public:
	Walec(float x, float y, float z, double wysokosc, double promien);
	~Walec();

	GLfloat pos[3];
	double wysokoscWalca;
	double promienWalca;
	//s
	void rysujWalec();
	void ustawPozycje(float x, float y, float z);
};

