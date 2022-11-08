//
// Created by IceLenf on 2022/11/8.
//

#include "CuboidAnchorBottom.h"

void CuboidAnchorBottom::init() {
    Obj::init();
}

void CuboidAnchorBottom::GLDraw() {
//region gl
    glBegin(GL_QUADS);
    glNormal3f( 0,0,1);
    glVertex3f( 1.0, 0.5, 0.5);
    glVertex3f( 0.0, 0.5, 0.5);
    glVertex3f( 0.0,-0.5, 0.5);
    glVertex3f( 1.0,-0.5, 0.5);

    glNormal3f( 0, 0, -1);
    glVertex3f( 1.0, 0.5, -0.5);
    glVertex3f( 1.0,-0.5, -0.5);
    glVertex3f( 0.0,-0.5, -0.5);
    glVertex3f( 0.0, 0.5, -0.5);

    glNormal3f( 0,1,0);
    glVertex3f( 1.0,0.5, 0.5);
    glVertex3f( 0.0,0.5, 0.5);
    glVertex3f( 0.0,0.5,-0.5);
    glVertex3f( 1.0,0.5,-0.5);


    glNormal3f( 0,-1,0);
    glVertex3f( 1.0,-0.5, 0.5);
    glVertex3f( 0.0,-0.5, 0.5);
    glVertex3f( 0.0,-0.5,-0.5);
    glVertex3f( 1.0,-0.5,-0.5);

    glNormal3f( 1,0,0);
    glVertex3f( 1.0, 0.5, 0.5);
    glVertex3f( 1.0,-0.5, 0.5);
    glVertex3f( 1.0,-0.5,-0.5);
    glVertex3f( 1.0, 0.5,-0.5);

    glNormal3f(-1,0,0);
    glVertex3f( 0.0, 0.5, 0.5);
    glVertex3f( 0.0, 0.5,-0.5);
    glVertex3f( 0.0,-0.5,-0.5);
    glVertex3f( 0.0,-0.5, 0.5);
    glEnd();
//endregion
}

CuboidAnchorBottom::CuboidAnchorBottom() : Obj() {
    init();
}

CuboidAnchorBottom::CuboidAnchorBottom(const ObjInfoPack &infoPack) : Obj(infoPack) {
    init();
}

CuboidAnchorBottom::CuboidAnchorBottom(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top,
                                       GLubyte *color) : Obj(pos, size, front, top, color) {
    init();
}

