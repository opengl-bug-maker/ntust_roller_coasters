/************************************************************************
     File:        Track.cpp

     Author:
                  Michael Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu

     Comment:     Container for the "World"

                        This provides a container for all of the "stuff"
                        in the world.

                        It could have been all global variables, or it could
                        have just been
                        contained in the window. The advantage of doing it
                        this way is that
                        we might have multiple windows looking at the same
                        world. But, I don't	think we'll actually do that.

                        See the readme for commentary on code style

     Platform:    Visio Studio.Net 2003/2005

*************************************************************************/

#include "Track.H"
#include "Utilities/3dUtils.h"
#include "TrainWindow.H"

//****************************************************************************
//
// * Constructor
//============================================================================
CTrack::
CTrack() : trainU(0)
//============================================================================
{
    resetPoints();
    ComputePointsFunc[0] = &CTrack::LinearPoints;
    ComputePointsFunc[1] = &CTrack::CardinalPoints;
    ComputePointsFunc[2] = &CTrack::BspLinePoints;

    DrawTrackLineFunc[0] = &CTrack::DrawTrackLineTwoLine;
    DrawTrackLineFunc[1] = &CTrack::DrawTrackLineOneLine;

    DrawTrackRoadFunc[0] = &CTrack::DrawTrackRoadOneWood;
    DrawTrackRoadFunc[1] = &CTrack::DrawTrackRoadRoadWood;
}

//****************************************************************************
//
// * provide a default set of points
//============================================================================
void CTrack::
resetPoints()
//============================================================================
{

    points.clear();
    points.push_back(ControlPoint(Pnt3f(50, 5, 0)));
    points.push_back(ControlPoint(Pnt3f(0, 5, 50)));
    points.push_back(ControlPoint(Pnt3f(-50, 5, 0)));
    points.push_back(ControlPoint(Pnt3f(0, 5, -50)));

    // we had better put the train back at the start of the track...
    trainU = 0.0;
}

//****************************************************************************
//
// * Handy utility to break a string into a list of words
//============================================================================      
void breakString(char* str, std::vector<const char*>& words)
//============================================================================
{
    // start with no words
    words.clear();

    // scan through the string, starting at the beginning
    char* p = str;

    // stop when we hit the end of the string
    while (*p) {
        // skip over leading whitespace - stop at the first character or end of string
        while (*p && *p <= ' ') p++;

        // now we're pointing at the first thing after the spaces
        // make sure its not a comment, and that we're not at the end of the string
        // (that's actually the same thing)
        if (!(*p) || *p == '#')
            break;

        // so we're pointing at a word! add it to the word list
        words.push_back(p);

        // now find the end of the word
        while (*p > ' ') p++;	// stop at space or end of string

        // if its ethe end of the string, we're done
        if (!*p) break;

        // otherwise, turn this space into and end of string (to end the word)
        // and keep going
        *p = 0;
        p++;
    }
}

//****************************************************************************
//
// * The file format is simple
//   first line: an integer with the number of control points
//	  other lines: one line per control point
//   either 3 (X,Y,Z) numbers on the line, or 6 numbers (X,Y,Z, orientation)
//============================================================================
void CTrack::
readPoints(const char* filename)
//============================================================================
{
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fl_alert("Can't Open File!\n");
    }
    else {
        char buf[512];

        // first line = number of points
        fgets(buf, 512, fp);
        size_t npts = (size_t)atoi(buf);

        if ((npts < 4) || (npts > 65535)) {
            fl_alert("Illegal Number of Points Specified in File");
        }
        else {
            points.clear();
            // get lines until EOF or we have enough points
            while ((points.size() < npts) && fgets(buf, 512, fp)) {
                Pnt3f pos, orient;
                vector<const char*> words;
                breakString(buf, words);
                if (words.size() >= 3) {
                    pos.x = (float)strtod(words[0], 0);
                    pos.y = (float)strtod(words[1], 0);
                    pos.z = (float)strtod(words[2], 0);
                }
                else {
                    pos.x = 0;
                    pos.y = 0;
                    pos.z = 0;
                }
                if (words.size() >= 6) {
                    orient.x = (float)strtod(words[3], 0);
                    orient.y = (float)strtod(words[4], 0);
                    orient.z = (float)strtod(words[5], 0);
                }
                else {
                    orient.x = 0;
                    orient.y = 1;
                    orient.z = 0;
                }
                orient.normalize();
                points.push_back(ControlPoint(pos, orient));
            }
        }
        fclose(fp);
    }
    trainU = 0;
}

//****************************************************************************
//
// * write the control points to our simple format
//============================================================================
void CTrack::
writePoints(const char* filename)
//============================================================================
{
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fl_alert("Can't open file for writing");
    }
    else {
        fprintf(fp, "%d\n", points.size());
        for (size_t i = 0; i < points.size(); ++i)
            fprintf(fp, "%g %g %g %g %g %g\n",
                points[i].pos.x, points[i].pos.y, points[i].pos.z,
                points[i].orient.x, points[i].orient.y, points[i].orient.z);
        fclose(fp);
    }
}

void DrawCube(Pnt3f pos, Pnt3f size, Pnt3f dir) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    float theta1 = -radiansToDegrees(atan2(dir.z, dir.x));
    glRotatef(theta1, 0, 1, 0);
    float theta2 = -radiansToDegrees(acos(dir.y));
    glRotatef(theta2, 0, 0, 1);
    //region gl
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(-size.x, -size.y, size.z);
    glVertex3f(size.x, -size.y, size.z);

    glNormal3f(0, 0, -1);
    glVertex3f(size.x, size.y, -size.z);
    glVertex3f(size.x, -size.y, -size.z);
    glVertex3f(-size.x, -size.y, -size.z);
    glVertex3f(-size.x, size.y, -size.z);

    glNormal3f(0, 1, 0);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, -size.z);
    glVertex3f(size.x, size.y, -size.z);


    glNormal3f(0, -1, 0);
    glVertex3f(size.x, -size.y, size.z);
    glVertex3f(-size.x, -size.y, size.z);
    glVertex3f(-size.x, -size.y, -size.z);
    glVertex3f(size.x, -size.y, -size.z);

    glNormal3f(1, 0, 0);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(size.x, -size.y, size.z);
    glVertex3f(size.x, -size.y, -size.z);
    glVertex3f(size.x, size.y, -size.z);

    glNormal3f(-1, 0, 0);
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, -size.z);
    glVertex3f(-size.x, -size.y, -size.z);
    glVertex3f(-size.x, -size.y, size.z);
    glEnd();
    //endregion
    glPopMatrix();
}

void DrawCube(Pnt3f now, Pnt3f next, float cubeWidth) {
    Pnt3f Pos = (now + next) * 0.5;
    Pnt3f Minus = now + next * -1;
    Pnt3f Size(cubeWidth, (Minus * 0.5).length(), cubeWidth);

    DrawCube(Pos, Size, Minus);
}

//Pnt3f AverageTrackPoint(ControlPoint prev, ControlPoint now, ControlPoint next, float trackWidth){
//    Pnt3f Line0 = now.orient * (now.pos + prev.pos * -1);
//    Line0.normalize();
//    Pnt3f Line1 = now.orient * (next.pos + now.pos * -1);
//    Line1.normalize();
//    Pnt3f Line = (Line0 + Line1) * 0.5;
//    Line.normalize();
//    return Line * trackWidth + now.pos;
//}

//void DrawTrackLine(ControlPoint prev, ControlPoint now, ControlPoint next, ControlPoint last, float trackWidth, float trackLineWidth){
//    Pnt3f p0 = AverageTrackPoint(prev, now, next, trackWidth);
//    Pnt3f p1 = AverageTrackPoint(now, next, last, trackWidth);
//    DrawCube(p0, p1, trackLineWidth);
//}

void CTrack::draw(bool doingShadows, TrainWindow* tw) {
    t = tw;
    int ComputePointIndex = tw->splineBrowser->value() - 1;
    int DrawTrackLineIndex = tw->TrackLineBrowser->value() - 1;
    int DrawTrackRoadIndex = tw->TrackRoadBrowser->value() - 1;
    if(ComputePointIndex < 0) ComputePointIndex = 0;
    if(DrawTrackLineIndex < 0) DrawTrackLineIndex = 0;
    if(DrawTrackRoadIndex < 0) DrawTrackRoadIndex = 0;

    bool arcLengthVersion = tw->arcLength->value();

    int checkPointsCount = tw->checkPointsCount->value();
    float arcMinLength = 0.1, arcMaxLength = 0.2;
    //    float arcMinLength = 3, arcMaxLength = 4;
    float trackWidth = tw->trackWidth->value();
    float trackLineWidth = tw->trackLineWidth->value();
    float trackRoadWidth = tw->trackRoadWidth->value();

    float tension = tw->tension->value();

    GLubyte TrackLineColor[3] = { 60, 240, 60 };
    GLubyte TrackRoadColor[3] = { 60, 240, 60 };
    GLubyte TrainColor[3] = { 240, 60, 60 };

    TrackLine trackLine = TrackLine(TrackLineColor, trackLineWidth);
    TrackRoad trackRoad = TrackRoad(TrackRoadColor, trackRoadWidth);

    int CarsCount = 3;


    virtualPoints = (this->*ComputePointsFunc[ComputePointIndex])(checkPointsCount, tension);
    if (arcLengthVersion)
        virtualPoints = FixedArcPoints(virtualPoints, arcMinLength, arcMaxLength);
    //    std::cout << "======\n\n";
    //    for(int i = 0; i < virtualPoints.size(); i++){
    //        std::cout << virtualPoints[i].pos.x << " " << virtualPoints[i].pos.y << " " << virtualPoints[i].pos.z << "\n";
    //        if(!doingShadows)
    //            glColor3ub(20 + i * 4, 20 + i * 4, 20 + i * 4);
    //        virtualPoints[i].draw();
    //    }

    //    if(!doingShadows)
    (this->*DrawTrackLineFunc[DrawTrackLineIndex])(virtualPoints, doingShadows, trackLine, trackWidth);
    //    if(!doingShadows)
    (this->*DrawTrackRoadFunc[DrawTrackRoadIndex])(virtualPoints, doingShadows, trackRoad, trackWidth);

    //    DrawTrack(virtualPoints, doingShadows, trackWidth, trackLineWidth, trackRoadWidth, TrackLineColor, TrackRoadColor);

    //    for(int i = 0; i < virtualPoints.size(); i++){
    //        if(!doingShadows)
    //            glColor3ub(20 + i * 4, 20 + i * 4, 20 + i * 4);
    //        virtualPoints[i].draw();
    //    }





//    if (!doingShadows)
//        glColor3ubv(TrainColor);

    //Train
    ObjInfoPack TrainInfoPack = GetTrainInfoPack(trainU);
    train.setPos(TrainInfoPack.getPos());
    train.setFront(TrainInfoPack.getFront());
    train.setTop(TrainInfoPack.getTop());
    train.setWheels(trainU * TotalArcLength / virtualPoints.size());
    //todo : train orient
    // 
    // Smoke 
//    Smoke smoke;
//    int nowPos = ((int)trainU) % virtualPoints.size(), nextPos = (nowPos + 1) % virtualPoints.size();
//    float midPoint = trainU - nowPos;
//    Pnt3f TrainDir = (virtualPoints[nextPos].pos + virtualPoints[nowPos].pos * -1);
//    smoke.setPos((virtualPoints[nowPos].pos * (1 - midPoint) + virtualPoints[nextPos].pos * midPoint) + virtualPoints[nowPos].orient * 16 + TrainDir * 2);
//    smoke.Draw(doingShadows);


    float smokeDis = trainU;
    if(smokes.empty()){
        smokeDis += 9999;
    }else{
        smokeDis -= smokes.back().getStartTick();
    }
    if(smokeDis < 0) smokeDis += virtualPoints.size();
    if(smokes.empty() || smokeDis > (10.0 / ArcLength)){
//        int i = 0;
        if(!doingShadows)
        smokes.push_back(Smoke(trainU));
        int _nowPos = ((int)trainU) % virtualPoints.size(), _nextPos = (_nowPos + 1) % virtualPoints.size();
        float _midPoint = trainU - _nowPos;
        Pnt3f TrainDir = (virtualPoints[_nextPos].pos + virtualPoints[_nowPos].pos * -1);
        smokes[smokes.size() - 1].setPos((virtualPoints[_nowPos].pos * (1 - _midPoint) + virtualPoints[_nextPos].pos * _midPoint) + virtualPoints[_nowPos].orient * 16 + TrainDir * 2);
    }
    for(auto smoke : smokes){
        smoke.setSize(smoke.getSize() * 0.9);
        smoke.Draw(doingShadows);
    }
    for(int i = smokes.size() - 1; i >= 0; i--){
        smokes[i].setSize(smokes[i].getSize() * 0.95);
        smokes[i].setPos(smokes[i].getPos() + Pnt3f(0, 0.3, 0));
        smokes[i].Draw(doingShadows);
        if(smokes[i].getSize().length() < 0.001) smokes.erase(smokes.begin() + i);
    }

    SupportStructure support = SupportStructure(
        Pnt3f(0, 0, 0),
        Pnt3f(1, 1, 1),
        Pnt3f(1, 0, 0),
        Pnt3f(0, 1, 0),
        new GLubyte[]{ 255,255,255 }
    );
    // Support
    for (int i = 0; i < points.size(); i++) {
        Pnt3f d = points[i].pos + Pnt3f(0, -2, 0);
        support.setPos(Pnt3f(d.x, d.y * 0.5, d.z));
        support.setSize(Pnt3f(1, d.y, 1));
        support.Draw(doingShadows);
    }



    //train.setColor(new GLubyte[]{ 255, 0, 100 });
    //DrawCube(trainPos, trainBodySize, TrainDir);
    if(!tw->trainCam->value())
        train.Draw(doingShadows);

    if(tw->arcLength->value()){
//    Cars
        Car car = Car(new GLubyte[]{ 233, 29, 45 });
        float trainu = trainU;
        for(int i = 0; i < CarsCount; i++){
            trainu -= 18 / ArcLength;
            while(trainu < 0){
                trainu += virtualPoints.size();
            }
            ObjInfoPack carInfoPack = GetTrainInfoPack(trainu);
            car.setPos(carInfoPack.getPos());
            car.setFront(carInfoPack.getFront());
            car.setTop(carInfoPack.getTop());
            car.setWheels(trainU * TotalArcLength / virtualPoints.size());
            car.Draw(doingShadows);
        }
    }

    //tunnel
    int step = t->checkPointsCount->value() / 5;
    if(t->arcLength->value()) step = (int)(1.0f / ArcLength);
    for (int i = 0; i < virtualPoints.size() / 5; i += step) {
        ControlPoint fir = virtualPoints[i];
        ControlPoint sec = virtualPoints[(i + 1) % virtualPoints.size()];

        Tunnel tunnel = Tunnel(fir.pos, trackWidth * 2, 20);
        tunnel.setPos(fir.pos);
        tunnel.setFront((sec.pos + fir.pos * -1));
        tunnel.setTop(fir.orient);
        tunnel.Draw(doingShadows);
    }
}

//vector <ControlPoint> CTrack::ComputeVirtualPoints() {
//    vector<ControlPoint> VirtualPoints;
//    float checkPointCount = 20;
//    for(int i = 0; i < points.size() * checkPointCount; i++){
//        int now = i / checkPointCount,
//            prev = now - 1 + points.size(),
//            next = now + 1,
//            last = now + 2;
//        prev %= points.size();
//        next %= points.size();
//        last %= points.size();
//        float mod = (1 - 1 / checkPointCount) - (i / checkPointCount - now);
//        VirtualPoints.emplace_back((
//                                       points[prev].pos * ( mod * mod * mod ) +
//                                       points[now].pos * ( 1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod ) +
//                                       points[next].pos * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
//                                       points[last].pos * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f),
//
//                                   (points[prev].orient * ( mod * mod * mod ) +
//                                   points[now].orient * ( 1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod ) +
//                                   points[next].orient * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
//                                   points[last].orient * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f)
//
//        );
//    }
//    return VirtualPoints;
//}

vector<ControlPoint> CTrack::LinearPoints(int checkPointsCount, float data = NULL) {
    vector<ControlPoint> VirtualPoints;
    for (int i = 0; i < points.size() * checkPointsCount; i++) {
        int now = i / checkPointsCount,
            next = (now + 1) % points.size();
        float mod = i - now * checkPointsCount;
        VirtualPoints.emplace_back(
            (points[now].pos * (checkPointsCount - mod) +
                points[next].pos * (mod)) * (1.0f / checkPointsCount),

            (points[now].orient * (checkPointsCount - mod) +
                points[next].orient * (mod)) * (1.0f / checkPointsCount)

        );
    }
    return VirtualPoints;
}

vector<ControlPoint> CTrack::CardinalPoints(int checkPointsCount, float data) {
    vector<ControlPoint> VirtualPoints;
    float tension = data;
    for (int i = 0; i < points.size() * checkPointsCount; i++) {
        int now = i / checkPointsCount,
            prev = now - 1 + points.size(),
            next = now + 1,
            last = now + 2;
        prev %= points.size();
        next %= points.size();
        last %= points.size();
        float mod = (i / (float)checkPointsCount - now);
        float mod2 = mod * mod;
        float mod3 = mod2 * mod;



        VirtualPoints.emplace_back(
            (points[prev].pos * tension * (-mod + 2 * mod2 - mod3) +
                points[now].pos * (1 + (tension - 3) * mod2 + (2 - tension) * mod3) +
                points[next].pos * (tension * mod + (3 - 2 * tension) * mod2 + (tension - 2) * mod3) +
                points[last].pos * (-tension * mod2 + tension * mod3)),

            (points[prev].orient * tension * (-mod + 2 * mod2 - mod3) +
                points[now].orient * (1 + (tension - 3) * mod2 + (2 - tension) * mod3) +
                points[next].orient * (tension * mod + (3 - 2 * tension) * mod2 + (tension - 2) * mod3) +
                points[last].orient * (-tension * mod2 + tension * mod3))

        );
    }
    return VirtualPoints;
}

vector<ControlPoint> CTrack::BspLinePoints(int checkPointsCount, float data = NULL) {
    vector<ControlPoint> VirtualPoints;
    //    float checkPointCount = 20;
    for (int i = 0; i < points.size() * checkPointsCount; i++) {
        int now = i / checkPointsCount,
            prev = now - 1 + points.size(),
            next = now + 1,
            last = now + 2;
        prev %= points.size();
        next %= points.size();
        last %= points.size();
        float mod = (1 - 1.0f / checkPointsCount) - (i / (float)checkPointsCount - now);
        VirtualPoints.emplace_back((
            points[prev].pos * (mod * mod * mod) +
            points[now].pos * (1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod) +
            points[next].pos * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
            points[last].pos * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f),

            (points[prev].orient * (mod * mod * mod) +
                points[now].orient * (1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod) +
                points[next].orient * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
                points[last].orient * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f)

        );
    }
    return VirtualPoints;
}

vector<ControlPoint> CTrack::FixedArcPoints(const vector<ControlPoint>& vPoints, float minLength, float maxLength) {
    vector<ControlPoint> copy = vPoints;
    copy.push_back(copy[0]);
    vector<ControlPoint> arcPoints;
    vector<float> PointsLength = vector<float>(copy.size(), 0);
    for (int i = 1; i < copy.size(); i++) {
        PointsLength[i] = PointsLength[i - 1] + (copy[i].pos + copy[i - 1].pos * -1).length();
    }
    int ArcPointCount = (PointsLength[copy.size() - 1] / minLength + PointsLength[copy.size() - 1] / maxLength) / 2;
    ArcLength = PointsLength[copy.size() - 1] / ArcPointCount;
    TotalArcLength = PointsLength[copy.size() - 1];

    int lastPos = 0;

    for (int i = 0; i < ArcPointCount; i++) {
        float nowLength = ArcLength * i;
        while (nowLength >= PointsLength[lastPos]) {
            lastPos++;
        }
        int prev = lastPos - 1;
        float minus = PointsLength[lastPos] - PointsLength[prev];
        arcPoints.emplace_back(
            copy[prev].pos * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].pos * ((nowLength - PointsLength[prev]) / minus),
            copy[prev].orient * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].orient * ((nowLength - PointsLength[prev]) / minus)
        );
    }
    physicsPoints(arcPoints);
    return arcPoints;
}

vector<ControlPoint> CTrack::physicsPoints(const vector<ControlPoint> &vPoints) {
    ControlPoint HighestPoint = vPoints[0].pos;
    float min = Gravity.dot(vPoints[0].pos);
    for (const ControlPoint& p : vPoints) {
        float f = Gravity.dot(p.pos);
        if(f < min){
            min = f;
            HighestPoint = p;
        }
    }
    maxHeight = -min / Gravity.length();

    return vector<ControlPoint>();
}

//void DrawTrackLine(const vector<ControlPoint>& trackPoints, float trackWidth, float trackLineWidth){
//    for(int i = 0; i < trackPoints.size(); i++){
//        ControlPoint prev = trackPoints[(i - 1 + trackPoints.size()) % trackPoints.size()];
//        ControlPoint now = trackPoints[i];
//        ControlPoint next = trackPoints[(i + 1) % trackPoints.size()];
//        ControlPoint last = trackPoints[(i + 2) % trackPoints.size()];
//        DrawTrackLine(prev, now, next, last, trackWidth, trackLineWidth);
//        DrawTrackLine(last, next, now, prev, trackWidth, trackLineWidth);
//    }
//}

//void DrawTrackRoad(const vector<ControlPoint>& trackPoints, float trackWidth, float trackLineWidth, float trackRoadWidth){
//    for(int i = 0; i < trackPoints.size(); i++){
//        ControlPoint prev = trackPoints[(i - 1 + trackPoints.size()) % trackPoints.size()];
//        ControlPoint now = trackPoints[i];
//        ControlPoint next = trackPoints[(i + 1) % trackPoints.size()];
//        Pnt3f p0 = AverageTrackPoint(prev, now, next, trackWidth);
//        Pnt3f p1 = AverageTrackPoint(next, now, prev, trackWidth);
//
//        Pnt3f Pos = ( p0 + p1 ) * 0.5;
//        Pnt3f Minus = p0 + p1 * -1;
//        Pnt3f Size(trackLineWidth / 2, (Minus * 0.5).length() , trackRoadWidth);
//
//        DrawCube(Pos, Size, Minus);
//    }
//}

//void CTrack::DrawTrack(const vector<ControlPoint>& trackPoints, bool doingShadows, float trackWidth, float trackLineWidth, float trackRoadWidth, GLubyte* trackLineColor, GLubyte* trackRoadColor) {
////    float trackWidth = 3;
////    float trackLineWidth = 0.4;
////    float trackRoadWidth = 1;
//    if(!doingShadows)
////        glColor3ub(60, 240, 60);
//        glColor3ubv(trackLineColor);
//    DrawTrackLine(trackPoints, trackWidth, trackLineWidth);
//    if(!doingShadows)
////        glColor3ub(60, 60, 240);
//        glColor3ubv(trackRoadColor);
//    DrawTrackRoad(trackPoints, trackWidth, trackLineWidth, trackRoadWidth);
//}

void CTrack::DrawTrackLineTwoLine(const vector<ControlPoint>& trackPoints, const bool& doingShadows, TrackLine& trackLine, const float& trackWidth) {
    for (int i = 0; i < trackPoints.size(); i++) {
        ControlPoint fir = trackPoints[i];
        ControlPoint sec = trackPoints[(i + 1) % trackPoints.size()];
        ControlPoint trd = trackPoints[(i + 2) % trackPoints.size()];

        ObjInfoPack pack0 = TrackTwoLine(fir, sec, trd, trackWidth);
        trackLine.setPos(pack0.getPos());
        trackLine.setTrackLineLength(pack0.getSize().y);
        //        trackLine.setRotate(pack0.getRotate());
        trackLine.setTop(pack0.getTop());
        trackLine.setFront(pack0.getFront());
        trackLine.Draw(doingShadows);

        ObjInfoPack pack1 = TrackTwoLine(trd, sec, fir, trackWidth);
        trackLine.setPos(pack1.getPos());
        trackLine.setTrackLineLength(pack1.getSize().y);
        //        trackLine.setRotate(pack1.getRotate());
        trackLine.setTop(pack1.getTop());
        trackLine.setFront(pack1.getFront());
        trackLine.Draw(doingShadows);
    }
}

ObjInfoPack CTrack::TrackTwoLine(const ControlPoint& fir, const ControlPoint& sec, const ControlPoint& trd, const float& trackWidth) {
    ControlPoint mid0 = ControlPoint(
        (fir.pos + sec.pos) * 0.5,
        (fir.orient + sec.orient) * 0.5
    );
    ControlPoint mid1 = ControlPoint(
        (sec.pos + trd.pos) * 0.5,
        (sec.orient + trd.orient) * 0.5
    );

    Pnt3f out0 = (mid0.orient * (sec.pos + fir.pos * -1));
    out0.normalize();
    out0 = mid0.pos + out0 * trackWidth;
    Pnt3f out1 = (mid1.orient * (trd.pos + sec.pos * -1));
    out1.normalize();
    out1 = mid1.pos + out1 * trackWidth;

    return ObjInfoPack(
        (out0 + out1) * 0.5,
        Pnt3f(1, (out1 + out0 * -1).length(), 1),
        (out1 + out0 * -1),
        mid0.orient,
        //        Pnt3f(mid0.orient + mid1.orient) * 0.5,
        new GLubyte[]{ 0, 0, 0 }
    );
}

void CTrack::DrawTrackRoadOneWood(const vector<ControlPoint>& trackPoints, const bool& doingShadows, TrackRoad& trackRoad, const float& trackWidth) {
    int step = t->checkPointsCount->value() / 5;
    if(t->arcLength->value()) step = (int)(10.0f / ArcLength);
    for (int i = 0; i < trackPoints.size(); i += step) {
        ControlPoint fir = trackPoints[i];
        ControlPoint sec = trackPoints[(i + 1) % trackPoints.size()];

        trackRoad.setPos(fir.pos);
        trackRoad.setTrackRoadLength(trackWidth * 2);
        trackRoad.setFront((sec.pos + fir.pos * -1));
        trackRoad.setTop(fir.orient);
        trackRoad.Draw(doingShadows);
    }
}

float CTrack::getArcV() const{
    return 10.0f / ArcLength;
}

float CTrack::getPhysicsV(float trainU) const {
    int nowPos = ((int)trainU) % virtualPoints.size(), nextPos = (nowPos + 1) % virtualPoints.size();
    float midPoint = trainU - nowPos;
    Pnt3f trainPos = virtualPoints[nowPos].pos * (1 - midPoint) + virtualPoints[nextPos].pos * midPoint;
    float H = maxHeight + trainPos.dot(Gravity) / Gravity.length();
    float V = sqrt(2 * Gravity.length() * H);
    return getArcV() + V / ArcLength;
}

ObjInfoPack CTrack::GetTrainInfoPack(float trainU) const {
    int nowPos = ((int)trainU) % virtualPoints.size(), nextPos = (nowPos + 1) % virtualPoints.size();
    float midPoint = trainU - nowPos;
    Pnt3f trainPos = virtualPoints[nowPos].pos * (1 - midPoint) + virtualPoints[nextPos].pos * midPoint;
    trainPos = trainPos + virtualPoints[nowPos].orient * 4;
    Pnt3f TrainDir = (virtualPoints[nextPos].pos + virtualPoints[nowPos].pos * -1);
    TrainDir.normalize();
    return ObjInfoPack(
        trainPos,
        Pnt3f(),
        TrainDir,
        virtualPoints[nowPos].orient,
        new GLubyte[]{0,0,0}
    );
}

void CTrack::DrawTrackLineOneLine(const vector<ControlPoint> &trackPoints, const bool &doingShadows, TrackLine &trackLine,
                             const float &trackWidth) {
    glBegin(GL_LINE_LOOP);
    if(doingShadows){
        glColor4f(0, 0, 0, 0.5f);
    }else{
        glColor3ubv(trackLine.getColor());
    }
    for(auto point : trackPoints){
        glVertex3f(point.pos.x, point.pos.y, point.pos.z);
    }
    glEnd();

}

void
CTrack::DrawTrackRoadRoadWood(const vector<ControlPoint> &trackPoints, const bool &doingShadows, TrackRoad &trackRoad,
                              const float &trackWidth) {
    glBegin(GL_QUAD_STRIP);
    if(doingShadows){
        glColor4f(0, 0, 0, 0.5f);
    }else{
        glColor3ubv(trackRoad.getColor());
    }
    for(int i = 0; i < trackPoints.size(); i++){
        ControlPoint fir = trackPoints[i];
        ControlPoint sec = trackPoints[(i + 1) % trackPoints.size()];
        Pnt3f Cross = (sec.pos + fir.pos * -1) * fir.orient;
        Cross.normalize();
        Pnt3f f = fir.pos + Cross * trackWidth;
        Pnt3f ff = fir.pos + Cross * -trackWidth;
        glVertex3f(f.x, f.y, f.z);
        glVertex3f(ff.x, ff.y, ff.z);
    }
    glEnd();
}
