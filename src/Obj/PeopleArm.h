//
// Created by IceLenf on 2022/11/8.
//

#ifndef ROLLERCOASTERS_PEOPLEARM_H
#define ROLLERCOASTERS_PEOPLEARM_H

#include "Obj.h"

class PeopleArm : public Obj {
public:
    void init() override;

    PeopleArm();

    explicit PeopleArm(const ObjInfoPack &infoPack);

    PeopleArm(const Pnt3f &pos, const Pnt3f &front, const Pnt3f &top, GLubyte *color);

protected:
    void GLDraw() override;
};


#endif //ROLLERCOASTERS_PEOPLEARM_H
