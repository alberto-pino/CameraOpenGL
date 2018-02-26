
#include "GLInclude.h"
#include "shapes.h"

void drawDot(VECTOR3D position, float sradius, COLOUR color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);


	VECTOR3D p[4], n[4];
	int STEP = 30;
	for (int i = 0; i<360; i += STEP) {
		for (int j = -90; j<90; j += STEP) {

			p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
			p[0].y = sradius * sin(j*DTOR);
			p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
			n[0] = p[0];

			p[1].x = sradius * cos((j + STEP)*DTOR) * cos(i*DTOR);
			p[1].y = sradius * sin((j + STEP)*DTOR);
			p[1].z = sradius * cos((j + STEP)*DTOR) * sin(i*DTOR);
			n[1] = p[1];

			p[2].x = sradius * cos((j + STEP)*DTOR) * cos((i + STEP)*DTOR);
			p[2].y = sradius * sin((j + STEP)*DTOR);
			p[2].z = sradius * cos((j + STEP)*DTOR) * sin((i + STEP)*DTOR);
			n[2] = p[2];

			p[3].x = sradius * cos(j*DTOR) * cos((i + STEP)*DTOR);
			p[3].y = sradius * sin(j*DTOR);
			p[3].z = sradius * cos(j*DTOR) * sin((i + STEP)*DTOR);
			n[3] = p[3];

			glBegin(GL_POLYGON);
			if (i % (STEP * 4) == 0)
				glColor3f(color.r, color.g, color.b);
			else
				glColor3f(color.r*0.5, color.g*0.5, color.b*0.5);
			for (int k = 0; k<4; k++) {
				glNormal3f(n[k].x, n[k].y, n[k].z);
				glVertex3f(p[k].x, p[k].y, p[k].z);
			}
			glEnd();
		}
	}

	glPopMatrix();
}



void drawLine(LINE line, COLOUR color, bool doDrawDots) {

	glColor3f(color.r, color.g, color.b);

	if (!doDrawDots)
	{
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < line.P.size(); i++)
		{
			glVertex3f(line.P[i].x, line.P[i].y, line.P[i].z);
		}

		glEnd();
	}

	else
	{

		drawDot(line.P[0]);

		drawDot(line.P[line.P.size() - 1]);

	}

	// usa GL_LINE_STRIP en modo inmediato (glBegin/glEnd)
	// enviar puntos a OpenGL usando glVertex3f
}


void drawAxis()
{

	LINE axisX;
	LINE axisY;
	LINE axisZ;

	axisX.P = { { 0,0,0 } ,{ 100,0,0 } };
	axisY.P = { { 0,0,0 } ,{ 0,100,0 } };
	axisZ.P = { { 0,0,0 } ,{ 0,0,100 } };


	drawLine(axisX, red);
	drawLine(axisY, green);
	drawLine(axisZ, blue);
}


void drawMesh()
{
	LINE new_line1_pos;
	LINE new_line1_neg;
	LINE new_line2_pos;
	LINE new_line2_neg;

	new_line1_pos.P = { { 0,0,-500 } ,{ 0,0,500 } };
	new_line2_pos.P = { { -500,0,0 } ,{ 500,0,0 } };


	drawLine(new_line1_pos, blue);


	for (int i = 0; i < 100; i++)
	{

		new_line1_pos.P = { { (double)i*5,0,-500 } ,{ (double)i*5,0,500 } };
		new_line1_neg.P = { { (double)-i*5,0,-500 } ,{ (double)-i*5,0,500 } };
		new_line2_pos.P = { { -500,0,(double)i*5 } ,{ 500,0,(double)i*5 } };
		new_line2_neg.P = { { -500,0,(double)-i*5 } ,{ 500,0,(double)-i*5 } };


		drawLine(new_line1_pos, blue);
		drawLine(new_line1_neg, blue);
		drawLine(new_line2_pos, blue);
		drawLine(new_line2_neg, blue);

	}

}



Paralelogramo::Paralelogramo()
{
	esq[0] = { 0,0,0 };
	esq[1] = { 1,0,0 };
	esq[2] = { 1,0,1 };
	esq[3] = { 0,0,1 };

	esq[4] = { 0,1,1 };
	esq[5] = { 0,1,0 };
	esq[6] = { 1,1,0 };
	esq[7] = { 1,1,1 };

}

void Paralelogramo::draw(Paralelogramo *pl)
{
	// draw figure fill
	int i;
	glColor3f(green.r,green.g,green.b);
	glBegin(GL_QUADS);

	glVertex3f(pl->esq[0].x, pl->esq[0].y, pl->esq[0].z);
	glVertex3f(pl->esq[1].x, pl->esq[1].y, pl->esq[1].z);
	glVertex3f(pl->esq[2].x, pl->esq[2].y, pl->esq[2].z);
	glVertex3f(pl->esq[3].x, pl->esq[3].y, pl->esq[3].z);

	glVertex3f(pl->esq[0].x, pl->esq[0].y, pl->esq[0].z);
	glVertex3f(pl->esq[1].x, pl->esq[1].y, pl->esq[1].z);
	glVertex3f(pl->esq[6].x, pl->esq[6].y, pl->esq[6].z);
	glVertex3f(pl->esq[5].x, pl->esq[5].y, pl->esq[5].z);
	
	glVertex3f(pl->esq[1].x, pl->esq[1].y, pl->esq[1].z);
	glVertex3f(pl->esq[2].x, pl->esq[2].y, pl->esq[2].z);
	glVertex3f(pl->esq[7].x, pl->esq[7].y, pl->esq[7].z);
	glVertex3f(pl->esq[6].x, pl->esq[6].y, pl->esq[6].z);

	glVertex3f(pl->esq[2].x, pl->esq[2].y, pl->esq[2].z);
	glVertex3f(pl->esq[3].x, pl->esq[3].y, pl->esq[3].z);
	glVertex3f(pl->esq[4].x, pl->esq[4].y, pl->esq[4].z);
	glVertex3f(pl->esq[7].x, pl->esq[7].y, pl->esq[7].z);

	glVertex3f(pl->esq[0].x, pl->esq[0].y, pl->esq[0].z);
	glVertex3f(pl->esq[3].x, pl->esq[3].y, pl->esq[3].z);
	glVertex3f(pl->esq[4].x, pl->esq[4].y, pl->esq[4].z);
	glVertex3f(pl->esq[5].x, pl->esq[5].y, pl->esq[5].z);

	glVertex3f(pl->esq[5].x, pl->esq[5].y, pl->esq[5].z);
	glVertex3f(pl->esq[6].x, pl->esq[6].y, pl->esq[6].z);
	glVertex3f(pl->esq[7].x, pl->esq[7].y, pl->esq[7].z);
	glVertex3f(pl->esq[4].x, pl->esq[4].y, pl->esq[4].z);

	glEnd();

}

//P2D Paralelogramo::mouse(int x, int y)
//{
//
//}

Paralelogramo* Paralelogramo::drag(Paralelogramo *pl, int movex, int movey, VECTOR3D up, VECTOR3D side, VECTOR3D forward, VECTOR3D target)
{

	VECTOR3D fw = Normalize(forward);

	double det = (side.x*up.y*fw.z) + (up.x*fw.y*side.z) + (fw.x*up.z*side.y)
		- ((fw.x*up.y*side.z) + (fw.y*up.z*side.x) + (fw.z*up.x*side.y));

	VECTOR3D e1,e2;

	e1.x = (up.y*fw.z - up.z*fw.y) / det;
	e1.y = -1*(side.y*fw.z - side.z*fw.y) / det;
	e1.z = (side.y*up.z - side.z*up.y) / det;

	e2.x = -1*(up.x*fw.z - up.z*fw.x) / det;
	e2.y = (side.x*fw.z - side.z*fw.x) / det;
	e2.z = -1*(side.x*up.z - side.z*up.x) / det;



	for (int i = 0; i < 8; i++)
	{
		pl->esq[i].x += (movex *e1.x + movey *e2.x)*0.002*Magnitude(target);
		pl->esq[i].y += (movex *e1.y + movey *e2.y)*0.002*Magnitude(target);
		pl->esq[i].z += (movex *e1.z + movey *e2.z)*0.002*Magnitude(target);
	}

	//pl->esq[0] = { 0,0,0 };
	//pl->esq[1] = { -1,0,0 };
	//pl->esq[2] = { -1,0,-1 };
	//pl->esq[3] = { 0,0,-1 };

	//pl->esq[4] = { 0,-1,-1 };
	//pl->esq[5] = { 0,-1,0 };
	//pl->esq[6] = { -1,-1,0 };
	//pl->esq[7] = { -1,-1,-1 };
	//
	return pl;
}