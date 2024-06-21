#include "Objects.h"
#include <GL\glut.h>

void Render(Point& point)
{
    glColor4d(point.r, point.g, point.b, point.a);
    glPointSize(point.size);

    glBegin(GL_POINTS);
        glVertex2d(point.pos.x, point.pos.y);
    glEnd();
}

void Render(Line& line)
{
    glColor4d(line.r, line.g, line.b, line.a);
    glLineWidth(line.width);

    glBegin(GL_LINES);
        glVertex2d(line.start.x, line.start.y);
        glVertex2d(line.end.x, line.end.y);
    glEnd();
        
}

void Render(Quad& quad)
{
    glColor4d(quad.r, quad.g, quad.b, quad.a);

    glBegin(GL_QUADS); 
        glVertex2d( quad.topL.x, quad.topL.y);
        glVertex2d( quad.topR.x, quad.topR.y); 
        glVertex2d( quad.bottomR.x, quad.bottomR.y);
        glVertex2d( quad.bottomL.x, quad.bottomL.y);
    glEnd();
}