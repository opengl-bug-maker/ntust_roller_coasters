//
// Created by IceLenf on 2022/10/27.
//

#include "Obj.h"
#include "../Utilities/3DUtils.h"

void Obj::init() {

}

void Obj::Draw(bool doingShadows) {
    glPushMatrix();
//    glTranslatef(infoPack.getPos().x, infoPack.getPos().y, infoPack.getPos().z);
//    Pnt3f Side = (infoPack.getFront() * infoPack.getTop());
    Pnt3f Side = (infoPack.getTop() * infoPack.getFront());
    Side.normalize();
    Pnt3f Top = infoPack.getFront() * Side;
    Top.normalize();

//    GLfloat* rotate = new GLfloat []{
//        infoPack.getFront().x, infoPack.getFront().y, infoPack.getFront().z, 0,
//        Side.x, Side.y, Side.z, 0,
//        Top.x, Top.y, Top.z, 0,
//        0, 0, 0, 1};
//    GLfloat* rotate = new GLfloat []{
//        infoPack.getFront().x, infoPack.getFront().y, infoPack.getFront().z, 0,
//        Top.x, Top.y, Top.z, 0,
//        Side.x, Side.y, Side.z, 0,
//        0, 0, 0, 1};
//like
//    GLfloat* rotate = new GLfloat []{
//        Side.x, Side.y, Side.z, 0,
//        infoPack.getFront().x, infoPack.getFront().y, infoPack.getFront().z, 0,
//        Top.x, Top.y, Top.z, 0,
//        0, 0, 0, 1};
//    GLfloat* rotate = new GLfloat []{
//        Side.x, Side.y, Side.z, 0,
//        Top.x, Top.y, Top.z, 0,
//        infoPack.getFront().x, infoPack.getFront().y, infoPack.getFront().z, 0,
//        0, 0, 0, 1};
//    GLfloat* rotate = new GLfloat []{
//        Top.x, Top.y, Top.z, 0,
//        infoPack.getFront().x, infoPack.getFront().y, infoPack.getFront().z, 0,
//        Side.x, Side.y, Side.z, 0,
//        0, 0, 0, 1};
    GLfloat* rotate = new GLfloat []{
        Top.x, Top.y, Top.z, 0,
        Side.x, Side.y, Side.z, 0,
        -infoPack.getFront().x, -infoPack.getFront().y, -infoPack.getFront().z, 0,
        0, 0, 0, 1};





//    GLfloat* rotate = new GLfloat[]{  Top.x, infoPack.getFront().x, Side.x,0,
//                                      Top.y, infoPack.getFront().y,Side.y, 0,
//                                      Top.z, infoPack.getFront().z, Side.z,0,
//                                     0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, Top.x, infoPack.getFront().x, 0,
//                                     Side.y, Top.y, infoPack.getFront().y, 0,
//                                     Side.z, Top.z, infoPack.getFront().z, 0,
//                                     0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, infoPack.getFront().x, Top.x, 0,
//                                     Side.y, infoPack.getFront().y,Top.y,  0,
//                                     Side.z,  infoPack.getFront().z,Top.z, 0,
//                                     0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, infoPack.getFront().x, Top.x, 0,
//                                     Side.y, infoPack.getFront().y,Top.y,  0,
//                                     Side.z,  infoPack.getFront().z,Top.z, 0,
//                                     0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, infoPack.getFront().x, Top.x, 0,
//                                     Side.y, infoPack.getFront().y,Top.y,  0,
//                                     Side.z,  infoPack.getFront().z,Top.z, 0,
//                                     0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, infoPack.getFront().x, Top.x, 0,
//                                     Side.y, infoPack.getFront().y,Top.y,  0,
//                                     Side.z,  infoPack.getFront().z,Top.z, 0,
//                                     0,0,0, 1};

//    glMultMatrixf(rotate);
//    GLfloat* mat = new GLfloat[]{
//        Side.x, Side.y, Side.z, 0,
//        infoPack.getTop().x, infoPack.getTop().y, infoPack.getTop().z, 0,
//                                  -infoPack.getFront().x, -infoPack.getFront().y, -infoPack.getFront().z, 0,
//                                  infoPack.getPos().x, infoPack.getPos().y, infoPack.getPos().z, 1};
//    GLfloat* mat = new GLfloat[]{ -Side.x, -Side.y, -Side.z, infoPack.getSize().x,
//                                  -infoPack.getTop().x, -infoPack.getTop().y, -infoPack.getTop().z, infoPack.getSize().y,
//                                  -infoPack.getFront().x, -infoPack.getFront().y, -infoPack.getFront().z, infoPack.getSize().z,
//                                  infoPack.getPos().x, infoPack.getPos().y, infoPack.getPos().z, 1};
//    GLfloat* mat = new GLfloat[]{ 0, 0, 0, -infoPack.getPos().x,
//                                  0, 0, 0, -infoPack.getPos().y,
//                                  0, 0,0, -infoPack.getPos().z,
//                                  1,1,1, 1};
//    GLfloat* mat = new GLfloat[]{ 0, 0, 0, infoPack.getPos().x,
//                                  0, 0, 0, infoPack.getPos().y,
//                                  0, 0, 0, infoPack.getPos().z,
//                                  1,1,1, 1};
//    GLfloat* mat = new GLfloat[]{ 0, 0, 0, 1,
//                                  0, 0, 0, 1,
//                                  0, 0,0, 1,
//                                  -infoPack.getPos().x,-infoPack.getPos().y,-infoPack.getPos().z, 1};
    GLfloat* mat = new GLfloat[]{ 1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0,1, 0,
                                  infoPack.getPos().x,infoPack.getPos().y,infoPack.getPos().z, 1};
    glMultMatrixf(mat);
//    GLfloat* mat = new GLfloat[]{ Side.x, Top.x, infoPack.getFront().x, infoPack.getPos().x,
//                                  Side.y, Top.y, infoPack.getFront().y, infoPack.getPos().y,
//                                  Side.z, Top.z, infoPack.getFront().z, infoPack.getPos().z,
//                                  infoPack.getSize().x, infoPack.getSize().y, infoPack.getSize().z, 1};
//    GLfloat* mat = new GLfloat[]{ Side.x, infoPack.getTop().x, infoPack.getFront().x, infoPack.getSize().x,
//                                  Side.y, infoPack.getTop().y, infoPack.getFront().y, infoPack.getSize().y,
//                                  Side.z, infoPack.getTop().z, infoPack.getFront().z, infoPack.getSize().z,
//                                  infoPack.getPos().x, infoPack.getPos().y, infoPack.getPos().z, 1};
//    GLfloat* mat = new GLfloat[]{ Side.x, Top.x, infoPack.getFront().x, 0,
//                                  Side.y, Top.y, infoPack.getFront().y, 0,
//                                  Side.z, Top.z, infoPack.getFront().z, 0,
//                                  0,0,0, 1};
//    GLfloat* rotate = new GLfloat[]{ Side.x, Top.x, infoPack.getFront().x, 0,
//                                     Side.y, Top.y, infoPack.getFront().y, 0,
//                                     Side.z, Top.z, infoPack.getFront().z, 0,
//                                     0,0,0, 1};
//
    glMultMatrixf(rotate);


//    float theta1 = -radiansToDegrees(atan2(infoPack.getRotate().z,infoPack.getRotate().x));
//    glRotatef(theta1,0,1,0);
//    float theta2 = -radiansToDegrees(acos(infoPack.getRotate().y));
//    glRotatef(theta2,0,0,1);
    glScalef(infoPack.getSize().x, infoPack.getSize().y, infoPack.getSize().z);
    for(Obj* obj : Children){
        obj->Draw(doingShadows);
    }
    if(doingShadows){
        glColor4f(0, 0, 0, .5);
    }else{
        glColor3ubv(infoPack.getColor());
    }
    this->GLDraw(); //��ڵe�F��
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

//Obj::Obj(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color){
//    infoPack = ObjInfoPack(pos, size, rotate, color);
//}

Obj::Obj(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color) {
    infoPack = ObjInfoPack(pos, size, front, top, color);
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

//const Pnt3f &Obj::getRotate() const {
//    return infoPack.getRotate();
//}
//
//void Obj::setRotate(const Pnt3f &rotate) {
//    infoPack.setRotate(rotate);
//}

const Pnt3f &Obj::getFront() const {
    return infoPack.getFront();
}

void Obj::setFront(const Pnt3f &front) {
    infoPack.setFront(front);
}

const Pnt3f &Obj::getTop() const {
    return infoPack.getTop();
}

void Obj::setTop(const Pnt3f &top) {
    infoPack.setTop(top);
}

GLubyte *Obj::getColor() const {
    return infoPack.getColor();
}

void Obj::setColor(GLubyte *color) {
    infoPack.setColor(color);
}
