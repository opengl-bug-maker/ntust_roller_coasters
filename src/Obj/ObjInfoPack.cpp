//
// Created by IceLenf on 2022/10/28.
//

#include "ObjInfoPack.h"

ObjInfoPack::ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color) : Pos(pos),
                                                                                                     Size(size),
                                                                                                     Rotate(rotate),
                                                                                                     Color(color) {
    Rotate.normalize();
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

const Pnt3f &ObjInfoPack::getRotate() const {
    return Rotate;
}

void ObjInfoPack::setRotate(const Pnt3f &rotate) {
    Rotate = rotate;
    Rotate.normalize();
}

GLubyte *ObjInfoPack::getColor() const {
    return Color;
}

void ObjInfoPack::setColor(GLubyte *color) {
    Color = color;
}

ObjInfoPack::ObjInfoPack() {
    Pos = Pnt3f(0, 0, 0);
    Size = Pnt3f(1, 1, 1);
    Rotate = Pnt3f(0, 0, 0);
    Color = new GLubyte[]{0, 0, 0};
}

ObjInfoPack::~ObjInfoPack() {
//    if(Color)   delete[] Color;
}
