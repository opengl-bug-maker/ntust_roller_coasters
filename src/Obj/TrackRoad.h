//
// Created by IceLenf on 2022/11/3.
//

#ifndef ROLLERCOASTERS_TRACKROAD_H
#define ROLLERCOASTERS_TRACKROAD_H

#include "Obj.h"
#include "Cuboid.h"

class TrackRoad : public Obj{
    float trackRoadWidth;
public:
    void init() override;

    TrackRoad();

    TrackRoad(GLubyte *color, const float &trackRoadWidth);

    TrackRoad(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color,
              float trackLineWidth);

    void setTrackRoadLength(const float &trackRoadLength);
private:
    void GLDraw() override;


};


#endif //ROLLERCOASTERS_TRACKROAD_H
