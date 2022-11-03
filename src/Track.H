/************************************************************************
     File:        Track.H

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
#pragma once

class TrainWindow;

#include <vector>
#include <GL/GL.h>
#include <FL/fl_ask.H>
#include <iostream>

using std::vector; // avoid having to say std::vector all of the time

// make use of other data structures from this project
#include "ControlPoint.H"
#include "Obj/Obj.h"
#include "Obj/Cuboid.h"
#include "Obj/TrackLine.h"
#include "Obj/TrackRoad.h"
#include "Obj/ObjInfoPack.h"
#include "SupportStructure.h"
#include "Tunnel.h"
#include "Train.h"

class CTrack {
	public:		
		// Constructor
		CTrack();

	public:
		// when we want to clear the control points, we really "reset" them 
		// to have 4 default positions (since we should never have fewer
		// than 4 points)
		void resetPoints();


		// read and write to files
		void readPoints(const char* filename);
		void writePoints(const char* filename);

        void draw(bool doingShadows, TrainWindow* tw);

        //
        vector<ControlPoint> (CTrack::*ComputePointsFunc[3])(int, float);

//        vector<ControlPoint> ComputeVirtualPoints();
        vector<ControlPoint> CardinalPoints(int checkPointsCount, float data);
        vector<ControlPoint> LinearPoints(int checkPointsCount, float data);
        vector<ControlPoint> BspLinePoints(int checkPointsCount, float data);
        //

        vector<ControlPoint> FixedArcPoints(const vector<ControlPoint>& vPoints, float minLength, float maxLength);

        //

        /// need Arc Points
        vector<ControlPoint> physicsPoints(const vector<ControlPoint>& vPoints);

        //
//        void DrawTrack(const vector<ControlPoint>& trackPoints, bool doingShadows, float trackWidth, float trackLineWidth, float trackRoadWidth, GLubyte* trackLineColor, GLubyte* trackRoadColor);

        void (CTrack::*DrawTrackLineFunc[3])(const vector<ControlPoint>&, const bool&, TrackLine&, const float&);
        void DrawTrackLineTwoLine(const vector<ControlPoint>& trackPoints, const bool& doingShadows, TrackLine& trackLine,const float& trackWidth);
        ObjInfoPack TrackTwoLine(const ControlPoint& fir, const ControlPoint& sec, const ControlPoint& trd, const float& trackWidth);

        void (CTrack::*DrawTrackRoadFunc[3])(const vector<ControlPoint>&, const bool&, TrackRoad&,const float&);
        void DrawTrackRoadOneWood(const vector<ControlPoint>& trackPoints, const bool& doingShadows, TrackRoad& trackRoad,const float& trackWidth);
        //
	public:
		// rather than have generic objects, we make a special case for these few
		// objects that we know that all implementations are going to need and that
		// we're going to have to handle specially
		vector<ControlPoint> points;
        vector<ControlPoint> virtualPoints;

		//###################################################################
		// TODO: you might want to do this differently
		//###################################################################
		// the state of the train - basically, all I need to remember is where
		// it is in parameter space
		float trainU;
        Pnt3f Gravity = Pnt3f(0, -10, 0);
        float ArcLength = 1;
        float TotalArcLength = 1;
        float maxHeight = 1;
        float getArcV() const;
        float getPhysicsV(float trainU) const;
        TrainWindow* t;

        Train train;
};