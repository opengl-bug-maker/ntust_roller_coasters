//
// Created by IceLenf on 2022/10/28.
//

#include "Cuboid.h"


void Cuboid::GLDraw() {
//region gl
    glBegin(GL_QUADS);
    glNormal3f( 0,0,1);
    glVertex3f( 0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5,-0.5, 0.5);
    glVertex3f( 0.5,-0.5, 0.5);

    glNormal3f( 0, 0, -1);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f( 0.5,-0.5, -0.5);
    glVertex3f(-0.5,-0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glNormal3f( 0,1,0);
    glVertex3f( 0.5,0.5, 0.5);
    glVertex3f(-0.5,0.5, 0.5);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f( 0.5,0.5,-0.5);


    glNormal3f( 0,-1,0);
    glVertex3f( 0.5,-0.5, 0.5);
    glVertex3f(-0.5,-0.5, 0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f( 0.5,-0.5,-0.5);

    glNormal3f( 1,0,0);
    glVertex3f( 0.5, 0.5, 0.5);
    glVertex3f( 0.5,-0.5, 0.5);
    glVertex3f( 0.5,-0.5,-0.5);
    glVertex3f( 0.5, 0.5,-0.5);

    glNormal3f(-1,0,0);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5,-0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5,-0.5, 0.5);
    glEnd();
//endregion
}

Cuboid::Cuboid(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color) : Obj(pos, size, rotate,
                                                                                               color) {}

