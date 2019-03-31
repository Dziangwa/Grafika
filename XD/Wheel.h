#pragma once
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>          // About box resource identifiers.

class Wheel
{
public:
	Wheel(float x, float y, float z);
	~Wheel();

	GLfloat pos[3];
	//s
	void rysujKolo();
	void ustawPozycje(float x, float y, float z);
};

