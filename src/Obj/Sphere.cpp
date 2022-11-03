#include "Sphere.h"
#include <GL/gl.h>
#include <GL/glu.h>
void Sphere::GLDraw()
{
    GLUquadricObj* sphere = NULL;
    sphere = gluNewQuadric();             //Instatiate our sphere
    gluQuadricDrawStyle(sphere, GLU_FILL);//Following three method calls instantiate the texturing style
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.4, 100, 100);
}
Sphere::Sphere(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color):Obj(pos, size, front, top, color)
{
}
