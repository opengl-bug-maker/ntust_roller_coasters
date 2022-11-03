#include "Smoke.h"
#include "Obj/Cuboid.h"
#include "Obj/Cylinder.h"
#include "Obj/Sphere.h"
#include <time.h>       
float get_random_float() {
    int r = rand() % 2000;
    return (float)r / 1000-1;
}
Smoke::Smoke() :Obj() {
    srand(time(NULL));
    int count = 10;
    
    for (int i = 0; i < count; i++) {
        GLubyte color = (GLubyte)(90 + get_random_float() * 10);
        Children.push_back(new Sphere(
            Pnt3f(get_random_float() * 4, get_random_float() + 2, get_random_float() * 4),
            Pnt3f(0.6+0.1* get_random_float(), 0.7+0.1* get_random_float(), 0.6 + 0.1 * get_random_float()),
            Pnt3f(1, 0, 0),
            Pnt3f(0, 1, 0),
            new GLubyte[]{ color , color , color }
        ));
    }
}


void Smoke::GLDraw() {
}
