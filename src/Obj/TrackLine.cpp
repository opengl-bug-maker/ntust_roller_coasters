//
// Created by IceLenf on 2022/10/27.
//

#include "TrackLine.h"

void TrackLine::GLDraw() {

}

TrackLine::TrackLine():Obj() {
    trackLineWidth = 0;
}

TrackLine::TrackLine(GLubyte *color, const float &trackLineWidth):TrackLine() {
    setColor(color);
    this->trackLineWidth = trackLineWidth;
    init();
}

//TrackLine::TrackLine(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &rotate, GLubyte *color, const float&trackLineWidth) :
//Obj(pos, size, rotate,color),
//trackLineWidth(trackLineWidth) {
//    Children.push_back(new Cuboid(
//        Pnt3f(0, 0, 0),
//        Pnt3f(1 * trackLineWidth, 1, 1 * trackLineWidth),
//        Pnt3f(0, 0, 0),
//        color
//    ));
//}

void TrackLine::setTrackLineLength(const float &trackLineLength) {
    Children[0]->setSize(Pnt3f(Children[0]->getSize().x, trackLineLength, Children[0]->getSize().z));
}

TrackLine::TrackLine(const Pnt3f &pos, const Pnt3f &size, const Pnt3f &front, const Pnt3f &top, GLubyte *color,
                     float trackLineWidth) : Obj(pos, size, front, top, color), trackLineWidth(trackLineWidth) {
    init();
}

void TrackLine::init() {
    Obj::init();
    Children.push_back(new Cuboid(
        Pnt3f(0, 0, 0),
        Pnt3f(1 * trackLineWidth, 1, 1 * trackLineWidth),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        infoPack.getColor()
    ));
}
