//
// Created by IceLenf on 2022/11/8.
//

#ifndef ROLLERCOASTERS_CUBOIDANCHORBOTTOM_H
#define ROLLERCOASTERS_CUBOIDANCHORBOTTOM_H

#include "Obj.h"

class CuboidAnchorBottom : public Obj {
public:
    void init() override;

    CuboidAnchorBottom();

    explicit CuboidAnchorBottom(const ObjInfoPack &infoPack);

    CuboidAnchorBottom(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color);

protected:
    void GLDraw() override;
};


#endif //ROLLERCOASTERS_CUBOIDANCHORBOTTOM_H
