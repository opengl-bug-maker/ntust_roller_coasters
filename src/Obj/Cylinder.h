#include "Obj.h"

class Cylinder : public Obj {

    void GLDraw() override;

public:
    Cylinder(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& rotate, GLubyte* color);
};