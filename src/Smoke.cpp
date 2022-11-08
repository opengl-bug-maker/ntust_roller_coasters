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
    init();
}


void Smoke::GLDraw() {
}

Smoke::Smoke(float startTick) : Obj(), startTick(startTick) {
    init();
}

float Smoke::getStartTick() const {
    return startTick;
}

void Smoke::init() {
    Obj::init();
    srand(time(NULL));
    int count = 50;

    for (int i = 0; i < count; i++) {
        GLubyte color = (GLubyte)(90 + get_random_float() * 10);
        GLubyte colors[] = { color , color , color };
        Children.push_back(new Cuboid(
            Pnt3f(get_random_float() * 4, get_random_float() + 2, get_random_float() * 4),
            Pnt3f(0.6+0.1* get_random_float(), 0.7+0.1* get_random_float(), 0.6 + 0.1 * get_random_float()),
            Pnt3f(1, 0, 0),
            Pnt3f(0, 1, 0),
            colors
        ));
    }
}
