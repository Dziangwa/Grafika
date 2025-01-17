#include "Walec.h"



Walec::Walec()
{
}

Walec::Walec(float x, float y, float z, double wysokosc, double promien, const char* color)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	wysokoscWalca = wysokosc;
	promienWalca = promien;
	this->color = color;
}


Walec::~Walec()
{
}

void Walec::rysujWalec()
{
	if (color == "czarny") {
		x = 0;
		y = 0;
		z = 0;
	}
	else if (color == "zolty") {
		x = 0.9;
		y = 0.9;
		z = 0;
	}


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); {

		GLfloat temp[3] = { pos[0], pos[1] - wysokoscWalca/2, pos[2] };
		GLfloat okrag[3];
		okrag[2] = pos[2] - wysokoscWalca/2;
		okrag[1] = temp[1];
		glColor3f(x + 0.1, y + 0.1, z + 0.1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(temp);

		for (float i = 0; i < 6.28; i += 0.001) {
			okrag[0] = temp[0] - promienWalca * sin(i);
			okrag[2] = temp[2] - promienWalca * cos(i);
			glVertex3fv(okrag);
		}
		glEnd();

		GLfloat temp2[3] = { pos[0], pos[1] + wysokoscWalca/2, pos[2] };
		GLfloat okrag2[3];
		okrag2[2] = pos[2] - wysokoscWalca/2;
		okrag2[1] = temp2[1];

		glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(temp2);

		for (float i = 0; i < 6.28; i += 0.001) {
			okrag2[0] = temp2[0] - promienWalca * sin(i);
			okrag2[2] = temp2[2] - promienWalca * cos(i);
			glVertex3fv(okrag2);
		}
		glEnd();


		GLfloat okrag3[3] = { temp[0], temp[1], temp[2] - wysokoscWalca/2 };

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(x, y, z);
		for (float i = 0; i < 6.28; i += 0.001) {
			if (okrag3[1] == temp[1]) {
				okrag3[1] = temp[1] + wysokoscWalca;
			}
			else {
				okrag3[1] = temp[1];
			}

			okrag3[0] = temp[0] - promienWalca * sin(i);
			okrag3[2] = temp[2] - promienWalca * cos(i);

			glVertex3fv(okrag3);
		}
		glEnd();
	}
}

void Walec::ustawPozycje(float x, float y, float z)
{
	//teqweqwe123w
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}
