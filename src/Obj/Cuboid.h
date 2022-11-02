//
// Created by IceLenf on 2022/10/28.
//

#ifndef ROLLERCOASTERS_CUBOID_H
#define ROLLERCOASTERS_CUBOID_H

#include "Obj.h"

class Cuboid : public Obj{

    void GLDraw() override;

public:
//    Cuboid(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color);

    Cuboid(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color);
};


#endif //ROLLERCOASTERS_CUBOID_H
