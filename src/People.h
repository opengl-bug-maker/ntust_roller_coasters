
#ifndef ROLLERCOASTERS_PEOPLE_H
#define ROLLERCOASTERS_PEOPLE_H

#include "Obj/Obj.h"

class People : public Obj{
public:
    People();
    People(const Pnt3f &pos, const Pnt3f &front, const Pnt3f &top);
    void turn_hand(float degree);
private:
    void GLDraw() override {};
};
#endif //ROLLERCOASTERS_PEOPLE_H

