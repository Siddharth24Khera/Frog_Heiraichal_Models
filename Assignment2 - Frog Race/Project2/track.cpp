#include "track.h"



track::track()
{	
}

void track::createQuadList()
{
	float boxSize = 10.0f;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	quadList = glGenLists(1);
	glNewList(quadList, GL_COMPILE);

	Texture tex;
	trackTexture = tex.loadBMP_custom("./images/sand.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(50, 0, 50);
	glTexCoord2f(0.0, 1.0); glVertex3f(-50, 0, 50);
	glTexCoord2f(1.0, 1.0); glVertex3f(-50, 0, -50);
	glTexCoord2f(1.0, 0.0); glVertex3f(50, 0, -50);
	/*glTexCoord2f(0.0, 0.0); glVertex3f(boxSize, -boxSize, boxSize);
	glTexCoord2f(0.0, 1.0); glVertex3f(boxSize, boxSize, boxSize);
	glTexCoord2f(1.0, 1.0); glVertex3f(-boxSize, boxSize, boxSize);
	glTexCoord2f(1.0, 0.0); glVertex3f(-boxSize, -boxSize, boxSize);*/
	glEnd();
	glEndList();
}

void track::drawTrack()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f,-6.0f, 0.0f);
	glCallList(quadList);
	glPopMatrix();
}