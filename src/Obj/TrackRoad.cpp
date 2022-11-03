//
// Created by IceLenf on 2022/11/3.
//

#include "TrackRoad.h"

void TrackRoad::GLDraw() {

}

TrackRoad::TrackRoad():Obj() {
    trackRoadWidth = 0;
}

TrackRoad::TrackRoad(GLubyte *color, const float &trackRoadWidth):TrackRoad() {
    setColor(color);
    this->trackRoadWidth = trackRoadWidth;
    init();
}

void TrackRoad::setTrackRoadLength(const float &trackRoadLength) {
    Children[0]->setSize(Pnt3f(Children[0]->getSize().x, Children[0]->getSize().y, trackRoadLength));
}

TrackRoad::TrackRoad(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color,
                     float trackLineWidth) : Obj(pos, size, front, top, color), trackRoadWidth(trackRoadWidth) {
    init();
}

void TrackRoad::init() {
    Obj::init();
    Children.push_back(new Cuboid(
        Pnt3f(0, 0, 0),
        Pnt3f(1 * trackRoadWidth, 0.8, 1),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        infoPack.getColor()
    ));
}
