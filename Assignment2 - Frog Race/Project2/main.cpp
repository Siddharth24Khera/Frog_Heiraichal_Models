
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

#define SPEED1 1 
#define SPEED2 2 
#define _USE_MATH_DEFINES

/* Global variables */
char title[] = "Frog";
float degree = 0.0f;
float verticalDegree = 10.0f;
Box boxObject;
track trackObject;



float eyex = 0.0f, eyey = 0.0f;
float eyez = 80.0f;
frog frogObject1 = frog(SPEED1);
frog frogObject2 = frog(SPEED2);
int mode = -1;

int flag1 = 1;
int flag2 = 1;
/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
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
	glMatrixMode(GL_MODELVIEW);    

	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	glRotatef(verticalDegree, 1.0f, 0.0f, 0.0f);	

	glColor3f(1.0f, 1.0f, 1.0f);	
	frogObject1.drawFrog();
	glTranslatef(0.0f, 0.0f, 20.0f);
	frogObject2.drawFrog();
	/*glTranslatef(5.0f, 0.0f, -15.0f);
	boxObject.drawBox();
	glTranslatef(-5.0f, 0.0f, 15.0f);*/
	trackObject.drawTrack();
	
	glDisable(GL_TEXTURE_2D);
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
	glutPostRedisplay();
}


/*
Jump up with 'n'
Jump down with 'm'


Body movement scheme is designed in the following way
There are modes which decide the bosy parts controlled by z,x and c.
0: Translate
1: Head
2: Hip
3: Torso
4: Left-Upper-Arm
5: Left-Lower-Arm
6: Right-Upper-Arm
7: Right-Lower-Arm

'p': Left-Upper-Leg
'o': Left-Lower-Leg
'i': Right-Upper-Leg
'u': Right-Lower-Leg

Shift + key is for reverse direction movenment

Other than that the box lid angle is controlled by '=' and '-'

All joints and box-lid have certain boundaries till which they can rotate in various directions

ALso, r is for reset

Also w, s, left ,right control the camera
up and down are for zoom.
*/

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
	case 'r': {
		frogObject1.reset();
		glutPostRedisplay();
	}
	case '0': {
		mode = 0;
		glutPostRedisplay();
		break;
	}
	case '1': {
		mode = 1;
		glutPostRedisplay();
		break;
	}
	case '2': {
		mode = 2;
		glutPostRedisplay();
		break;
	}
	case '3': {
		mode = 3;
		glutPostRedisplay();
		break;
	}
	case '4': {
		mode = 4;
		glutPostRedisplay();
		break;
	}
	case '5': {
		mode = 5;
		glutPostRedisplay();
		break;
	}
	case '6': {
		mode = 6;
		glutPostRedisplay();
		break;
	}
	case '7': {
		mode = 7;
		glutPostRedisplay();
		break;
	}
	
	case 'p': {
		mode = 9;
		glutPostRedisplay();
		break;
	}
	case 'o': {
		mode = 10;
		glutPostRedisplay();
		break;
	}
	case 'i': {
		mode = 11;
		glutPostRedisplay();
		break;
	}
	case 'u': {
		mode = 12;
		glutPostRedisplay();
		break;
	}
	case '=':
	{
		if (boxObject.lidAngle < 265.0f) {
			boxObject.lidAngle += 2.0f;
			glutPostRedisplay();
		}		
		break;
	}
	case '-':
	{
		if (boxObject.lidAngle > 5.0f) {
			boxObject.lidAngle -= 2.0f;
			glutPostRedisplay();
		}
		break;
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
	case 'z': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatez += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.headz <= 45.0f)
					frogObject1.headz += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipz < 45.0f)
				frogObject1.hipz += 2.0f;
			}
			else if (mode == 3) {
				// Torso Rotation
				if (frogObject1.torsoz <= 25.0f)
					frogObject1.torsoz += 2.0f;
			}
			else if (mode == 4) {
				if ((((int)frogObject1.leftUpperArmx) % 360 <= 20.0f || ((int)frogObject1.leftUpperArmx) % 360 >= 340.0f) && frogObject1.leftUpperArmy >= 30.0f) {
					/*cout<<"problem case"<<endl;
					cout<<"angle"<<":"<<4.0/7.0*frogObject1.leftLowerArmx<<endl;*/
					if (frogObject1.leftUpperArmz < 0.0f && frogObject1.leftUpperArmz < 4.0 / 7.0*frogObject1.leftLowerArmx) {
						frogObject1.leftUpperArmz += 2.0f;
					}
				}
				else {
					if (frogObject1.leftUpperArmz < 0.0f)
						frogObject1.leftUpperArmz += 2.0f;
				}
			}
			else if (mode == 6) {
				if (frogObject1.rightUpperArmz<180.0f)
					frogObject1.rightUpperArmz += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegz < 0.0f)
					frogObject1.leftUpperLegz += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegz < 45.0f)
					frogObject1.rightUpperLegz += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'Z': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatez -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.headz >= -45.0f)
					frogObject1.headz -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipz > -45.0f)
				frogObject1.hipz -= 2.0f;
			}
			else if (mode == 3) {
				// Neck Rotation
				if (frogObject1.torsoz >= -25.0f)
					frogObject1.torsoz -= 2.0f;
			}
			else if (mode == 4) {
				// cout<<"AAYA"<<endl;
				if (frogObject1.leftUpperArmz >= -180.0f)
					frogObject1.leftUpperArmz -= 2.0f;
			}
			else if (mode == 6) {
				// cout<<fabs(4.0/7.0*frogObject1.rightLowerArmx)<<endl;
				if ((((int)frogObject1.rightLowerArmx) % 360 < 20.0f || ((int)frogObject1.rightLowerArmx) % 360 > 340.0f) && frogObject1.rightUpperArmy < -30.0f) {
					if (frogObject1.rightUpperArmz > 0.0f && frogObject1.rightUpperArmz > fabs(4.0 / 7.0*frogObject1.rightLowerArmx)) {
						frogObject1.rightUpperArmz -= 2.0f;
					}
				}
				else {
					if (frogObject1.rightUpperArmz > 0.0f) {
						frogObject1.rightUpperArmz -= 2.0f;
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegz > -45.0f)
					frogObject1.leftUpperLegz -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegz > 0.0f)
					frogObject1.rightUpperLegz -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'x': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatex += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.headx <= 45.0f)
					frogObject1.headx += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipx < 45.0f)
				frogObject1.hipx += 2.0f;
			}
			
			else if (mode == 3) {
				// Neck Rotation
				if (frogObject1.torsox <= 25.0f)
					frogObject1.torsox += 2.0f;
			}
			else if (mode == 4) {
				// Upper Arm Rotation
				frogObject1.leftUpperArmx += 2.0f;
			}
			else if (mode == 5) {
				if (frogObject1.leftLowerArmx <= 0.0f)
					frogObject1.leftLowerArmx += 2.0f;
			}
			else if (mode == 6) {
				// Upper Arm Rotation
				frogObject1.rightUpperArmx += 2.0f;
			}
			else if (mode == 7) {
				if (frogObject1.rightLowerArmx <= 0.0f)
					frogObject1.rightLowerArmx += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegx < 60.0f)
					frogObject1.leftUpperLegx += 2.0f;
			}
			else if (mode == 10) {
				if (frogObject1.leftLowerLegx < 120.0f)
					frogObject1.leftLowerLegx += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegx < 60.0f)
					frogObject1.rightUpperLegx += 2.0f;
			}
			else if (mode == 12) {
				if (frogObject1.rightLowerLegx < 120.0f)
					frogObject1.rightLowerLegx += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'X': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatex -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.headx >= -45.0f)
					frogObject1.headx -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipx > -45.0f)
				frogObject1.hipx -= 2.0f;
			}
			
			else if (mode == 3) {
				// Head Rotation
				if (frogObject1.torsox >= -25.0f)
					frogObject1.torsox -= 2.0f;
			}
			else if (mode == 4) {
				//Upper Arm Rotation
				frogObject1.leftUpperArmx -= 2.0f;
			}
			else if (mode == 5) {
				if ((((int)frogObject1.leftUpperArmx) % 360 <= 20.0f || ((int)frogObject1.leftUpperArmx) % 360 >= 340.0f) && frogObject1.leftUpperArmy >= 30.0f) {
					cout << "problem case" << endl;
					if (frogObject1.leftUpperArmz > -90.0f && frogObject1.leftLowerArmx > -135.0f && frogObject1.leftLowerArmx > 7.0 / 4.0*frogObject1.leftUpperArmz) {
						frogObject1.leftLowerArmx -= 2.0f;
					}
					else if (frogObject1.leftUpperArmz < -90.0f) {
						if (frogObject1.leftLowerArmx > -135.0f) {
							frogObject1.leftLowerArmx -= 2.0f;
						}
					}
				}
				else {
					if (frogObject1.leftLowerArmx > -135.0f) {
						frogObject1.leftLowerArmx -= 2.0f;
					}
				}
			}
			else if (mode == 6) {
				//Upper Arm Rotation
				frogObject1.rightUpperArmx -= 2.0f;
			}
			else if (mode == 7) {
				if ((((int)frogObject1.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject1.rightUpperArmx) % 360 >= 340.0f) && frogObject1.rightUpperArmy < -30.0f) {
					cout << "problem case" << endl;
					if (frogObject1.rightUpperArmz < 90.0f && frogObject1.rightLowerArmx > -135.0f && frogObject1.rightLowerArmx > -1.0*7.0 / 4.0*frogObject1.rightUpperArmz) {
						frogObject1.rightLowerArmx -= 2.0f;
					}
					else if (frogObject1.rightUpperArmz > 90.0f) {
						if (frogObject1.rightLowerArmx > -135.0f) {
							frogObject1.rightLowerArmx -= 2.0f;
						}
					}
				}
				else {
					if (frogObject1.rightLowerArmx > -135.0f) {
						frogObject1.rightLowerArmx -= 2.0f;
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegx > -90.0f)
					frogObject1.leftUpperLegx -= 2.0f;
			}
			else if (mode == 10) {
				if (frogObject1.leftLowerLegx > 0.0f)
					frogObject1.leftLowerLegx -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegx > -90.0f)
					frogObject1.rightUpperLegx -= 2.0f;
			}
			else if (mode == 12) {
				if (frogObject1.rightLowerLegx > 0.0f)
					frogObject1.rightLowerLegx -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'c': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatey += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.heady <= 60.0f)
					frogObject1.heady += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipy < 30.0f)
				frogObject1.hipy += 2.0f;
			}
			else if (mode == 3) {
				// Head Rotation
				if (frogObject1.torsoy <= 45.0f)
					frogObject1.torsoy += 2.0f;
			}
			else if (mode == 4) {
				// Left Upper Arm Rotation
				// cout<<(90+frogObject1.leftUpperArmz)<<":"<<(180.0/M_PI)*acos(0.75*(sin(-1*frogObject1.leftUpperArmz))) <<endl;
				if (((int)frogObject1.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject1.rightUpperArmx) % 360 >= 340.0f) {
					// cout<<"problem case"<<endl;
					cout << frogObject1.leftUpperArmz << ":" << frogObject1.leftLowerArmx << endl;
					if (frogObject1.leftUpperArmz > 4.0 / 7.0*frogObject1.leftLowerArmx) {
						if (frogObject1.leftUpperArmy < 30.0f)
							frogObject1.leftUpperArmy += 2.0f;
					}
					else {
						// cout<<"case 2"<<endl;
						if (frogObject1.leftUpperArmy < 90.0f)
							frogObject1.leftUpperArmy += 2.0f;
					}
				}
				else {
					// cout<<"no roblem"<<endl;
					if (frogObject1.leftUpperArmy < 90.0f)
						frogObject1.leftUpperArmy += 2.0f;
				}
			}
			else if (mode == 6) {
				// Head Rotation
				if (frogObject1.rightUpperArmy<90.0f)
					frogObject1.rightUpperArmy += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegy < 30.0f)
					frogObject1.leftUpperLegy += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegy < 30.0f)
					frogObject1.rightUpperLegy += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'C': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject1.hipTranslatey -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject1.heady >= -60.0f)
					frogObject1.heady -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject1.hipy > -30.0f)
				frogObject1.hipy -= 2.0f;
			}
			else if (mode == 3) {
				// Head Rotation
				if (frogObject1.torsoy >= -45.0f)
					frogObject1.torsoy -= 2.0f;
			}
			else if (mode == 4) {
				// Head Rotation
				if (frogObject1.leftUpperArmy >= -90.0f)
					frogObject1.leftUpperArmy -= 2.0f;
			}
			else if (mode == 6) {
				// Right Upper Arm Rotation
				if (((int)frogObject1.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject1.rightUpperArmx) % 360 >= 340.0f) {
					// cout<<"problem"<<endl;
					if (frogObject1.rightUpperArmz < fabs(4.0 / 7.0*frogObject1.rightLowerArmx)) {
						if (frogObject1.rightUpperArmy > -30.0f) {
							frogObject1.rightUpperArmy -= 2.0f;
						}
					}
					else  if (frogObject1.rightUpperArmy > -90.0f) {
						frogObject1.rightUpperArmy -= 2.0f;
					}
					else {
						// cout<<"no problem"<<endl;
						if (frogObject1.rightUpperArmy > -90.0f) {
							frogObject1.rightUpperArmy -= 2.0f;
						}
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject1.leftUpperLegy > -30.0f)
					frogObject1.leftUpperLegy -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject1.rightUpperLegy > -30.0f)
					frogObject1.rightUpperLegy -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'n': {		
		cout << "yay";
		
		if (frogObject1.hipTranslatey > 10.0f) {
			flag1 = 0;
		}
		if (frogObject1.hipTranslatey < 0.0f) {
			flag1 = 1;
		}
			if (flag1==1) {
				frogObject1.hipTranslatey += frogObject1.speed *0.2f;
				frogObject1.hipTranslatex += frogObject1.speed *0.2f;
				frogObject1.leftUpperArmx -= frogObject1.speed *1.4f;
				frogObject1.rightUpperArmx -= frogObject1.speed *1.2f;
				frogObject1.leftLowerArmx += frogObject1.speed *1.2f;
				frogObject1.rightLowerArmx += frogObject1.speed *1.4f;
				frogObject1.headz += frogObject1.speed *0.8f;
				frogObject1.torsox -= frogObject1.speed *0.4f;
				frogObject1.rightUpperLegx += frogObject1.speed *0.6f;
				frogObject1.leftUpperLegx += frogObject1.speed *0.4f;
				frogObject1.rightLowerLegx += frogObject1.speed *0.2f;
				frogObject1.leftLowerLegx += frogObject1.speed *0.2f;
			}
			if (flag1==0) {
				frogObject1.hipTranslatey -= frogObject1.speed *0.2f;
				frogObject1.hipTranslatex += frogObject1.speed *0.2f;
				frogObject1.leftUpperArmx += frogObject1.speed *1.4f;
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

			
			if (frogObject2.hipTranslatey > 10.0f) {
				flag2 = 0;
			}
			if (frogObject2.hipTranslatey < 0.0f) {
				flag2 = 1;
			}
			if (flag2==1) {
				frogObject2.hipTranslatey += frogObject2.speed * 0.2f;
				frogObject2.hipTranslatex += frogObject2.speed * 0.2f;
				frogObject2.leftUpperArmx -= frogObject2.speed *1.4f;
				frogObject2.rightUpperArmx -= frogObject2.speed *1.2f;
				frogObject2.leftLowerArmx += frogObject2.speed *1.2f;
				frogObject2.rightLowerArmx += frogObject2.speed *1.4f;
				frogObject2.headz += frogObject2.speed *0.8f;
				frogObject2.torsox -= frogObject2.speed *0.4f;
				frogObject2.rightUpperLegx += frogObject2.speed *0.6f;
				frogObject2.leftUpperLegx += frogObject2.speed *0.4f;
				frogObject2.rightLowerLegx += frogObject2.speed *0.2f;
				frogObject2.leftLowerLegx += frogObject2.speed *0.2f;
			}
			if (flag2==0) {
				frogObject2.hipTranslatey -= frogObject2.speed * 0.2f;
				frogObject2.hipTranslatex += frogObject2.speed * 0.2f;
				frogObject2.leftUpperArmx += frogObject2.speed *1.4f;
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
			glutPostRedisplay();
		
		break;
	}
			 
	default: {	}
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
	glutMouseFunc(mouse);	//	
	initGL();                       
	glutMainLoop();                 
	return 0;
}
