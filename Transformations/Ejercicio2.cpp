//#include "Ejercicio2.h"
//
//
//void drawLine(LINE line, COLOUR color, bool doDrawDots) {
//
//	glColor3f(color.r, color.g, color.b);
//
//	if (!doDrawDots)
//	{
//		glBegin(GL_LINE_STRIP);
//
//		for (int i = 0; i < line.P.size(); i++)
//		{
//			glVertex3f(line.P[i].x, line.P[i].y, line.P[i].z);
//		}
//
//		glEnd();
//	}
//
//	else
//	{
//
//			drawDot(line.P[0]);
//
//			drawDot(line.P[line.P.size()-1]);
//
//	}
//
//	// usa GL_LINE_STRIP en modo inmediato (glBegin/glEnd)
//	// enviar puntos a OpenGL usando glVertex3f
//}
//
//
//void drawAxis()
//{
//
//	LINE axisX;
//	LINE axisY;
//	LINE axisZ;
//
//	axisX.P = { {0,0,0} , {100,0,0} };
//	axisY.P = { { 0,0,0 } ,{ 0,100,0 } };
//	axisZ.P = { { 0,0,0 } ,{ 0,0,100 } };
//
//
//	drawLine(axisX, red);
//	drawLine(axisY, green);
//	drawLine(axisZ, blue);
//}
