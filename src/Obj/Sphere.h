//
// Created by IceLenf on 2022/10/28.
//

#ifndef ROLLERCOASTERS_SPHERE_H
#define ROLLERCOASTERS_SPHERE_H

#include "Obj.h"

class Sphere : public Obj {

    void GLDraw() override;

public:
    

    Sphere(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color);
};


#endif //ROLLERCOASTERS_SPHERE_H
