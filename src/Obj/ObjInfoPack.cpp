//
// Created by IceLenf on 2022/10/28.
//

#include "ObjInfoPack.h"

//ObjInfoPack::ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color) : Pos(pos),
//                                                                                                     Size(size),
//                                                                                                     Rotate(rotate),
//                                                                                                     Color(color) {
//    Rotate.normalize();
//}

ObjInfoPack::ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color)
    : Pos(pos), Size(size), Front(front), Top(top), Color(color) {
    Front.normalize();
    Top.normalize();
}

const Pnt3f &ObjInfoPack::getPos() const {
    return Pos;
}

void ObjInfoPack::setPos(const Pnt3f &pos) {
    Pos = pos;
}

const Pnt3f &ObjInfoPack::getSize() const {
    return Size;
}

void ObjInfoPack::setSize(const Pnt3f &size) {
    Size = size;
}

const Pnt3f &ObjInfoPack::getFront() const {
    return Front;
}

void ObjInfoPack::setFront(const Pnt3f &front) {
    Front = front;
    Front.normalize();
}

const Pnt3f &ObjInfoPack::getTop() const {
    return Top;
}

void ObjInfoPack::setTop(const Pnt3f &top) {
    Top = top;
    Top.normalize();
}

//const Pnt3f &ObjInfoPack::getRotate() const {
//    return Rotate;
//}
//
//void ObjInfoPack::setRotate(const Pnt3f &rotate) {
//    Rotate = rotate;
//    Rotate.normalize();
//}

GLubyte *ObjInfoPack::getColor() const {
    return Color;
}

void ObjInfoPack::setColor(GLubyte *color) {
    Color = color;
}

static GLubyte BLACK[3] = {0,0,0};

ObjInfoPack::ObjInfoPack() {
    Pos = Pnt3f(0, 0, 0);
    Size = Pnt3f(1, 1, 1);
//    Rotate = Pnt3f(0, 0, 0);
    Top = Pnt3f(0, 1, 0);
    Front = Pnt3f(1, 0, 0);
    Color = BLACK;
}

ObjInfoPack::~ObjInfoPack() {
//    if(Color)   delete[] Color;
}
