#ifndef FROG_H
#define FROG_H

#include "Dependencies\freeglut\freeglut.h"
//#include "Dependencies\glew\glew.h"
#include <stdlib.h>
#include <iostream>
#include "tex.h"
using namespace std;

class frog{
public:

	float speed;

	float headx;
	float heady;
	float headz;


	float torsox;
	float torsoy;
	float torsoz;

	float leftUpperArmx;
	float leftUpperArmy;
	float leftUpperArmz;

	float rightUpperArmx;
	float rightUpperArmy;
	float rightUpperArmz;

	float leftLowerArmx;
	float rightLowerArmx;

	float hipx;
	float hipy;
	float hipz;
	float hipTranslatex;
	float hipTranslatey;
	float hipTranslatez;

	float leftUpperLegx;
	float leftUpperLegy;
	float leftUpperLegz;

	float rightUpperLegx;
	float rightUpperLegy;
	float rightUpperLegz;

	float leftLowerLegx;
	float rightLowerLegx;

	GLuint headList;
	GLuint neckList;
	GLuint torsoList;
	GLuint upperArmList;
	GLuint lowerArmList;
	GLuint hipList;
	GLuint upperLegList;
	GLuint lowerLegList;

	void createAllLists();
	void drawFrog();
	void  reset();
	frog();
	frog(float);


private:
	void  createHeadList();

	void  createTorsoList();
	void  createUpperArmList();
	void  createLowerArmList();
	void  createHipList();
	void  createUpperLegList();
	void  createLowerLegList();
	GLuint frogTexture;
};
#endif
