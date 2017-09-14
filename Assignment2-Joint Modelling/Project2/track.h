#ifndef TRA_H
#define TRA_H

#include "tex.h"
#include "Dependencies\freeglut\freeglut.h"
class track
{
public:
	track();
	GLuint quadList;
	void createQuadList();
	void drawTrack();

private:
	GLuint trackTexture;
};

#endif