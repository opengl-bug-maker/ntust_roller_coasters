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

#include <GL/gl.h>
#include <FL/fl_ask.h>
#include <iostream>

//****************************************************************************
//
// * Constructor
//============================================================================
CTrack::
CTrack() : trainU(0)
//============================================================================
{
	resetPoints();
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
	points.push_back(ControlPoint(Pnt3f(50,5,0)));
	points.push_back(ControlPoint(Pnt3f(0,5,50)));
	points.push_back(ControlPoint(Pnt3f(-50,5,0)));
	points.push_back(ControlPoint(Pnt3f(0,5,-50)));

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
	while(*p) {
		// skip over leading whitespace - stop at the first character or end of string
		while (*p && *p<=' ') p++;

		// now we're pointing at the first thing after the spaces
		// make sure its not a comment, and that we're not at the end of the string
		// (that's actually the same thing)
		if (! (*p) || *p == '#')
		break;

		// so we're pointing at a word! add it to the word list
		words.push_back(p);

		// now find the end of the word
		while(*p > ' ') p++;	// stop at space or end of string

		// if its ethe end of the string, we're done
		if (! *p) break;

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
	FILE* fp = fopen(filename,"r");
	if (!fp) {
		fl_alert("Can't Open File!\n");
	} 
	else {
		char buf[512];

		// first line = number of points
		fgets(buf,512,fp);
		size_t npts = (size_t) atoi(buf);

		if( (npts<4) || (npts>65535)) {
			fl_alert("Illegal Number of Points Specified in File");
		} else {
			points.clear();
			// get lines until EOF or we have enough points
			while( (points.size() < npts) && fgets(buf,512,fp) ) {
				Pnt3f pos,orient;
				vector<const char*> words;
				breakString(buf,words);
				if (words.size() >= 3) {
					pos.x = (float) strtod(words[0],0);
					pos.y = (float) strtod(words[1],0);
					pos.z = (float) strtod(words[2],0);
				} else {
					pos.x=0;
					pos.y=0;
					pos.z=0;
				}
				if (words.size() >= 6) {
					orient.x = (float) strtod(words[3],0);
					orient.y = (float) strtod(words[4],0);
					orient.z = (float) strtod(words[5],0);
				} else {
					orient.x = 0;
					orient.y = 1;
					orient.z = 0;
				}
				orient.normalize();
				points.push_back(ControlPoint(pos,orient));
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
	FILE* fp = fopen(filename,"w");
	if (!fp) {
		fl_alert("Can't open file for writing");
	} else {
		fprintf(fp,"%d\n",points.size());
		for(size_t i=0; i<points.size(); ++i)
			fprintf(fp,"%g %g %g %g %g %g\n",
				points[i].pos.x, points[i].pos.y, points[i].pos.z, 
				points[i].orient.x, points[i].orient.y, points[i].orient.z);
		fclose(fp);
	}
}

void DrawCube(Pnt3f pos, Pnt3f size, Pnt3f dir){
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);

    float theta1 = -radiansToDegrees(atan2(dir.z,dir.x));
    glRotatef(theta1,0,1,0);
    float theta2 = -radiansToDegrees(acos(dir.y));
    glRotatef(theta2,0,0,1);
//region gl
    glBegin(GL_QUADS);
    glNormal3f( 0,0,1);
    glVertex3f( size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(-size.x,-size.y, size.z);
    glVertex3f( size.x,-size.y, size.z);

    glNormal3f( 0, 0, -1);
    glVertex3f( size.x, size.y, -size.z);
    glVertex3f( size.x,-size.y, -size.z);
    glVertex3f(-size.x,-size.y, -size.z);
    glVertex3f(-size.x, size.y, -size.z);

    glNormal3f( 0,1,0);
    glVertex3f( size.x,size.y, size.z);
    glVertex3f(-size.x,size.y, size.z);
    glVertex3f(-size.x,size.y,-size.z);
    glVertex3f( size.x,size.y,-size.z);


    glNormal3f( 0,-1,0);
    glVertex3f( size.x,-size.y, size.z);
    glVertex3f(-size.x,-size.y, size.z);
    glVertex3f(-size.x,-size.y,-size.z);
    glVertex3f( size.x,-size.y,-size.z);

    glNormal3f( 1,0,0);
    glVertex3f( size.x, size.y, size.z);
    glVertex3f( size.x,-size.y, size.z);
    glVertex3f( size.x,-size.y,-size.z);
    glVertex3f( size.x, size.y,-size.z);

    glNormal3f(-1,0,0);
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(-size.x, size.y,-size.z);
    glVertex3f(-size.x,-size.y,-size.z);
    glVertex3f(-size.x,-size.y, size.z);
    glEnd();
//endregion
    glPopMatrix();
}

void DrawCube(Pnt3f now, Pnt3f next, float cubeWidth){
    Pnt3f Pos = ( now + next ) * 0.5;
    Pnt3f Minus = now + next * -1;
    Pnt3f Size(cubeWidth, (Minus * 0.5).length() , cubeWidth);

    DrawCube(Pos, Size, Minus);
}

Pnt3f AverageTrackPoint(ControlPoint prev, ControlPoint now, ControlPoint next, float trackWidth){
    Pnt3f Line0 = now.orient * (now.pos + prev.pos * -1);
    Line0.normalize();
    Pnt3f Line1 = now.orient * (next.pos + now.pos * -1);
    Line1.normalize();
    Pnt3f Line = (Line0 + Line1) * 0.5;
    Line.normalize();
    return Line * trackWidth + now.pos;
}

void DrawTrackLine(ControlPoint prev, ControlPoint now, ControlPoint next, ControlPoint last, float trackWidth, float trackLineWidth){
    Pnt3f p0 = AverageTrackPoint(prev, now, next, trackWidth);
    Pnt3f p1 = AverageTrackPoint(now, next, last, trackWidth);
    DrawCube(p0, p1, trackLineWidth);
}

void CTrack::draw(bool doingShadows, bool arc) {

    virtualPoints = ComputeVirtualPoints();
    if(arc)
        virtualPoints = FixedArcPoints(virtualPoints, 3, 4);
//    std::cout << "======\n\n";
//    for(int i = 0; i < virtualPoints.size(); i++){
//        std::cout << virtualPoints[i].pos.x << " " << virtualPoints[i].pos.y << " " << virtualPoints[i].pos.z << "\n";
//        if(!doingShadows)
//            glColor3ub(20 + i * 4, 20 + i * 4, 20 + i * 4);
//        virtualPoints[i].draw();
//    }
    DrawTrack(virtualPoints, doingShadows);
    if(!doingShadows)
        glColor3ub(240, 60, 60);
//    for(int i = 0; i < virtualPoints.size(); i++){
//        if(!doingShadows)
//            glColor3ub(20 + i * 4, 20 + i * 4, 20 + i * 4);
//        virtualPoints[i].draw();
//    }




    //Track
    for(int i = 0; i < points.size(); i++){
        ControlPoint now = points[i];
        ControlPoint next = points[(i+1)%points.size()];
        Pnt3f Pos = (now.pos + next.pos) * 0.5;
        Pnt3f minus = (next.pos + now.pos * -1);
        Pnt3f Size(1, (minus * 0.5).length(), 1);

        DrawCube(Pos, Size, minus);
    }



    //Train
    Pnt3f trainBodySize(3, 10, 3);
    int nowPos = ((int)trainU) % virtualPoints.size(), nextPos = (nowPos + 1) % virtualPoints.size();
    float midPoint = trainU - nowPos;
    Pnt3f trainPos = virtualPoints[nowPos].pos * (1 - midPoint) + virtualPoints[nextPos].pos * midPoint;
    trainPos = trainPos + Pnt3f(0, 4, 0);

    Pnt3f TrainDir = (virtualPoints[nextPos].pos + virtualPoints[nowPos].pos * -1);
    DrawCube(trainPos, trainBodySize, TrainDir);


}

vector <ControlPoint> CTrack::ComputeVirtualPoints() {
    vector<ControlPoint> VirtualPoints;
    float checkPointCount = 20;
    for(int i = 0; i < points.size() * checkPointCount; i++){
        int now = i / checkPointCount,
            prev = now - 1 + points.size(),
            next = now + 1,
            last = now + 2;
        prev %= points.size();
        next %= points.size();
        last %= points.size();
        float mod = (1 - 1 / checkPointCount) - (i / checkPointCount - now);
        VirtualPoints.emplace_back((
                                       points[prev].pos * ( mod * mod * mod ) +
                                       points[now].pos * ( 1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod ) +
                                       points[next].pos * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
                                       points[last].pos * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f),

                                   (points[prev].orient * ( mod * mod * mod ) +
                                   points[now].orient * ( 1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod ) +
                                   points[next].orient * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
                                   points[last].orient * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f)

        );
    }
    return VirtualPoints;
}

vector<ControlPoint> CTrack::FixedArcPoints(const vector<ControlPoint> &vPoints, float minLength, float maxLength) {
    vector<ControlPoint> copy = vPoints;
    copy.push_back(copy[0]);
    vector<ControlPoint> arcPoints;
    vector<float> PointsLength = vector<float>(copy.size(), 0);
    for(int i = 1; i < copy.size(); i++){
        PointsLength[i] = PointsLength[i - 1] + (copy[i].pos + copy[i - 1].pos * -1).length();
    }
    int ArcPointCount = ( PointsLength[copy.size() - 1] / minLength + PointsLength[copy.size() - 1] / maxLength ) / 2;
    float ArcLength = PointsLength[copy.size() - 1] / ArcPointCount;

    int lastPos = 0;

    for(int i = 0; i < ArcPointCount; i++){
        float nowLength = ArcLength * i;
        while(nowLength >= PointsLength[lastPos]){
            lastPos++;
        }
        int prev = lastPos - 1;
        float minus = PointsLength[lastPos] - PointsLength[prev];
        arcPoints.emplace_back(
            copy[prev].pos * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].pos * ((nowLength - PointsLength[prev]) / minus),
            copy[prev].orient * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].orient * ((nowLength - PointsLength[prev]) / minus)
        );
    }

    return arcPoints;
}

void DrawTrackLine(const vector<ControlPoint>& trackPoints, float trackWidth, float trackLineWidth){
    for(int i = 0; i < trackPoints.size(); i++){
        ControlPoint prev = trackPoints[(i - 1 + trackPoints.size()) % trackPoints.size()];
        ControlPoint now = trackPoints[i];
        ControlPoint next = trackPoints[(i + 1) % trackPoints.size()];
        ControlPoint last = trackPoints[(i + 2) % trackPoints.size()];
        DrawTrackLine(prev, now, next, last, trackWidth, trackLineWidth);
        DrawTrackLine(last, next, now, prev, trackWidth, trackLineWidth);
    }
}

void DrawTrackRoad(const vector<ControlPoint>& trackPoints, float trackWidth, float trackLineWidth, float trackRoadWidth){
    for(int i = 0; i < trackPoints.size(); i++){
        ControlPoint prev = trackPoints[(i - 1 + trackPoints.size()) % trackPoints.size()];
        ControlPoint now = trackPoints[i];
        ControlPoint next = trackPoints[(i + 1) % trackPoints.size()];
        Pnt3f p0 = AverageTrackPoint(prev, now, next, trackWidth);
        Pnt3f p1 = AverageTrackPoint(next, now, prev, trackWidth);

        Pnt3f Pos = ( p0 + p1 ) * 0.5;
        Pnt3f Minus = p0 + p1 * -1;
        Pnt3f Size(trackLineWidth / 2, (Minus * 0.5).length() , trackRoadWidth);

        DrawCube(Pos, Size, Minus);
    }
}

void CTrack::DrawTrack(const vector<ControlPoint>& trackPoints, bool doingShadows) {
    float trackWidth = 3;
    float trackLineWidth = 0.4;
    float trackRoadWidth = 1;
    if(!doingShadows)
        glColor3ub(60, 240, 60);
    DrawTrackLine(trackPoints, trackWidth, trackLineWidth);
    if(!doingShadows)
        glColor3ub(60, 60, 240);
    DrawTrackRoad(trackPoints, trackWidth, trackLineWidth, trackRoadWidth);
}
