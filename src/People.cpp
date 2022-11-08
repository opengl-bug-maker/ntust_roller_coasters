#include "People.h"
#include "Obj/Cuboid.h"
#include "Obj/PeopleArm.h"

People::People() : Obj() {
    Obj::init();
}

void People::turn_hand(float degree) {
    Children[2]->setFront(Pnt3f(cos(degree/180 * 3.1415926),sin(degree/180 * 3.1415926), 0));
    Children[3]->setFront(Pnt3f(cos(degree/180 * 3.1415926),sin(degree/180 * 3.1415926), 0));
}

People::People(const Pnt3f &pos, const Pnt3f &front, const Pnt3f &top) {
    Obj::init();

    static GLubyte head_color[3] = { 247, 222, 213 };
    Children.push_back(new Cuboid( //head
        Pnt3f( -3.75, 9.25, 0),
        Pnt3f( 2.5, 2.5, 2.5),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        head_color
    ));

    static GLubyte body_color[3] = { 247, 222, 213 };
    Children.push_back(new Cuboid( //body
        Pnt3f( -3.75, 4, 0),
        Pnt3f( 1.5, 9, 3),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        body_color
    ));

    // Left arm
    static GLubyte arm_color[3] = { 247, 222, 213 };
    Children.push_back(new PeopleArm(
        Pnt3f( -3.75,7, -1.9),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, 1),
        arm_color
    ));

    // Right arm
    Children.push_back(new PeopleArm(
        Pnt3f( -3.75,7, 1.9),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, -1),
        arm_color
    ));

    // Left leg
    static GLubyte leg_color[3] = { 247, 222, 213 };
    Children.push_back(new Cuboid(
        Pnt3f(0.5 ,-0.25, -1),
        Pnt3f(7, 1.5, 1.25),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, 1),
        leg_color
    ));

    // Right leg
    Children.push_back(new Cuboid(
        Pnt3f(0.5 ,-0.25, 1),
        Pnt3f(7, 1.5, 1.25),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, -1),
        leg_color
    ));
}

