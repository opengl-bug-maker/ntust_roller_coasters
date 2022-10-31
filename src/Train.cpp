#include "Train.h"
#include "Obj/Cuboid.h"
#include "Obj/Cylinder.h"
Train::Train() :Obj() {
    this->setSize(Pnt3f(6, 20, 6));

}

Train::Train(GLubyte* color){
    //this->setSize(Pnt3f(6, 20, 6));
    Children.push_back(new Cuboid( //車身
        Pnt3f(-1, 0, 0), //pos
        Pnt3f(6, 17, 6), //size
        Pnt3f(0, 0, 0), //rotation
        new GLubyte[]{ 233, 29, 45 }
    ));
    Children.push_back(new Cuboid( //駕駛艙
        Pnt3f(-7, -4.5, 0), //pos
        Pnt3f(6, 8, 6), //size
        Pnt3f(0, 0, 0), //rotation
        new GLubyte[] { 117, 206, 219 }
    ));
    Children.push_back(new Cuboid( //駕駛艙屋頂
        Pnt3f(-10.5, -4.5, 0), //pos
        Pnt3f(1, 10, 7), //size
        Pnt3f(0, 0, 0), //rotation
        new GLubyte[]{ 233, 29, 45 }
    )); 
    Children.push_back(new Cylinder( //烟囪
        Pnt3f(-5, 5, 0),
        Pnt3f(2, 4, 2),
        Pnt3f(90, 0, 0),
        new GLubyte[]{200, 200, 10}
    ));

    Children.push_back(new Cylinder( //輪子1
        Pnt3f(2, 5, 3.25),
        Pnt3f(2, 0.5,  2),
        Pnt3f(0, 0, 90),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Cylinder( //輪子2
        Pnt3f(1, -5, 3.25),
        Pnt3f(3, 0.5, 3),
        Pnt3f(0, 0, 90),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Cylinder( //輪子3
        Pnt3f(1, -5, -3.25),
        Pnt3f(3, 0.5, 3),
        Pnt3f(0, 0, 90),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Cylinder( //輪子4
        Pnt3f(2, 5, -3.25),
        Pnt3f(2, 0.5, 2),
        Pnt3f(0, 0, 90),
        new GLubyte[]{ 200, 200, 10 }
    ));
}

void Train::GLDraw(){
    //glBegin(GL_QUADS);
    //glNormal3f(0, 0, 1);
    //glVertex3f(0.5, 0.5, 0.5);
    //glVertex3f(-0.5, 0.5, 0.5);
    //glVertex3f(-0.5, -0.5, 0.5);
    //glVertex3f(0.5, -0.5, 0.5);

    //glNormal3f(0, 0, -1);
    //glVertex3f(0.5, 0.5, -0.5);
    //glVertex3f(0.5, -0.5, -0.5);
    //glVertex3f(-0.5, -0.5, -0.5);
    //glVertex3f(-0.5, 0.5, -0.5);

    //glNormal3f(0, 1, 0);
    //glVertex3f(0.5, 0.5, 0.5);
    //glVertex3f(-0.5, 0.5, 0.5);
    //glVertex3f(-0.5, 0.5, -0.5);
    //glVertex3f(0.5, 0.5, -0.5);


    //glNormal3f(0, -1, 0);
    //glVertex3f(0.5, -0.5, 0.5);
    //glVertex3f(-0.5, -0.5, 0.5);
    //glVertex3f(-0.5, -0.5, -0.5);
    //glVertex3f(0.5, -0.5, -0.5);

    //glNormal3f(1, 0, 0);
    //glVertex3f(0.5, 0.5, 0.5);
    //glVertex3f(0.5, -0.5, 0.5);
    //glVertex3f(0.5, -0.5, -0.5);
    //glVertex3f(0.5, 0.5, -0.5);

    //glNormal3f(-1, 0, 0);
    //glVertex3f(-0.5, 0.5, 0.5);
    //glVertex3f(-0.5, 0.5, -0.5);
    //glVertex3f(-0.5, -0.5, -0.5);
    //glVertex3f(-0.5, -0.5, 0.5);
    //glEnd();
}
