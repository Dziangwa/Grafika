#include "Wheel.h"



Wheel::Wheel(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}


Wheel::~Wheel()
{
}

void Wheel::rysujKolo()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); {

		GLfloat temp[3] = { pos[0], pos[1] - 5, pos[2] };
		GLfloat okrag[3];
		okrag[2] = pos[2] - 5;
		okrag[1] = temp[1];
		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(temp);

		for (float i = 0; i < 6.28; i += 0.01) {
			okrag[0] = temp[0] - 5 * sin(i);
			okrag[2] = temp[2] - 5 * cos(i);
			glVertex3fv(okrag);
		}
		glEnd();

		GLfloat temp2[3] = { pos[0], pos[1] + 5, pos[2] };
		GLfloat okrag2[3];
		okrag2[2] = pos[2] - 5;
		okrag2[1] = temp2[1];

		glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(temp2);

		for (float i = 0; i < 6.28; i += 0.01) {
			okrag2[0] = temp2[0] - 5 * sin(i);
			okrag2[2] = temp2[2] - 5 * cos(i);
			glVertex3fv(okrag2);
		}
		glEnd();


		GLfloat okrag3[3] = { temp[0], temp[1], temp[2] - 5 };

		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0, 0, 0);
		for (float i = 0; i < 6.28; i += 0.01) {
			if (okrag3[1] == temp[1]) {
				okrag3[1] = temp[1] + 10;
			}
			else {
				okrag3[1] = temp[1];
			}

			okrag3[0] = temp[0] - 5 * sin(i);
			okrag3[2] = temp[2] - 5 * cos(i);

			glVertex3fv(okrag3);
		}
		glEnd();
	}
}

void Wheel::ustawPozycje(float x, float y, float z)
{
	//teqweqwe123w
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}
