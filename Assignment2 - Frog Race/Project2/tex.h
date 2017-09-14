#ifndef TEX_H
#define TEX_H

#include "Dependencies\freeglut\freeglut.h"
//#include "Dependencies\glew\glew.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Texture{
public:
	GLuint loadBMP_custom(const char * imagepath);
};

#endif

