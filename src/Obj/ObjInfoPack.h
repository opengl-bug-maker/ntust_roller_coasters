//
// Created by IceLenf on 2022/10/28.
//

#ifndef ROLLERCOASTERS_OBJINFOPACK_H
#define ROLLERCOASTERS_OBJINFOPACK_H

#include <GL/GL.h>
#include "../Utilities/Pnt3f.H"

class ObjInfoPack {
    Pnt3f Pos, Size;
//    Pnt3f Rotate;
    Pnt3f Front, Top;
    GLubyte *Color;
public:
    ObjInfoPack();

//    ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color);

    ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color);

    virtual ~ObjInfoPack();

    const Pnt3f &getPos() const;

    void setPos(const Pnt3f &pos);

    const Pnt3f &getSize() const;

    void setSize(const Pnt3f &size);

//    const Pnt3f &getRotate() const;
//
//    void setRotate(const Pnt3f &rotate);

    const Pnt3f &getFront() const;

    void setFront(const Pnt3f &front);

    const Pnt3f &getTop() const;

    void setTop(const Pnt3f &top);

    GLubyte *getColor() const;

    void setColor(GLubyte *color);
};


#endif //ROLLERCOASTERS_OBJINFOPACK_H
