//
// Created by IceLenf on 2022/10/28.
//

#ifndef ROLLERCOASTERS_OBJINFOPACK_H
#define ROLLERCOASTERS_OBJINFOPACK_H

#include <GL/GL.h>
#include "../Utilities/Pnt3f.H"

class ObjInfoPack {
    Pnt3f Pos, Size, Rotate;
    GLubyte *Color;
public:
    ObjInfoPack();

    ObjInfoPack(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color);

    virtual ~ObjInfoPack();

    const Pnt3f &getPos() const;

    void setPos(const Pnt3f &pos);

    const Pnt3f &getSize() const;

    void setSize(const Pnt3f &size);

    const Pnt3f &getRotate() const;

    void setRotate(const Pnt3f &rotate);

    GLubyte *getColor() const;

    void setColor(GLubyte *color);
};


#endif //ROLLERCOASTERS_OBJINFOPACK_H
