#include "Cylinder.h"
#include "cmath"
# define M_PI           3.14159265358979323846
double to_degree(double x) {
    return (x * 180.0)/ M_PI;
}
void Cylinder::GLDraw(){
    glBegin(GL_QUAD_STRIP);
    const float rate = 2;
    for (int j = 0; j <= 360; j+= rate) {
        glVertex3f(cos(to_degree(j)), 1, sin(to_degree(j)));
        glVertex3f(cos(to_degree(j)), -1, sin(to_degree(j)));
    }

    glBegin(GL_POLYGON);
    for (int j = 0; j <= 360; j += rate) {
        glVertex3f(cos(to_degree(j)), 1, sin(to_degree(j)));
    }
    glEnd();


    glBegin(GL_POLYGON);
    for (int j = 0; j <= 360; j += rate) {
        glVertex3f(cos(to_degree(j)), -1, sin(to_degree(j)));
    }
    glEnd();
}

Cylinder::Cylinder(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color) : Obj(pos,
                                                                                                                    size,
                                                                                                                    front,
                                                                                                                    top,
                                                                                                                    color) {}