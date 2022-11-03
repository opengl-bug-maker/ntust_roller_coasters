#include "Tunnel.h"
#include "Obj/Cuboid.h"
#include "Obj/Cylinder.h"
#include "Obj/Sphere.h"


void Tunnel::GLDraw() {
}
Tunnel::Tunnel(const Pnt3f& pos, float w, float h){
    const int tunnel_width = 2;
    Children.push_back(new Cuboid( //top
        Pnt3f(0, h-0.5, 0),
        Pnt3f(tunnel_width, 1, w + 2),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 145,132, 13}
    ));
    Children.push_back(new Cuboid( //left
        Pnt3f(0, (h-1)/2, (w+1)/2),
        Pnt3f(tunnel_width, h-1, 1),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 145,132, 13 }
    ));
    Children.push_back(new Cuboid( //right
        Pnt3f(0, (h - 1) / 2, -((w + 1) / 2)),
        Pnt3f(tunnel_width, h - 1, 1),
        //Pnt3f(0, 0, 90),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 145,132, 13 }
    ));
}
