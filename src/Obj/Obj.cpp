//
// Created by IceLenf on 2022/10/27.
//

#include "Obj.h"
#include "../Utilities/3DUtils.h"

void Obj::Draw(bool doingShadows) {
    glPushMatrix();
    glTranslatef(infoPack.getPos().x, infoPack.getPos().y, infoPack.getPos().z);
    float theta1 = -radiansToDegrees(atan2(infoPack.getRotate().z,infoPack.getRotate().x));
    glRotatef(theta1,0,1,0);
    float theta2 = -radiansToDegrees(acos(infoPack.getRotate().y));
    glRotatef(theta2,0,0,1);
    glScalef(infoPack.getSize().x, infoPack.getSize().y, infoPack.getSize().z);
    for(Obj* obj : Children){
        obj->Draw(doingShadows);
    }
    if(doingShadows){
        glColor4f(0, 0, 0, .5);
    }else{
        glColor3ubv(infoPack.getColor());
    }
    this->GLDraw(); //實際畫東西
    glPopMatrix();
}

Obj::Obj() {
//    Pos = Pnt3f(0, 0, 0);
//    Size = Pnt3f(1, 1, 1);
//    Rotate = Pnt3f(0, 0, 0);
//    Color = (GLubyte[3]){0, 0, 0};
//    Color = new GLubyte[]{0, 0, 0};
}

void Obj::AddChild(Obj *child) {
    Children.push_back(child);
}

Obj::Obj(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color){
    infoPack = ObjInfoPack(pos, size, rotate, color);
}

Obj::Obj(const ObjInfoPack &infoPack) : infoPack(infoPack) {}

const Pnt3f &Obj::getPos() const {
    return infoPack.getPos();
}

void Obj::setPos(const Pnt3f &pos) {
    infoPack.setPos(pos);
}

const Pnt3f &Obj::getSize() const {
    return infoPack.getSize();
}

void Obj::setSize(const Pnt3f &size) {
    infoPack.setSize(size);
}

const Pnt3f &Obj::getRotate() const {
    return infoPack.getRotate();
}

void Obj::setRotate(const Pnt3f &rotate) {
    infoPack.setRotate(rotate);
}

GLubyte *Obj::getColor() const {
    return infoPack.getColor();
}

void Obj::setColor(GLubyte *color) {
    infoPack.setColor(color);
}
