#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

#include <string>
#include "Dependencies\freeglut\freeglut.h"

#include <cstdio>
#include "box.h"
#include "frog.h"
#include "track.h"

#define _USE_MATH_DEFINES
#define SPEED1 1 
#define SPEED2 1.5
#define PI 3.14159265

/* Global variables */
char title[] = "Frog";
float degree = 0.0f;
float verticalDegree = 36.0f;
Box boxObject;
track trackObject;

char keyboardbuffer[64];
float flyXcoord = -10.0f;
float flyYcoord = 0.0f;
float flyZcoord = 20.0f;

double dist1=100, dist2=100;



float eyex = 0.0f, eyey = 0.0f;
float eyez = 80.0f;
frog frogObject1 = frog(SPEED1);
frog frogObject2 = frog(SPEED2);
int mode = -1;
int flag1=0;
int flag2 = 0;
int g_counter = 0;
int alpha = 0;

void myTimer(int value);
void initGL();
void display();
void reshape(GLsizei width, GLsizei height);
void mouse(int button, int state, int x, int y);
void inputKey(int key, int x, int y);
void myTimer(int value);
void Sprint(int x, int y, char *st);
void updatePositions();

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);        
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_SMOOTH);  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
	frogObject1.createAllLists();
	frogObject2.createAllLists();
	boxObject.createQuadList();
	trackObject.createQuadList();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	/*GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, -100.0, 0.0, 1.0 };

	glmaterialfv(gl_front, gl_specular, mat_specular);
	glmaterialfv(gl_front, gl_shininess, mat_shininess);
	gllightfv(gl_light0, gl_position, light_position);

	glenable(gl_lighting);
	glenable(gl_light0);*/
	glMatrixMode(GL_MODELVIEW);    

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	glRotatef(verticalDegree, 1.0f, 0.0f, 0.0f);	

	glColor3f(1.0f, 1.0f, 1.0f);

	frogObject1.drawFrog();

	glTranslatef(80.0f, 0.0f, 0.0f);
	frogObject2.drawFrog();
	glTranslatef(-80.0f, 0.0f, 0.0f);
	/*boxObject.drawBox();
	glTranslatef(-5.0f, 0.0f, 15.0f);*/
	trackObject.drawTrack();
	
	//glTranslatef(5.0f, 0.0f, 10.0f);
	glTranslatef(flyXcoord, flyYcoord, flyZcoord);
	boxObject.drawBox();
	glTranslatef(-flyXcoord, -flyYcoord, -flyZcoord);
	//glTranslatef(-5.0f, 0.0f, -10.0f);

	glDisable(GL_TEXTURE_2D);

	Sprint(0, 25, keyboardbuffer);
	glutSwapBuffers();  
}


void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, aspect, 0.1f, 100.0f);
}

void mouse(int button, int state, int x, int y) {
	//cout << x << " " << y << endl;
	/*flyXcoord = x;
	flyYcoord = y;*/
	glutPostRedisplay();
}




void inputKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT: {degree -= 5.0f; glutPostRedisplay(); break; }
	case GLUT_KEY_LEFT: {degree += 5.0f; glutPostRedisplay(); break; }
	case GLUT_KEY_UP: {eyez -= 1.0f; glutPostRedisplay(); break;}
	case GLUT_KEY_DOWN:{ eyez += 1.0f; glutPostRedisplay(); break; }
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
	{
		exit(0);
		break;
	}
	case '+':
	{
		frogObject1.speed += 0.2;
		frogObject2.speed += 0.2;
		break;
	}
	case '-':
	{
		frogObject1.speed -= 0.2;
		frogObject2.speed += 0.2;
		break;
	}
	case 'r': {
		frogObject1.reset();
		degree = 0.0f;
		verticalDegree = 36.0f;
		eyex = 0;
		eyey = 0;
		eyez = 80.0f;
	}
	
	case 's':
	{
		verticalDegree -= 3.0f;
		glutPostRedisplay();
		break;
	}
	case 'w':
	{
		verticalDegree += 3.0f;
		glutPostRedisplay();
		break;
	}
	
	case 'i': {
		flyZcoord -= 0.3f;
		updatePositions();
		glutPostRedisplay();
		break;
	}	
	case 'j': {
		flyXcoord -= 0.3f;
		updatePositions();
		glutPostRedisplay();
		break;
	}
	case 'k': {
		flyZcoord += 0.3f;
		updatePositions();
		glutPostRedisplay();
		break;
	}
	case 'l': {
		flyXcoord += 0.3f;
		updatePositions();
		glutPostRedisplay();
		break;
	}
				 
	default: {	}
	}
}

void updatePositions() {
	dist1 = sqrt(pow(frogObject1.hipTranslatex - flyXcoord, 2) + pow(frogObject1.hipTranslatez - flyZcoord, 2));
	double cosTheta1 = -(frogObject1.hipTranslatex  - flyXcoord) / dist1;
	double sinTheta1 = -(frogObject1.hipTranslatez - flyZcoord) / dist1;
	double tanTheta1 = sinTheta1 / cosTheta1;
	//cout << sinTheta1 << " " << cosTheta1 << endl;
	//cout << 270 + (atan(tanTheta1) * 180 / PI) << endl;
	/*if (tanTheta1 < 0.01) {
		frogObject1.hipz = 270 + (atan(tanTheta1) * 180 / PI);
	}*/

	if (frogObject1.hipTranslatey > 10.0f) {
		flag1 = 0;
	}
	if (frogObject1.hipTranslatey < 0.0f) {
		flag1 = 1;
	}
	if (flag1 == 1) {

		frogObject1.hipTranslatey += frogObject1.speed *0.2f;		//
		frogObject1.hipTranslatex += frogObject1.speed *0.2f*cosTheta1;		//
		frogObject1.hipTranslatez += frogObject1.speed *0.2f*sinTheta1;		//
		frogObject1.leftUpperArmx -= frogObject1.speed *1.4f;		//
		frogObject1.rightUpperArmx -= frogObject1.speed *1.2f;
		frogObject1.leftLowerArmx += frogObject1.speed *1.2f;
		frogObject1.rightLowerArmx += frogObject1.speed *1.4f;
		frogObject1.headz += frogObject1.speed *0.8f;
		frogObject1.torsox -= frogObject1.speed *0.4f;			//
		frogObject1.rightUpperLegx += frogObject1.speed *0.6f;
		frogObject1.leftUpperLegx += frogObject1.speed *0.4f;
		frogObject1.rightLowerLegx += frogObject1.speed *0.2f;
		frogObject1.leftLowerLegx += frogObject1.speed *0.2f;
	}
	if (flag1 == 0) {
		frogObject1.hipTranslatey -= frogObject1.speed *0.2f;		//
		frogObject1.hipTranslatex += frogObject1.speed *0.2f*cosTheta1;		//
		frogObject1.hipTranslatez += frogObject1.speed *0.2f*sinTheta1;		//
		frogObject1.leftUpperArmx += frogObject1.speed *1.4f;		//
		frogObject1.rightUpperArmx += frogObject1.speed *1.2f;
		frogObject1.leftLowerArmx -= frogObject1.speed *1.2f;
		frogObject1.rightLowerArmx -= frogObject1.speed *1.4f;
		frogObject1.headz -= frogObject1.speed *0.8f;
		frogObject1.torsox += frogObject1.speed *0.4f;
		frogObject1.rightUpperLegx -= frogObject1.speed *0.6f;
		frogObject1.leftUpperLegx -= frogObject1.speed *0.4f;
		frogObject1.rightLowerLegx -= frogObject1.speed *0.2f;
		frogObject1.leftLowerLegx -= frogObject1.speed *0.2f;
	}


	dist2 = sqrt(pow(frogObject2.hipTranslatex+80 - flyXcoord, 2) + pow(frogObject2.hipTranslatez - flyZcoord, 2));
	double cosTheta2 = -(frogObject2.hipTranslatex+80 - flyXcoord) / dist1;
	double sinTheta2 = -(frogObject2.hipTranslatez - flyZcoord) / dist1;
	double tanTheta2 = sinTheta2 / cosTheta2;
	
	frogObject2.hipz = 90 + (atan(tanTheta2) * 180 / PI);

	if (frogObject2.hipTranslatey > 10.0f) {
		flag2 = 0;
	}
	if (frogObject2.hipTranslatey < 0.0f) {
		flag2 = 1;
	}
	if (flag2 == 1) {

		frogObject2.hipTranslatey += frogObject2.speed *0.2f;		//
		frogObject2.hipTranslatex += frogObject2.speed *0.2f*cosTheta2;		//
		frogObject2.hipTranslatez += frogObject2.speed *0.2f*sinTheta2;		//
		frogObject2.leftUpperArmx -= frogObject2.speed *1.4f;		//
		frogObject2.rightUpperArmx -= frogObject2.speed *1.2f;
		frogObject2.leftLowerArmx += frogObject2.speed *1.2f;
		frogObject2.rightLowerArmx += frogObject2.speed *1.4f;
		frogObject2.headz += frogObject2.speed *0.8f;
		frogObject2.torsox -= frogObject2.speed *0.4f;			//
		frogObject2.rightUpperLegx += frogObject2.speed *0.6f;
		frogObject2.leftUpperLegx += frogObject2.speed *0.4f;
		frogObject2.rightLowerLegx += frogObject2.speed *0.2f;
		frogObject2.leftLowerLegx += frogObject2.speed *0.2f;
	}
	if (flag2 == 0) {
		frogObject2.hipTranslatey -= frogObject2.speed *0.2f;		//
		frogObject2.hipTranslatex += frogObject2.speed *0.2f*cosTheta2;		//
		frogObject2.hipTranslatez += frogObject2.speed *0.2f*sinTheta2;		//
		frogObject2.leftUpperArmx += frogObject2.speed *1.4f;		//
		frogObject2.rightUpperArmx += frogObject2.speed *1.2f;
		frogObject2.leftLowerArmx -= frogObject2.speed *1.2f;
		frogObject2.rightLowerArmx -= frogObject2.speed *1.4f;
		frogObject2.headz -= frogObject2.speed *0.8f;
		frogObject2.torsox += frogObject2.speed *0.4f;
		frogObject2.rightUpperLegx -= frogObject2.speed *0.6f;
		frogObject2.leftUpperLegx -= frogObject2.speed *0.4f;
		frogObject2.rightLowerLegx -= frogObject2.speed *0.2f;
		frogObject2.leftLowerLegx -= frogObject2.speed *0.2f;
	}
}

void myTimer(int value) {


	if (alpha == 0)
	{
		g_counter = value + 1;
	}
	else if (alpha == 1)
	{
		g_counter = value + 0;
	}
	else if (alpha == -1)
	{
		strncpy(keyboardbuffer, "Congratulations!, You Win.", sizeof(keyboardbuffer));
		keyboardbuffer[sizeof(keyboardbuffer) - 1] = '\0';
	}
	else if (alpha == -5)
	{
		strncpy(keyboardbuffer, "Oops! You are caught.", sizeof(keyboardbuffer));
		keyboardbuffer[sizeof(keyboardbuffer) - 1] = '\0';
	}
	glutTimerFunc(1000, myTimer, g_counter);
	if (dist1 < 10 || dist2 < 10) {
		alpha = -5;
		strncpy(keyboardbuffer, "Oops! You are caught.", sizeof(keyboardbuffer));
		keyboardbuffer[sizeof(keyboardbuffer) - 1] = '\0';
		glutPostRedisplay();
		return;
	}
	if (g_counter == 20) {
		alpha = -1;
		strncpy(keyboardbuffer, "Congratulations!, You Win.", sizeof(keyboardbuffer));
		keyboardbuffer[sizeof(keyboardbuffer) - 1] = '\0';
		glutPostRedisplay();
		return;
	}

	string tmp = to_string(g_counter);
	strncpy(keyboardbuffer, tmp.c_str(), sizeof(keyboardbuffer));
	keyboardbuffer[sizeof(keyboardbuffer) - 1] = '\0';
	
	glutPostRedisplay();
	
}

void Sprint(int x, int y, char *st)
{
	int l, i;

	l = strlen(st);
	glRasterPos2i(x, y);
	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); 
	}

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);           
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
	glutInitWindowSize(640, 480);   
	glutInitWindowPosition(50, 50); 
	glutCreateWindow(title);          
	glutDisplayFunc(display);       
	glutReshapeFunc(reshape);       
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(inputKey);	
	glutTimerFunc(10, myTimer, g_counter);
	glutMouseFunc(mouse);	//	
	initGL();                       
	glutMainLoop();                 
	return 0;
}
