
#include "frog.h"

void  frog::createHeadList(){
	headList=glGenLists (1);
	glNewList(headList, GL_COMPILE);
	glPushMatrix();
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinDark.bmp");
		
		GLUquadricObj *quadratic1;
		quadratic1 = gluNewQuadric();
		gluQuadricTexture(quadratic1, 1);
		glTranslatef(0.0f, 2.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		
		gluCylinder(quadratic1,2.5f,2.5f,3.0f,32,32);
		glTranslatef(0.0f, 0.0f, 3.0f);
		gluDisk(quadratic1,0.0f,2.5f,32,32);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic, 1);
		gluCylinder(quadratic, 2.5f, 1.0f, 4.0f, 32, 32);
	glPopMatrix();

	glEndList();
}



void frog::createTorsoList(){
	torsoList=glGenLists (1);
	glNewList(torsoList, GL_COMPILE);
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinLight.bmp");
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,2.5f,4.0f,4.0f,32,32);
		gluDisk(quadratic,0.0f,2.5f,32,32);
		glTranslatef(0.0f, 0.0f, 4.0f);
		gluCylinder(quadratic, 4.0f, 2.5f, 4.0f, 32, 32);
		glPushMatrix();
			glTranslatef(0.0,0.0,4.0f);
			gluDisk(quadratic,0.0f,2.5f,32,32);
		glPopMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createUpperArmList(){
	upperArmList=glGenLists (1);
	glNewList(upperArmList, GL_COMPILE);
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinDark.bmp");
		glColor3f(1.0f, 1.0f, 1.0f);    
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,0.8f,0.8f,8.0f,32,32);
		gluDisk(quadratic,0.0f,0.8f,32,32);
		glPushMatrix();
			glTranslatef(0.0,0.0,8.0f);
			gluDisk(quadratic,0.0f,0.8f,32,32);
		glPopMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createLowerArmList(){
	lowerArmList=glGenLists (1);
	glNewList(lowerArmList, GL_COMPILE);
		glColor3f(1.0f, 1.0f, 1.0f);    
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,0.8f,0.7f,5.0f,32,32);
		gluDisk(quadratic,0.0f,0.8f,32,32);
		glPushMatrix();
			glTranslatef(0.0,0.0,5.0f);
			gluDisk(quadratic,0.0f,0.7f,32,32);
		glPopMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createHipList(){
    hipList=glGenLists (1);
	glNewList(hipList, GL_COMPILE);
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinLight.bmp");
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,2.1f,2.1f,4.0f,32,32);

		glPushMatrix();
			glTranslatef(0.0,0.0,1.0f);
			gluDisk(quadratic,0.0f,2.1f,32,32);
		glPopMatrix();

		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createUpperLegList(){
	upperLegList=glGenLists (1);
	glNewList(upperLegList, GL_COMPILE);
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinDark.bmp");
		glColor3f(1.0f, 1.0f, 1.0f);    
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,1.0f,0.7f,7.0f,32,32);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createLowerLegList(){
	lowerLegList=glGenLists (1);
	glNewList(lowerLegList, GL_COMPILE);
		Texture tex;
		frogTexture = tex.loadBMP_custom("./images/skinDark.bmp");
		glColor3f(1.0f, 1.0f, 1.0f);    
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,0.7f,0.7f,7.0f,32,32);

		glPushMatrix();
			glTranslatef(0.0,0.0,7.0f);
			gluDisk(quadratic,0.0f,0.7f,32,32);
		glPopMatrix();

		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void frog::createAllLists(){
	createHeadList();
	createTorsoList();
	createUpperArmList();
	createLowerArmList();
	createHipList();
	createUpperLegList();
	createLowerLegList();
}

void frog::drawFrog(){
	glPushMatrix();
	glScalef(0.6f, 0.6f, 0.6f);
		// hip
		glTranslatef(hipTranslatex,hipTranslatey,hipTranslatez);
		
		//glTranslatef(0.0f, -1.0f, 0.0f);
		glRotatef(hipx,1.0,0.0,0.0);
		glRotatef(hipz,0.0,0.0,1.0);
		glRotatef(hipy,0.0,1.0,0.0);
		//glTranslatef(0.0f, 1.0f, 0.0f);
		glCallList(hipList);
		glPushMatrix();
			glTranslatef(-1.1f,-4.0f,0.0f);
			glRotatef(leftUpperLegx,1.0,0.0,0.0);
			glRotatef(leftUpperLegz,0.0,0.0,1.0);
			glRotatef(leftUpperLegy,0.0,1.0,0.0);
			glCallList(upperLegList);															
			glTranslatef(0.0f,-7.0f,0.0f);
			glRotatef(leftLowerLegx,1.0,0.0,0.0);
			glCallList(lowerLegList);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.1f,-4.0f,0.0f);
			glRotatef(rightUpperLegx,1.0,0.0,0.0);
			glRotatef(rightUpperLegz,0.0,0.0,1.0);
			glRotatef(rightUpperLegy,0.0,1.0,0.0);
			glCallList(upperLegList);
			glTranslatef(0.0f,-7.0f,0.0f);
			glRotatef(rightLowerLegx,1.0,0.0,0.0);
			glCallList(lowerLegList);
		glPopMatrix();

			glRotatef(torsox,1.0,0.0,0.0);
			glRotatef(torsoz,0.0,0.0,1.0);
			glRotatef(torsoy,0.0,1.0,0.0);
			glTranslatef(0.0f, 8.0f, 0.0f);
			glCallList(torsoList);
	

		glPushMatrix();
			glTranslatef(3.0f,2.5f,0.0f);
			glRotatef(rightUpperArmx,1.0,0.0,0.0);
			glRotatef(rightUpperArmz,0.0,0.0,1.0);
			glRotatef(rightUpperArmy,0.0,1.0,0.0);
			glCallList(upperArmList);

			glTranslatef(0.0,-8.0f,0.0f);
			glRotatef(rightLowerArmx,1.0,0.0,0.0f);
			glCallList(lowerArmList);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-3.0f,2.5f,0.0f);
			glRotatef(leftUpperArmx,1.0,0.0,0.0);
			glRotatef(leftUpperArmz,0.0,0.0,1.0);
			glRotatef(leftUpperArmy,0.0,1.0,0.0);
			glCallList(upperArmList);

			glTranslatef(0.0,-8.0f,0.0f);
			glRotatef(leftLowerArmx,1.0,0.0,0.0f);
			glCallList(lowerArmList);
		glPopMatrix();


		glRotatef(headx,1.0,0.0,0.0);
		glRotatef(headz,0.0,0.0,1.0);
		glRotatef(heady,0.0,1.0,0.0);
		glTranslatef(0.0f,1.3f,0.0f);
		glCallList(headList);


	glPopMatrix();
}


frog::frog(){
	headx=-10.0f;
	heady=0.0f;
	headz=0.0f;

	torsox=0.0f;
	torsoy=0.0f;
	torsoz=0.0f;

	leftUpperArmx=-60.0f;
	leftUpperArmy=0.0f;
	leftUpperArmz=-10.0f;

	rightUpperArmx=-60.0f;
	rightUpperArmy=0.0f;
	rightUpperArmz=10.0f;

	leftLowerArmx=-105.0f;
	rightLowerArmx=-105.0f;

	hipx=90.0f;
	hipy=0.0f;
	hipz=-90.0f;
	hipTranslatex=-50.0f;
	hipTranslatey=0.0f;
	hipTranslatez=0.0f;

	leftUpperLegx=-75.0f;
	leftUpperLegy=0.0f;
	leftUpperLegz=-5.0f;

	rightUpperLegx=-75.0f;
	rightUpperLegy=0.0f;
	rightUpperLegz=5.0f;

	leftLowerLegx=45.0f;
	rightLowerLegx=45.0f;
}

void frog::reset(){
	headx = -10.0f;
	heady = 0.0f;
	headz = 0.0f;

	torsox = 0.0f;
	torsoy = 0.0f;
	torsoz = 0.0f;

	leftUpperArmx = -60.0f;
	leftUpperArmy = 0.0f;
	leftUpperArmz = -10.0f;

	rightUpperArmx = -60.0f;
	rightUpperArmy = 0.0f;
	rightUpperArmz = 10.0f;

	leftLowerArmx = -105.0f;
	rightLowerArmx = -105.0f;

	hipx = 90.0f;
	hipy = 0.0f;
	hipz = -90.0f;
	hipTranslatex = -50.0f;
	hipTranslatey = 0.0f;
	hipTranslatez = 0.0f;

	leftUpperLegx = -75.0f;
	leftUpperLegy = 0.0f;
	leftUpperLegz = -5.0f;

	rightUpperLegx = -75.0f;
	rightUpperLegy = 0.0f;
	rightUpperLegz = 5.0f;

	leftLowerLegx = 45.0f;
	rightLowerLegx = 45.0f;
}