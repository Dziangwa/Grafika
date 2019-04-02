#include "Prostopadloscian.h"



Prostopadloscian::Prostopadloscian(double x, double y, double z, double dlugosc, double szerokosc, double wysokosc, double ang, int kolor)
{
	color = kolor;
	angle = ang;
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
		glColor3fv(Jabko[color]);

		GLfloat sa[3] = {pos[0], pos[1], pos[2]};
		double posTemp[3]= { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1], pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat sb[3] = { posTemp[0], posTemp[1], posTemp[2] };
		GLfloat sc[3] = {pos[0] + (wymiary[0]/4)*cos(angle), pos[1], pos[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat sd[3] = { posTemp[0] + (wymiary[0] / 4)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat se[3] = { pos[0] + (wymiary[0]/2)*cos(angle), pos[1], pos[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat sf[3] = { posTemp[0] + (wymiary[0] / 2)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat sg[3] = { pos[0] + (wymiary[0]*3/4)*cos(angle), pos[1], pos[2] + (wymiary[0]*3 / 4)*sin(angle) };
		GLfloat sh[3] = { posTemp[0] + (wymiary[0] * 3 / 4)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] * 3 / 4)*sin(angle) };
		GLfloat si[3] = { pos[0] + wymiary[0] * cos(angle), pos[1], pos[2] + (wymiary[0])*sin(angle) };
		GLfloat sj[3] = { posTemp[0] + wymiary[0] * cos(angle), posTemp[1], posTemp[2] + (wymiary[0])*sin(angle) };

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
		double possTemp[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1], pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat ssb[3] = { possTemp[0], possTemp[1] + wymiary[1], possTemp[2] };
		GLfloat ssc[3] = { pos[0] + (wymiary[0] / 4)*cos(angle), pos[1] + wymiary[1], pos[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat ssd[3] = { possTemp[0] + (wymiary[0] / 4)*cos(angle), possTemp[1] + wymiary[1], possTemp[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat sse[3] = { pos[0] + (wymiary[0] / 2)*cos(angle), pos[1] + wymiary[1], pos[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat ssf[3] = { possTemp[0] + (wymiary[0] / 2)*cos(angle), possTemp[1] + wymiary[1], possTemp[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat ssg[3] = { pos[0] + (wymiary[0] * 3 / 4)*cos(angle), pos[1] + wymiary[1], pos[2] + (wymiary[0] * 3 / 4)*sin(angle) };
		GLfloat ssh[3] = { possTemp[0] + (wymiary[0] * 3 / 4)*cos(angle), possTemp[1] + wymiary[1], possTemp[2] + (wymiary[0] * 3 / 4)*sin(angle) };
		GLfloat ssi[3] = { pos[0] + wymiary[0] * cos(angle), pos[1] + wymiary[1], pos[2] + (wymiary[0])*sin(angle) };
		GLfloat ssj[3] = { possTemp[0] + wymiary[0] * cos(angle), possTemp[1] + wymiary[1], possTemp[2] + (wymiary[0])*sin(angle) };


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

		//glColor3f(0.1, 0.1, 0.1);
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
		GLfloat sssb[3] = { pos[0] - wymiary[2]*cos(3.14 / 2 - angle), pos[1], pos[2] + wymiary[2]*sin(3.14/2 - angle) };
		GLfloat sssc[3] = { pos[0], pos[1] + (wymiary[1] / 4), pos[2] };
		GLfloat sssd[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1] + (wymiary[1] / 4), pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat ssse[3] = { pos[0], pos[1] + (wymiary[1] / 2), pos[2] };
		GLfloat sssf[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1] + (wymiary[1] / 2), pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat sssg[3] = { pos[0], pos[1] + (wymiary[1] * 3 / 4), pos[2] };
		GLfloat sssh[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1] + (wymiary[1] * 3 / 4), pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat sssi[3] = { pos[0], pos[1] + wymiary[1], pos[2] };
		GLfloat sssj[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1] + wymiary[1], pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };

		double posssTemp[3] = {pos[0] + wymiary[0]*cos(angle), pos[1], pos[2] + wymiary[0]*sin(angle)};
		GLfloat ssssa[3] = { posssTemp[0], posssTemp[1], posssTemp[2] };
		GLfloat ssssb[3] = { posssTemp[0] - wymiary[2] * cos(3.14 / 2 - angle), posssTemp[1], posssTemp[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat ssssc[3] = { posssTemp[0], posssTemp[1] + (wymiary[1] / 4), posssTemp[2] };
		GLfloat ssssd[3] = { posssTemp[0] - wymiary[2] * cos(3.14 / 2 - angle), posssTemp[1] + (wymiary[1] / 4), posssTemp[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat sssse[3] = { posssTemp[0], posssTemp[1] + (wymiary[1] / 2), posssTemp[2] };
		GLfloat ssssf[3] = { posssTemp[0] - wymiary[2] * cos(3.14 / 2 - angle), posssTemp[1] + (wymiary[1] / 2), posssTemp[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat ssssg[3] = { posssTemp[0], posssTemp[1] + (wymiary[1] * 3 / 4), posssTemp[2] };
		GLfloat ssssh[3] = { posssTemp[0] - wymiary[2] * cos(3.14 / 2 - angle), posssTemp[1] + (wymiary[1] * 3 / 4), posssTemp[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat ssssi[3] = { posssTemp[0], posssTemp[1] + wymiary[1], posssTemp[2] };
		GLfloat ssssj[3] = { posssTemp[0] - wymiary[2] * cos(3.14 / 2 - angle), posssTemp[1] + wymiary[1], posssTemp[2] + wymiary[2] * sin(3.14 / 2 - angle) };

		//glColor3f(0.15, 0.15, 0.15);
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
		
		//glColor3f(1, 1, 0);
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
