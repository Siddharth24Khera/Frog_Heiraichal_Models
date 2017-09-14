
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

/* Global variables */
char title[] = "Frog";
float degree = 0.0f;
float verticalDegree = 0.0f;
Box boxObject;
track trackObject;



float eyex = 0.0f, eyey = 0.0f;
float eyez = 60.0f;
frog frogObject;
int mode = -1;
/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);        
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_SMOOTH);  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
	frogObject.createAllLists();
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
	frogObject.drawFrog();
	/*glTranslatef(0.0f, 0.0f, 20.0f);
	frogObject.drawFrog();*/
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


/*Body movement scheme is designed in the following way
There are modes which decide the bosy parts controlled by z,x and c.
0: Hip-Translation
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
		frogObject.reset();
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
				frogObject.hipTranslatez += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.headz <= 45.0f)
					frogObject.headz += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipz < 45.0f)
				frogObject.hipz += 2.0f;
			}
			else if (mode == 3) {
				// Torso Rotation
				if (frogObject.torsoz <= 25.0f)
					frogObject.torsoz += 2.0f;
			}
			else if (mode == 4) {
				if ((((int)frogObject.leftUpperArmx) % 360 <= 20.0f || ((int)frogObject.leftUpperArmx) % 360 >= 340.0f) && frogObject.leftUpperArmy >= 30.0f) {
					/*cout<<"problem case"<<endl;
					cout<<"angle"<<":"<<4.0/7.0*frogObject.leftLowerArmx<<endl;*/
					if (frogObject.leftUpperArmz < 0.0f && frogObject.leftUpperArmz < 4.0 / 7.0*frogObject.leftLowerArmx) {
						frogObject.leftUpperArmz += 2.0f;
					}
				}
				else {
					if (frogObject.leftUpperArmz < 0.0f)
						frogObject.leftUpperArmz += 2.0f;
				}
			}
			else if (mode == 6) {
				if (frogObject.rightUpperArmz<180.0f)
					frogObject.rightUpperArmz += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegz < 0.0f)
					frogObject.leftUpperLegz += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegz < 45.0f)
					frogObject.rightUpperLegz += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'Z': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject.hipTranslatez -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.headz >= -45.0f)
					frogObject.headz -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipz > -45.0f)
				frogObject.hipz -= 2.0f;
			}
			else if (mode == 3) {
				// Neck Rotation
				if (frogObject.torsoz >= -25.0f)
					frogObject.torsoz -= 2.0f;
			}
			else if (mode == 4) {
				// cout<<"AAYA"<<endl;
				if (frogObject.leftUpperArmz >= -180.0f)
					frogObject.leftUpperArmz -= 2.0f;
			}
			else if (mode == 6) {
				// cout<<fabs(4.0/7.0*frogObject.rightLowerArmx)<<endl;
				if ((((int)frogObject.rightLowerArmx) % 360 < 20.0f || ((int)frogObject.rightLowerArmx) % 360 > 340.0f) && frogObject.rightUpperArmy < -30.0f) {
					if (frogObject.rightUpperArmz > 0.0f && frogObject.rightUpperArmz > fabs(4.0 / 7.0*frogObject.rightLowerArmx)) {
						frogObject.rightUpperArmz -= 2.0f;
					}
				}
				else {
					if (frogObject.rightUpperArmz > 0.0f) {
						frogObject.rightUpperArmz -= 2.0f;
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegz > -45.0f)
					frogObject.leftUpperLegz -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegz > 0.0f)
					frogObject.rightUpperLegz -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'x': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject.hipTranslatex += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.headx <= 45.0f)
					frogObject.headx += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipx < 45.0f)
				frogObject.hipx += 2.0f;
			}
			
			else if (mode == 3) {
				// Neck Rotation
				if (frogObject.torsox <= 25.0f)
					frogObject.torsox += 2.0f;
			}
			else if (mode == 4) {
				// Upper Arm Rotation
				frogObject.leftUpperArmx += 2.0f;
			}
			else if (mode == 5) {
				if (frogObject.leftLowerArmx <= 0.0f)
					frogObject.leftLowerArmx += 2.0f;
			}
			else if (mode == 6) {
				// Upper Arm Rotation
				frogObject.rightUpperArmx += 2.0f;
			}
			else if (mode == 7) {
				if (frogObject.rightLowerArmx <= 0.0f)
					frogObject.rightLowerArmx += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegx < 60.0f)
					frogObject.leftUpperLegx += 2.0f;
			}
			else if (mode == 10) {
				if (frogObject.leftLowerLegx < 120.0f)
					frogObject.leftLowerLegx += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegx < 60.0f)
					frogObject.rightUpperLegx += 2.0f;
			}
			else if (mode == 12) {
				if (frogObject.rightLowerLegx < 120.0f)
					frogObject.rightLowerLegx += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'X': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject.hipTranslatex -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.headx >= -45.0f)
					frogObject.headx -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipx > -45.0f)
				frogObject.hipx -= 2.0f;
			}
			
			else if (mode == 3) {
				// Head Rotation
				if (frogObject.torsox >= -25.0f)
					frogObject.torsox -= 2.0f;
			}
			else if (mode == 4) {
				//Upper Arm Rotation
				frogObject.leftUpperArmx -= 2.0f;
			}
			else if (mode == 5) {
				if ((((int)frogObject.leftUpperArmx) % 360 <= 20.0f || ((int)frogObject.leftUpperArmx) % 360 >= 340.0f) && frogObject.leftUpperArmy >= 30.0f) {
					cout << "problem case" << endl;
					if (frogObject.leftUpperArmz > -90.0f && frogObject.leftLowerArmx > -135.0f && frogObject.leftLowerArmx > 7.0 / 4.0*frogObject.leftUpperArmz) {
						frogObject.leftLowerArmx -= 2.0f;
					}
					else if (frogObject.leftUpperArmz < -90.0f) {
						if (frogObject.leftLowerArmx > -135.0f) {
							frogObject.leftLowerArmx -= 2.0f;
						}
					}
				}
				else {
					if (frogObject.leftLowerArmx > -135.0f) {
						frogObject.leftLowerArmx -= 2.0f;
					}
				}
			}
			else if (mode == 6) {
				//Upper Arm Rotation
				frogObject.rightUpperArmx -= 2.0f;
			}
			else if (mode == 7) {
				if ((((int)frogObject.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject.rightUpperArmx) % 360 >= 340.0f) && frogObject.rightUpperArmy < -30.0f) {
					cout << "problem case" << endl;
					if (frogObject.rightUpperArmz < 90.0f && frogObject.rightLowerArmx > -135.0f && frogObject.rightLowerArmx > -1.0*7.0 / 4.0*frogObject.rightUpperArmz) {
						frogObject.rightLowerArmx -= 2.0f;
					}
					else if (frogObject.rightUpperArmz > 90.0f) {
						if (frogObject.rightLowerArmx > -135.0f) {
							frogObject.rightLowerArmx -= 2.0f;
						}
					}
				}
				else {
					if (frogObject.rightLowerArmx > -135.0f) {
						frogObject.rightLowerArmx -= 2.0f;
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegx > -90.0f)
					frogObject.leftUpperLegx -= 2.0f;
			}
			else if (mode == 10) {
				if (frogObject.leftLowerLegx > 0.0f)
					frogObject.leftLowerLegx -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegx > -90.0f)
					frogObject.rightUpperLegx -= 2.0f;
			}
			else if (mode == 12) {
				if (frogObject.rightLowerLegx > 0.0f)
					frogObject.rightLowerLegx -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'c': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject.hipTranslatey += 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.heady <= 60.0f)
					frogObject.heady += 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipy < 30.0f)
				frogObject.hipy += 2.0f;
			}
			else if (mode == 3) {
				// Head Rotation
				if (frogObject.torsoy <= 45.0f)
					frogObject.torsoy += 2.0f;
			}
			else if (mode == 4) {
				// Left Upper Arm Rotation
				// cout<<(90+frogObject.leftUpperArmz)<<":"<<(180.0/M_PI)*acos(0.75*(sin(-1*frogObject.leftUpperArmz))) <<endl;
				if (((int)frogObject.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject.rightUpperArmx) % 360 >= 340.0f) {
					// cout<<"problem case"<<endl;
					cout << frogObject.leftUpperArmz << ":" << frogObject.leftLowerArmx << endl;
					if (frogObject.leftUpperArmz > 4.0 / 7.0*frogObject.leftLowerArmx) {
						if (frogObject.leftUpperArmy < 30.0f)
							frogObject.leftUpperArmy += 2.0f;
					}
					else {
						// cout<<"case 2"<<endl;
						if (frogObject.leftUpperArmy < 90.0f)
							frogObject.leftUpperArmy += 2.0f;
					}
				}
				else {
					// cout<<"no roblem"<<endl;
					if (frogObject.leftUpperArmy < 90.0f)
						frogObject.leftUpperArmy += 2.0f;
				}
			}
			else if (mode == 6) {
				// Head Rotation
				if (frogObject.rightUpperArmy<90.0f)
					frogObject.rightUpperArmy += 2.0f;
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegy < 30.0f)
					frogObject.leftUpperLegy += 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegy < 30.0f)
					frogObject.rightUpperLegy += 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'C': {
		if (mode >= 0) {
			if (mode == 0) {
				//Hip Translation
				frogObject.hipTranslatey -= 0.4f;
			}
			else if (mode == 1) {
				// Head Rotation
				if (frogObject.heady >= -60.0f)
					frogObject.heady -= 2.0f;
			}
			else if (mode == 2) {
				//if (frogObject.hipy > -30.0f)
				frogObject.hipy -= 2.0f;
			}
			else if (mode == 3) {
				// Head Rotation
				if (frogObject.torsoy >= -45.0f)
					frogObject.torsoy -= 2.0f;
			}
			else if (mode == 4) {
				// Head Rotation
				if (frogObject.leftUpperArmy >= -90.0f)
					frogObject.leftUpperArmy -= 2.0f;
			}
			else if (mode == 6) {
				// Right Upper Arm Rotation
				if (((int)frogObject.rightUpperArmx) % 360 <= 20.0f || ((int)frogObject.rightUpperArmx) % 360 >= 340.0f) {
					// cout<<"problem"<<endl;
					if (frogObject.rightUpperArmz < fabs(4.0 / 7.0*frogObject.rightLowerArmx)) {
						if (frogObject.rightUpperArmy > -30.0f) {
							frogObject.rightUpperArmy -= 2.0f;
						}
					}
					else  if (frogObject.rightUpperArmy > -90.0f) {
						frogObject.rightUpperArmy -= 2.0f;
					}
					else {
						// cout<<"no problem"<<endl;
						if (frogObject.rightUpperArmy > -90.0f) {
							frogObject.rightUpperArmy -= 2.0f;
						}
					}
				}
			}
			
			else if (mode == 9) {
				if (frogObject.leftUpperLegy > -30.0f)
					frogObject.leftUpperLegy -= 2.0f;
			}
			else if (mode == 11) {
				if (frogObject.rightUpperLegy > -30.0f)
					frogObject.rightUpperLegy -= 2.0f;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'n': {		
			
			if (frogObject.hipTranslatey < 10.0f) {
				frogObject.hipTranslatey += 0.2f;
				frogObject.hipTranslatex += 0.2f;
				frogObject.leftUpperArmx -= 1.4f;
				frogObject.rightUpperArmx -= 1.2f;
				frogObject.leftLowerArmx += 1.2f;
				frogObject.rightLowerArmx += 1.4f;
				frogObject.headz += 0.8f;
				frogObject.torsox -= 0.4f;
				frogObject.rightUpperLegx += 0.6f;
				frogObject.leftUpperLegx += 0.4f;
				frogObject.rightLowerLegx += 0.2f;
				frogObject.leftLowerLegx += 0.2f;
			}
			glutPostRedisplay();			
		
		break;
	}
	case 'm': {

		if (frogObject.hipTranslatey > 0.0f) {
			frogObject.hipTranslatey -= 0.1f;
			frogObject.hipTranslatex += 0.1f;
			frogObject.leftUpperArmx += 0.7f;
			frogObject.rightUpperArmx += 0.6f;
			frogObject.leftLowerArmx -= 0.6f;
			frogObject.rightLowerArmx -= 0.7f;
			frogObject.headz -= 0.4f;
			frogObject.torsox += 0.2f;
			frogObject.rightUpperLegx -= 0.3f;
			frogObject.leftUpperLegx -= 0.2f;
			frogObject.rightLowerLegx -= 0.1f;
			frogObject.leftLowerLegx -= 0.1f;
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
