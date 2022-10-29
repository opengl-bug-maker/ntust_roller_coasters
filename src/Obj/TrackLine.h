//
// Created by IceLenf on 2022/10/27.
//

#ifndef ROLLERCOASTERS_TRACKLINE_H
#define ROLLERCOASTERS_TRACKLINE_H

#include "Obj.h"
#include "Cuboid.h"

class TrackLine : public Obj{
    float trackLineWidth;
public:
    TrackLine();

    TrackLine(GLubyte *color, const float &trackLineWidth);

    TrackLine(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color, const float &trackLineWidth);

    void setTrackLineLength(const float &trackLineLength);
private:
    void GLDraw() override;


};


#endif //ROLLERCOASTERS_TRACKLINE_H
