// Contains common stuff for all project units

#include "common_defs.h"

void RunShader(int width, int height)
{
	glViewport(0, 0, width, height);    
	glMatrixMode(GL_PROJECTION );
	glLoadIdentity(); 
	glOrtho(0.0F, 1.0F, 0.0F, 1.0F, -1.0F, 1.0F);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();				
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0F, 0.0F );  
		glVertex2f(0.0F, 0.0F);

		glTexCoord2f(0.0F, (GLfloat)height);
		glVertex2f(0.0F, 1.0F);

		glTexCoord2f((GLfloat)width, (GLfloat)height); 
		glVertex2f(1.0F, 1.0F);

		glTexCoord2f((GLfloat)width, 0.0F); 
		glVertex2f(1.0F, 0.0F);
	}
	glEnd(); 
}