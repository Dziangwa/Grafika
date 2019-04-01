#include "Prostopadloscian.h"



Prostopadloscian::Prostopadloscian(double x, double y, double z, double dlugosc, double szerokosc, double wysokosc)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	wymiary[dlug] = dlugosc;
	wymiary[szer] = szerokosc;
	wymiary[wys] = wysokosc;
}

Prostopadloscian::~Prostopadloscian()
{
}

void Prostopadloscian::rysujPro() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		GLfloat sa[3] = {pos[0], pos[1], pos[2]};
		GLfloat sb[3] = {pos[0], pos[1], pos[2] + wymiary[2]};
		GLfloat sc[3] = {pos[0] + (wymiary[0]/4), pos[1], pos[2]};
		GLfloat sd[3] = { pos[0] + (wymiary[0] / 4), pos[1], pos[2] + wymiary[2] };
		GLfloat se[3] = { pos[0] + (wymiary[0]/2), pos[1], pos[2] };
		GLfloat sf[3] = { pos[0] + (wymiary[0]/2), pos[1], pos[2] + wymiary[2] };
		GLfloat sg[3] = { pos[0] + (wymiary[0]*3/4), pos[1], pos[2] };
		GLfloat sh[3] = { pos[0] + (wymiary[0]*3/4), pos[1], pos[2] + wymiary[2] };
		GLfloat si[3] = { pos[0] + wymiary[0], pos[1], pos[2] };
		GLfloat sj[3] = { pos[0] + wymiary[0], pos[1], pos[2] + wymiary[2] };

		/*glBegin(GL_TRIANGLE_FAN);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glVertex3fv(se);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glVertex3fv(sj);
		glVertex3fv(sj);

		glEnd();*/

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sb);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glVertex3fv(sj);
		glVertex3fv(si);
		glEnd();

		GLfloat ssa[3] = { pos[0], pos[1] + wymiary[1], pos[2] };
		GLfloat ssb[3] = { pos[0], pos[1] + wymiary[1], pos[2] + wymiary[2] };
		GLfloat ssc[3] = { pos[0] + (wymiary[0] / 4), pos[1] + wymiary[1], pos[2] };
		GLfloat ssd[3] = { pos[0] + (wymiary[0] / 4), pos[1] + wymiary[1], pos[2] + wymiary[2] };
		GLfloat sse[3] = { pos[0] + (wymiary[0] / 2), pos[1] + wymiary[1], pos[2] };
		GLfloat ssf[3] = { pos[0] + (wymiary[0] / 2), pos[1] + wymiary[1], pos[2] + wymiary[2] };
		GLfloat ssg[3] = { pos[0] + (wymiary[0] * 3 / 4), pos[1] + wymiary[1], pos[2] };
		GLfloat ssh[3] = { pos[0] + (wymiary[0] * 3 / 4), pos[1] + wymiary[1], pos[2] + wymiary[2] };
		GLfloat ssi[3] = { pos[0] + wymiary[0], pos[1] + wymiary[1], pos[2] };
		GLfloat ssj[3] = { pos[0] + wymiary[0], pos[1] + wymiary[1], pos[2] + wymiary[2] };

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(ssb);
		glVertex3fv(ssa);
		glVertex3fv(ssd);
		glVertex3fv(ssc);
		glVertex3fv(ssf);
		glVertex3fv(sse);
		glVertex3fv(ssh);
		glVertex3fv(ssg);
		glVertex3fv(ssj);
		glVertex3fv(ssi);
		glEnd();

		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sb);
		glVertex3fv(ssb);
		glVertex3fv(sd);
		glVertex3fv(ssd);
		glVertex3fv(sf);
		glVertex3fv(ssf);
		glVertex3fv(sh);
		glVertex3fv(ssh);
		glVertex3fv(sj);
		glVertex3fv(ssj);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sa);
		glVertex3fv(ssa);
		glVertex3fv(sc);
		glVertex3fv(ssc);
		glVertex3fv(se);
		glVertex3fv(sse);
		glVertex3fv(sg);
		glVertex3fv(ssg);
		glVertex3fv(si);
		glVertex3fv(ssi);
		glEnd();

		GLfloat sssa[3] = { pos[0], pos[1], pos[2] };
		GLfloat sssb[3] = { pos[0], pos[1], pos[2] + wymiary[2] };
		GLfloat sssc[3] = { pos[0], pos[1] + (wymiary[1] / 4), pos[2] };
		GLfloat sssd[3] = { pos[0], pos[1] + (wymiary[1] / 4), pos[2] + wymiary[2] };
		GLfloat ssse[3] = { pos[0], pos[1] + (wymiary[1] / 2), pos[2] };
		GLfloat sssf[3] = { pos[0], pos[1] + (wymiary[1] / 2), pos[2] + wymiary[2] };
		GLfloat sssg[3] = { pos[0], pos[1] + (wymiary[1] * 3 / 4), pos[2] };
		GLfloat sssh[3] = { pos[0], pos[1] + (wymiary[1] * 3 / 4), pos[2] + wymiary[2] };
		GLfloat sssi[3] = { pos[0], pos[1] + wymiary[1], pos[2] };
		GLfloat sssj[3] = { pos[0], pos[1] + wymiary[1], pos[2] + wymiary[2] };

		GLfloat ssssa[3] = { pos[0] + wymiary[0], pos[1], pos[2] };
		GLfloat ssssb[3] = { pos[0] + wymiary[0], pos[1], pos[2] + wymiary[2] };
		GLfloat ssssc[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] / 4), pos[2] };
		GLfloat ssssd[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] / 4), pos[2] + wymiary[2] };
		GLfloat sssse[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] / 2), pos[2] };
		GLfloat ssssf[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] / 2), pos[2] + wymiary[2] };
		GLfloat ssssg[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] * 3 / 4), pos[2] };
		GLfloat ssssh[3] = { pos[0] + wymiary[0], pos[1] + (wymiary[1] * 3 / 4), pos[2] + wymiary[2] };
		GLfloat ssssi[3] = { pos[0] + wymiary[0], pos[1] + wymiary[1], pos[2] };
		GLfloat ssssj[3] = { pos[0] + wymiary[0], pos[1] + wymiary[1], pos[2] + wymiary[2] };

		glColor3f(0.15, 0.15, 0.15);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(sssb);
		glVertex3fv(sssa);
		glVertex3fv(sssd);
		glVertex3fv(sssc);
		glVertex3fv(sssf);
		glVertex3fv(ssse);
		glVertex3fv(sssh);
		glVertex3fv(sssg);
		glVertex3fv(sssj);
		glVertex3fv(sssi);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3fv(ssssb);
		glVertex3fv(ssssa);
		glVertex3fv(ssssd);
		glVertex3fv(ssssc);
		glVertex3fv(ssssf);
		glVertex3fv(sssse);
		glVertex3fv(ssssh);
		glVertex3fv(ssssg);
		glVertex3fv(ssssj);
		glVertex3fv(ssssi);
		glEnd();
	}
}
