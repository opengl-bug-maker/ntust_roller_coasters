#include "wheels.h"
#include "Obj/Cuboid.h"
#include "Obj/Cylinder.h"
#include "Obj/Sphere.h"


void Wheel::GLDraw() {

}

Wheel::Wheel(const Pnt3f& pos, const Pnt3f& size, const Pnt3f& front, const Pnt3f& top, GLubyte* color):Obj(pos,
    size,
    front,
    top,
    color) {
    Children.push_back(new Cuboid(
        Pnt3f(0, 0, 0),
        Pnt3f(0.75, 3, 0.25),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 1),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 130, 20, 130 }
    ));
    Children.push_back(new Cylinder(
        Pnt3f(0, 0, 0),
        Pnt3f(1, 1,1),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        color
    ));

}

void Wheel::setWheels(float length) {
    //直徑 = 4
    float wheelLength = getSize().x * 2 * 3.1415926;
    float circleCount = length / wheelLength;
    float theta = circleCount * 2 * 3.1415926;
    setFront(Pnt3f(cos(-theta) , sin(-theta), 0));
}
