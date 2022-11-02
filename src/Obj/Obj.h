//
// Created by IceLenf on 2022/10/27.
//

#ifndef ROLLERCOASTERS_OBJ_H
#define ROLLERCOASTERS_OBJ_H

#include <vector>
#include <GL/GL.h>
#include <FL/fl_ask.H>
#include "../Utilities/Pnt3f.H"
#include "ObjInfoPack.h"

class Obj {
protected:
    ObjInfoPack infoPack;
//    Pnt3f Pos, Size, Rotate;
//    GLubyte *Color;
    std::vector<Obj*> Children;
public:
    Obj();

    explicit Obj(const ObjInfoPack &infoPack);

//    Obj(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color);

    Obj(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color);

    const Pnt3f &getPos() const;

    void setPos(const Pnt3f &pos);

    const Pnt3f &getSize() const;

    void setSize(const Pnt3f &size);

    const Pnt3f &getFront() const;

    void setFront(const Pnt3f &front);

    const Pnt3f &getTop() const;

    void setTop(const Pnt3f &top);

//    const Pnt3f &getRotate() const;
//
//    void setRotate(const Pnt3f &rotate);

    GLubyte *getColor() const;

    void setColor(GLubyte *color);

    void AddChild(Obj*);

    void Draw(bool doingShadows);

    virtual void init();

protected:
    virtual void GLDraw() = 0;
};


#endif //ROLLERCOASTERS_OBJ_H
