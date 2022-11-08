//
// Created by IceLenf on 2022/11/8.
//

#ifndef ROLLERCOASTERS_FLOOR_H
#define ROLLERCOASTERS_FLOOR_H

#include "Obj.h"

class Floor: public Obj{
public:
    std::vector<std::vector<float>> floorHeight;
    Floor();

public:
    void init() override;

protected:
    void GLDraw() override;
};


#endif //ROLLERCOASTERS_FLOOR_H
