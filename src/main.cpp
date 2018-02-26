#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GLInclude.h"
#include "camera.h"
#include "shapes.h"


void Display(void);
void Init(void);
void Render(void);
void Lighting(void);
void InitCamera(int);
void HandleKeyboard(unsigned char key,int x, int y);
void HandleReshape(int,int);
void HandleIdle(void);
void dragObject(int x, int y);
void HandleMousePassiveMotion(int x, int y);


int fullscreen = FALSE;

int currentbutton = -1;
double rotatespeed = 3;
double tSpeed = 0.05;
float t = 0;

CAMERA camera;
FRUSTUM centerFrustum;


double rotateangle = 0;

int pre_x = 300;
int pre_y = 200;

int pre_x2 = 300;
int pre_y2 = 200;
EULER e_camera;
double sensibility = 0.5;
VECTOR3D e_forward = { 0,0,-20 };
VECTOR3D e_side;
VECTOR3D e_up;

bool staticCam = false;

Paralelogramo* cubo = new Paralelogramo;


int main(int argc,char **argv)
{
    camera.screenwidth = 600;
    camera.screenheight = 400;

	printf("\n\nHow to use this demo:\n\n");
	printf("\t Turn camera with mouse without pressing buttons\n");
	printf("\t Move the camera with WASD\n");
	printf("\t Add or remove camera sensibility with E and Q\n");
	printf("\t Turn on and off the camera turning with F\n");
	printf("\t You can click and push de green cube when the camera turning is off \n");
	printf("\t Quit by pressing ESC key\n");
	

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Geometria Proyectiva");
    if (fullscreen)
        glutFullScreen();
    glutDisplayFunc( Display);
    glutReshapeFunc(HandleReshape);
    glutReshapeWindow(camera.screenwidth,camera.screenheight);
    glutIdleFunc(HandleIdle);
    glutKeyboardFunc(HandleKeyboard);
    Init();
    InitCamera(0);
    Lighting();
    
    glutMainLoop();
    return(0);
}

void Init(void)
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    
    glLineWidth(1.0);
    glPointSize(1.0);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glFrontFace(GL_CW);
    glClearColor(0.0,0.0,0.0,0.0);         /* Background colour */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void Display(void)
{
    glDrawBuffer(GL_BACK_LEFT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glDrawBuffer(GL_BACK);
    
	double nearValue = 0.1;
	double farValue = 10000;
    
    double aspectRatio  = camera.screenwidth / (double)camera.screenheight;
    FRUSTUM centerFrustum = makeFrustum(camera.aperture, aspectRatio, nearValue, farValue);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//gluPerspective(camera.aperture, aspectRatio, nearValue, farValue);//QUITAR
	glFrustum(centerFrustum.left, centerFrustum.right, centerFrustum.bottom, centerFrustum.top, centerFrustum.nearValue, centerFrustum.farValue);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    VECTOR3D target = Add(camera.position, camera.direction);
    //gluLookAt(camera.position.x,camera.position.y,camera.position.z, target.x , target.y, target.z, camera.up.x,camera.up.y,camera.up.z); //QUITAR

	glutMotionFunc(dragObject);
	glutPassiveMotionFunc(HandleMousePassiveMotion);



	MATRIX4 lookAtMatrix = lookAt(Add(camera.position, { 5,1,5}), e_forward, camera.up, e_up, e_side);
    glLoadMatrixf(lookAtMatrix.m);

    glViewport(0,0,camera.screenwidth,camera.screenheight);
    
    Render();
    
    glutSwapBuffers();
}


void Render(void)
{
    GLfloat specular[4] = {1.0,1.0,1.0,1.0};
    GLfloat shiny[1] = {5.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    
    glPushMatrix();
    glRotatef(rotateangle,0.0,1.0,0.0);

    drawMesh();
	cubo->draw(cubo);

	//drawDot({ 1,1,0 });

    glPopMatrix();
}

void Lighting(void)
{
    GLfloat fullambient[4] = {1.0,1.0,1.0,1.0};
    GLfloat position[4] = {0.0,0.0,0.0,0.0};
    GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
    GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
    GLfloat specular[4] = {0.0,0.0,0.0,1.0};
    
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,fullambient);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glEnable(GL_LIGHT0);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void HandleKeyboard(unsigned char key,int x, int y)
{
    switch (key) {
        case ESC:
        //case 'Q':
        //case 'q':
            exit(0);
            break;
        case 'R':
        case 'r':
            rotateangle += rotatespeed;
            break;
            
        case '+':
            t += tSpeed;
            t = t > 1 ? 1:t;
            break;

        case '-':
            t -= tSpeed;
            t = t <0 ? 0:t;
            break;

        case 'h':
        case 'H':
            InitCamera(0);
            break;


		case 'f':
		case 'F':
			staticCam=!staticCam;
			break;



		case 'w':
		case 'W':
			camera.position=Add(camera.position, Normalize(e_forward));
			break;

		case 's':
		case 'S':
			camera.position = Add(camera.position, Normalize(MultiplyWithScalar(-1,e_forward)));
			break;

		case 'a':
		case 'A':
			camera.position = Add(camera.position, Normalize(MultiplyWithScalar(-1, CrossProduct(e_forward, camera.up))));
			break;

		case 'd':
		case 'D':
			camera.position = Add(camera.position, Normalize(CrossProduct(e_forward, camera.up)));
			break;


		case 'q':
		case 'Q':
		{
			if (sensibility == 0)
				printf("Sensibility cannot drop below 0 \n \n");
			else
			{
				sensibility -= 0.1;
				printf("Sensibility changed to: %f \n \n", sensibility);
			}
		}
			break;

		case 'e':
		case 'E':
		{
			sensibility += 0.1;
			printf("Sensibility changed to: %f \n \n", sensibility); 
		}
			break;
    }
}

void HandleIdle(void)
{
//    rotateangle += rotatespeed;
    glutPostRedisplay();
}

void HandleReshape(int w,int h)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    camera.screenwidth = w;
    camera.screenheight = h;
}


void InitCamera(int mode)
{
    camera.aperture = 45;

    camera.position.x = 0;
    camera.position.y = 0;
    camera.position.z = 20;
    
    camera.direction.x = -camera.position.x;
    camera.direction.y = -camera.position.y;
    camera.direction.z = -camera.position.z;
    
    camera.up.x = 0;
    camera.up.y = 1;
    camera.up.z = 0;
}

void dragObject(int x, int y)
{

	int difx, dify;

	difx = (x - pre_x);
	dify = (y - pre_y);

	pre_x = x;
	pre_y = y;

	if (staticCam)
	{
		unsigned char data[4];

		glReadPixels(x, camera.screenheight - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);

		//printf("%i \n", data[1]);

		if ((int)data[1] == 255)
		{
			cubo->drag(cubo, difx , -dify , e_up, e_side, Normalize(e_forward), Substract(camera.position,cubo->esq[1]));
			glutPostRedisplay();
		}
	}

}

void HandleMousePassiveMotion(int x, int y)
{
	int difx, dify;

	difx = x - pre_x;
	dify = y - pre_y;

	pre_x = x;
	pre_y = y;

	//printf("pre_x: %d  ", pre_x);
	//printf("pre_y: %d  \n", pre_y);

	if (sensibility < 0)
		sensibility = 0;

	if (!staticCam)
	{
		e_camera.pitch += -DTOR * dify * sensibility;
		e_camera.yaw += -DTOR * difx  * sensibility;

		updateEulerOrientation(e_camera);
		e_forward = getForward(e_camera);
	}


	//printf("x: %d  ", e_forward.x);
	//printf("y: %d  ", e_forward.y);
	//printf("z: %d  \n", e_forward.z);



}