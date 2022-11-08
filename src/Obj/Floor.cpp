//
// Created by IceLenf on 2022/11/8.
//

#include "Floor.h"

void Floor::init() {
    Obj::init();
    floorHeight = std::vector<std::vector<float>>(40,std::vector<float>(40, 0.0));
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            floorHeight[i][j] = 80 * exp(-((i-20)*(i-20) + (j-20)*(j-20)) / 20.0f);
        }
    }
}

void Floor::GLDraw() {
    float floorColor1[3] = { .7f, .7f, .7f }; // Light color
    float floorColor2[3] = { .3f, .3f, .3f }; // Dark color
    for(int i = 0; i < 39; i++){
        glBegin(GL_TRIANGLE_STRIP);
        for(int j = 0; j < 40; j++){
//            glColor4fv(((i + j) & 1) ? floorColor1 : floorColor2);
            glColor4fv(floorColor1);
//            glNormal3f(0, 1, 0);
            if(j & 1){
                Pnt3f fir = Pnt3f(-100 + (i + 1) * 5, floorHeight[i + 1][j], -100 + j * 5) + Pnt3f(-100 + i * 5, floorHeight[i][j], -100 + j * 5) * -1;
                Pnt3f sec = Pnt3f(-100 + i * 5, floorHeight[i][j - 1], -100 + (j - 1) * 5) + Pnt3f(-100 + (i + 1) * 5, floorHeight[i + 1][j], -100 + j * 5) * -1;
                Pnt3f cross = fir * sec;
                cross.normalize();
                glNormal3f(cross.x, cross.y, cross.z);
            }else{
                Pnt3f fir = Pnt3f(-100 + (i + 1) * 5, floorHeight[i + 1][j], -100 + j * 5) + Pnt3f(-100 + i * 5, floorHeight[i][j], -100 + j * 5) * -1;
                Pnt3f sec = Pnt3f(-100 + i * 5, floorHeight[i][j + 1], -100 + (j + 1) * 5) + Pnt3f(-100 + (i + 1) * 5, floorHeight[i + 1][j], -100 + j * 5) * -1;
                Pnt3f cross = sec * fir;
                cross.normalize();
                glNormal3f(cross.x, cross.y, cross.z);
            }
            glVertex3f(-100 + i * 5, floorHeight[i][j], -100 + j * 5);
            glVertex3f(-100 + (i + 1) * 5, floorHeight[i + 1][j], -100 + j * 5);
        }
        glEnd();
    }
}

Floor::Floor() {
    init();
}
