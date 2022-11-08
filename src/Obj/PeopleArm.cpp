//
// Created by IceLenf on 2022/11/8.
//

#include "PeopleArm.h"

void PeopleArm::init() {
    Obj::init();
}

void PeopleArm::GLDraw() {
//region gl
    glBegin(GL_QUADS);
    glNormal3f( 0,0,1);
    glVertex3f( 6.0,  0.5, 0.4);
    glVertex3f( 6.0, -0.5, 0.4);
    glVertex3f( -1.0,-0.5, 0.4);
    glVertex3f( -1.0, 0.5, 0.4);

    glNormal3f( 0, 0, -1);
    glVertex3f( 6.0,  0.5, -0.4);
    glVertex3f( 6.0, -0.5, -0.4);
    glVertex3f( -1.0,-0.5, -0.4);
    glVertex3f( -1.0, 0.5, -0.4);

    glNormal3f( 0,1,0);
    glVertex3f( 6.0,0.5, 0.4);
    glVertex3f( 6.0,0.5,-0.4);
    glVertex3f(-1.0,0.5,-0.4);
    glVertex3f(-1.0,0.5, 0.4);


    glNormal3f( 0,-1,0);
    glVertex3f( 6.0,-0.5, 0.4);
    glVertex3f(-1.0,-0.5, 0.4);
    glVertex3f(-1.0,-0.5,-0.4);
    glVertex3f( 6.0,-0.5,-0.4);


    glNormal3f( 1,0,0);
    glVertex3f( 6.0, 0.5, 0.4);
    glVertex3f( 6.0,-0.5, 0.4);
    glVertex3f( 6.0,-0.5,-0.4);
    glVertex3f( 6.0, 0.5,-0.4);

    glNormal3f(-1,0,0);
    glVertex3f(-1.0, 0.5, 0.4);
    glVertex3f(-1.0, 0.5,-0.4);
    glVertex3f(-1.0,-0.5,-0.4);
    glVertex3f(-1.0,-0.5, 0.4);
    glEnd();
//endregion
}

PeopleArm::PeopleArm() : Obj() {
    init();
}

PeopleArm::PeopleArm(const ObjInfoPack &infoPack) : Obj(infoPack) {
    init();
}

PeopleArm::PeopleArm(const Pnt3f &pos, const Pnt3f &front, const Pnt3f &top,
                     GLubyte *color) : Obj(pos, Pnt3f(1,1,1), front, top, color) {
    init();
}

