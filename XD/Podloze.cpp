#include "Podloze.h"



Podloze::Podloze(double x, double y, double z,
	double dlugosc, double szerokosc, double wysokosc, double ang, int kolor)
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


Podloze::~Podloze()
{
}

void Podloze::rysujPod()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		glColor3fv(Jabko[color]);

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
		GLfloat sa[3] = { pos[0], pos[1], pos[2] };
		double posTemp[3] = { pos[0] - wymiary[2] * cos(3.14 / 2 - angle), pos[1], pos[2] + wymiary[2] * sin(3.14 / 2 - angle) };
		GLfloat sb[3] = { posTemp[0], posTemp[1], posTemp[2] };
		GLfloat sc[3] = { pos[0] + (wymiary[0] / 4)*cos(angle), pos[1], pos[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat sd[3] = { posTemp[0] + (wymiary[0] / 4)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] / 4)*sin(angle) };
		GLfloat se[3] = { pos[0] + (wymiary[0] / 2)*cos(angle), pos[1], pos[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat sf[3] = { posTemp[0] + (wymiary[0] / 2)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] / 2)*sin(angle) };
		GLfloat sg[3] = { pos[0] + (wymiary[0] * 3 / 4)*cos(angle), pos[1], pos[2] + (wymiary[0] * 3 / 4)*sin(angle) };
		GLfloat sh[3] = { posTemp[0] + (wymiary[0] * 3 / 4)*cos(angle), posTemp[1], posTemp[2] + (wymiary[0] * 3 / 4)*sin(angle) };
		GLfloat si[3] = { pos[0] + wymiary[0] * cos(angle), pos[1], pos[2] + (wymiary[0])*sin(angle) };
		GLfloat sj[3] = { posTemp[0] + wymiary[0] * cos(angle), posTemp[1], posTemp[2] + (wymiary[0])*sin(angle) };
		
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
	}

}
