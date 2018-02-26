#ifndef _GEOMETRIA_PROYECTIVA_SHAPES_H_
#define _GEOMETRIA_PROYECTIVA_SHAPES_H_

#include "GLInclude.h"
#include "math3d.h"
#include <vector>

typedef struct {
	std::vector<VECTOR3D> P;
} LINE;

typedef struct {
	double x, y;
} P2D;

class Paralelogramo
{
public:
	VECTOR3D esq[8]; // square structure
	
	Paralelogramo(); // initialize constructor

	void draw(Paralelogramo *sqr); // draw the figure
	//P2D mouse(int x, int y); // get mouse coordintaes
	Paralelogramo* drag(Paralelogramo *sqr, int x, int y, VECTOR3D up, VECTOR3D side,  VECTOR3D forward, VECTOR3D target); // change points of the figure
};

void drawDot(VECTOR3D position, float sradius = 1, COLOUR color = grey);

//TODO
void drawLine(LINE line, COLOUR color = grey, bool doDrawDots = false);
void drawAxis();
void drawMesh();




#endif
