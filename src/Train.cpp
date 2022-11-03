#include "Train.h"
#include "Obj/Cuboid.h"
#include "Obj/Cylinder.h"
#include "Obj/Sphere.h"
#include "wheels.h"
Train::Train() :Obj() {
    this->setSize(Pnt3f(6, 20, 6));

}

Train::Train(GLubyte* color){
//    this->setSize(Pnt3f(6, 20, 6));
    Children.push_back(new Cuboid( //車身
        Pnt3f( 0, 1, 0), //pos
        Pnt3f( 17, 6, 6), //size
//        Pnt3f(0, 0, 0), //rotation
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 233, 29, 45 }
    ));
    Children.push_back(new Cuboid( //駕駛艙
        Pnt3f( -4.5,7, 0), //pos
        Pnt3f(8, 6,  6), //size
//        Pnt3f(0, 0, 0), //rotation
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[] { 117, 206, 219 }
    ));
    Children.push_back(new Cuboid( //駕駛艙屋頂
        Pnt3f(-4.5 ,10.5, 0), //pos
        Pnt3f(10, 1, 7), //size
        //Pnt3f(0, 0, 0), //rotation
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 233, 29, 45 }
    ));
    Children.push_back(new Cylinder( //烟囪
        Pnt3f(5, 5, 0),
        Pnt3f(2, 4, 2),
        //Pnt3f(90, 0, 0),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{200, 200, 10}
    ));
//
    Children.push_back(new Wheel( //輪子1
        Pnt3f(5, -1, 3.25),
        Pnt3f(2, 0.5,  2),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, 1),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Wheel( //輪子2
        Pnt3f(-5, -0.5, 3.25),
        Pnt3f(3, 0.5, 3),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, 1),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Wheel( //輪子3
        Pnt3f(5, -1, -3.25),
        Pnt3f(2, 0.5, 2),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, -1),
        new GLubyte[]{ 200, 200, 10 }
    ));
    Children.push_back(new Wheel ( //輪子4
        Pnt3f(-5, -0.5, -3.25),
        Pnt3f(3, 0.5, 3),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 0, -1),
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


Car::Car() :Obj() { }

Car::Car(GLubyte* color){
    Children.push_back(new Cuboid( // Left wall
        Pnt3f( 0, 2.5, 2.5), //pos
        Pnt3f( 15, 7, 1), //size
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 0, 0, 0 }
    ));

    Children.push_back(new Cuboid( // Right wall
        Pnt3f( 0, 2.5, -2.5), //pos
        Pnt3f( 15, 7, 1), //size
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 0, 0, 0 }
    ));

    Children.push_back(new Cuboid( // Front wall
        Pnt3f( 8, 2.5, 0), //pos
        Pnt3f( 1, 7, 6), //size
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 0, 0, 0 }
    ));

    Children.push_back(new Cuboid( // Back wall
        Pnt3f( -8, 2.5, 0), //pos
        Pnt3f( 1, 7, 6), //size
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 0, 0, 0 }
    ));

    Children.push_back(new Cuboid( // Bottom
        Pnt3f( 0, -1.5, 0), //pos
        Pnt3f( 17, 1, 6), //size
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 0, 0, 0 }
    ));
}