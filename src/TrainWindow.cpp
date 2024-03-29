/************************************************************************
     File:        TrainWindow.H

     Author:     
                  Michael Gleicher, gleicher@cs.wisc.edu

     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
     
     Comment:     
						this class defines the window in which the project 
						runs - its the outer windows that contain all of 
						the widgets, including the "TrainView" which has the 
						actual OpenGL window in which the train is drawn

						You might want to modify this class to add new widgets
						for controlling	your train

						This takes care of lots of things - including installing 
						itself into the FlTk "idle" loop so that we get periodic 
						updates (if we're running the train).


     Platform:    Visio Studio.Net 2003/2005

*************************************************************************/

#include <FL/fl.h>
#include <FL/Fl_Box.h>

// for using the real time clock
#include <time.h>

#include "TrainWindow.H"
#include "TrainView.H"
#include "CallBacks.H"


//************************************************************************
//
// * Constructor
//========================================================================
TrainWindow::
TrainWindow(const int x, const int y) 
	: Fl_Double_Window(x,y,900,600,"Train and Roller Coaster")
//========================================================================
{
	// make all of the widgets
	begin();	// add to this widget
	{
		int pty=5;			// where the last widgets were drawn

		trainView = new TrainView(5,5,590,590);
		trainView->tw = this;
		trainView->m_pTrack = &m_Track;
		this->resizable(trainView);

		// to make resizing work better, put all the widgets in a group
		widgets = new Fl_Group(600,5,290,590);
		widgets->begin();

		runButton = new Fl_Button(605,pty,60,20,"Run");
		togglify(runButton);

		Fl_Button* fb = new Fl_Button(700,pty,25,20,"@>>");
		fb->callback((Fl_Callback*)forwCB,this);
		Fl_Button* rb = new Fl_Button(670,pty,25,20,"@<<");
		rb->callback((Fl_Callback*)backCB,this);

        arcLength = new Fl_Button(730,pty,65,20,"ArcLength");
        togglify(arcLength,1);

        SubdivisionButton = new Fl_Button(800,pty,80,20,"Subdivision");
        togglify(SubdivisionButton,1);


        pty+=25;
        MountainButton = new Fl_Button(605,pty,65,20,"Mountain");
        togglify(MountainButton,1);

        PhysicButton = new Fl_Button(730,pty,65,20,"Physic");
        togglify(PhysicButton,1);

        pty+=25;
		speed = new Fl_Value_Slider(655,pty,140,20,"speed");
		speed->range(0,10);
		speed->value(2);
		speed->align(FL_ALIGN_LEFT);
		speed->type(FL_HORIZONTAL);

		pty += 30;

		// camera buttons - in a radio button group
		Fl_Group* camGroup = new Fl_Group(600,pty,195,20);
		camGroup->begin();
		worldCam = new Fl_Button(605, pty, 60, 20, "World");
        worldCam->type(FL_RADIO_BUTTON);		// radio button
        worldCam->value(1);			// turned on
        worldCam->selection_color((Fl_Color)3); // yellow when pressed
		worldCam->callback((Fl_Callback*)damageCB,this);
		trainCam = new Fl_Button(670, pty, 60, 20, "Train");
        trainCam->type(FL_RADIO_BUTTON);
        trainCam->value(0);
        trainCam->selection_color((Fl_Color)3);
		trainCam->callback((Fl_Callback*)damageCB,this);
		topCam = new Fl_Button(735, pty, 60, 20, "Top");
        topCam->type(FL_RADIO_BUTTON);
        topCam->value(0);
        topCam->selection_color((Fl_Color)3);
		topCam->callback((Fl_Callback*)damageCB,this);
		camGroup->end();

		pty += 30;

		// browser to select spline types
		// TODO: make sure these choices are the same as what the code supports
		splineBrowser = new Fl_Browser(605,pty,120,75,"Spline Type");
		splineBrowser->type(2);		// select
		splineBrowser->callback((Fl_Callback*)damageCB,this);
		splineBrowser->add("Linear");
		splineBrowser->add("Cardinal Cubic");
		splineBrowser->add("Cubic B-Spline");
		splineBrowser->select(2);

		pty += 110;

		// add and delete points
		Fl_Button* ap = new Fl_Button(605,pty,80,20,"Add Point");
		ap->callback((Fl_Callback*)addPointCB,this);
		Fl_Button* dp = new Fl_Button(690,pty,80,20,"Delete Point");
		dp->callback((Fl_Callback*)deletePointCB,this);

		pty += 25;
		// reset the points
		resetButton = new Fl_Button(735,pty,60,20,"Reset");
		resetButton->callback((Fl_Callback*)resetCB,this);
		Fl_Button* loadb = new Fl_Button(605,pty,60,20,"Load");
		loadb->callback((Fl_Callback*) loadCB, this);
		Fl_Button* saveb = new Fl_Button(670,pty,60,20,"Save");
		saveb->callback((Fl_Callback*) saveCB, this);

		pty += 25;
		// roll the points
		Fl_Button* rx = new Fl_Button(605,pty,30,20,"R+X");
		rx->callback((Fl_Callback*)rpxCB,this);
		Fl_Button* rxp = new Fl_Button(635,pty,30,20,"R-X");
		rxp->callback((Fl_Callback*)rmxCB,this);
		Fl_Button* rz = new Fl_Button(670,pty,30,20,"R+Z");
		rz->callback((Fl_Callback*)rpzCB,this);
		Fl_Button* rzp = new Fl_Button(700,pty,30,20,"R-Z");
		rzp->callback((Fl_Callback*)rmzCB,this);

		pty+=30;

        checkPointsCount = new Fl_Value_Slider(655,pty,140,20,"checkC");
        checkPointsCount->range(40,500);
        checkPointsCount->value(50);
        checkPointsCount->align(FL_ALIGN_LEFT);
        checkPointsCount->type(FL_HORIZONTAL);
        checkPointsCount->callback((Fl_Callback*)damageCB,this);

        pty+=25;

        trackWidth = new Fl_Value_Slider(655,pty,140,20,"trackW");
        trackWidth->range(1,10);
        trackWidth->value(6);
        trackWidth->align(FL_ALIGN_LEFT);
        trackWidth->type(FL_HORIZONTAL);
        trackWidth->type(FL_HORIZONTAL);
        trackWidth->callback((Fl_Callback*)damageCB,this);

        pty+=25;

        trackLineWidth = new Fl_Value_Slider(655,pty,140,20,"trackLW");
        trackLineWidth->range(1,10);
        trackLineWidth->value(1);
        trackLineWidth->align(FL_ALIGN_LEFT);
        trackLineWidth->type(FL_HORIZONTAL);
        trackLineWidth->callback((Fl_Callback*)damageCB,this);

        pty+=25;

        trackRoadWidth = new Fl_Value_Slider(655,pty,140,20,"trackRW");
        trackRoadWidth->range(1,10);
        trackRoadWidth->value(1);
        trackRoadWidth->align(FL_ALIGN_LEFT);
        trackRoadWidth->type(FL_HORIZONTAL);
        trackRoadWidth->callback((Fl_Callback*)damageCB,this);

        pty+=25;

        tension = new Fl_Value_Slider(655,pty,140,20,"tension");
        tension->range(0,1);
        tension->value(0.5f);
        tension->align(FL_ALIGN_LEFT);
        tension->type(FL_HORIZONTAL);
        tension->callback((Fl_Callback*)damageCB,this);

        pty+=25;

        HeadLightButton = new Fl_Button(605,pty,80,20,"HeadLight");
        togglify(HeadLightButton, 1);
        SunButton = new Fl_Button(695,pty,40,20,"Sun");
        togglify(SunButton, 1);

        pty+=25;

        TrackLineBrowser = new Fl_Browser(605,pty,120,60,"TrackLine Type");
        TrackLineBrowser->type(2);		// select
        TrackLineBrowser->callback((Fl_Callback*)damageCB,this);
        TrackLineBrowser->add("TwoLine");
        TrackLineBrowser->add("OneLine");
        TrackLineBrowser->select(1);

        pty += 70;

        TrackRoadBrowser = new Fl_Browser(605,pty,120,60,"TrackRoad Type");
        TrackRoadBrowser->type(2);		// select
        TrackRoadBrowser->callback((Fl_Callback*)damageCB,this);
        TrackRoadBrowser->add("Parallel Road");
        TrackRoadBrowser->add("Just Road");
        TrackRoadBrowser->select(1);

        pty += 70;

        // TODO: add widgets for all of your fancier features here
#ifdef EXAMPLE_SOLUTION
		makeExampleWidgets(this,pty);
#endif

		// we need to make a little phantom widget to have things resize correctly
		Fl_Box* resizebox = new Fl_Box(600,595,200,5);
		widgets->resizable(resizebox);

		widgets->end();
	}
	end();	// done adding to this widget

	// set up callback on idle
	Fl::add_idle((void (*)(void*))runButtonCB,this);
}

//************************************************************************
//
// * handy utility to make a button into a toggle
//========================================================================
void TrainWindow::
togglify(Fl_Button* b, int val)
//========================================================================
{
	b->type(FL_TOGGLE_BUTTON);		// toggle
	b->value(val);		// turned off
	b->selection_color((Fl_Color)3); // yellow when pressed	
	b->callback((Fl_Callback*)damageCB,this);
}

//************************************************************************
//
// *
//========================================================================
void TrainWindow::
damageMe()
//========================================================================
{
	if (trainView->selectedCube >= ((int)m_Track.points.size()))
		trainView->selectedCube = 0;
	trainView->damage(1);
}

//************************************************************************
//
// * This will get called (approximately) 30 times per second
//   if the run button is pressed
//========================================================================
void TrainWindow::
advanceTrain(float dir)
//========================================================================
{
	//#####################################################################
	// TODO: make this work for your train
	//#####################################################################
#ifdef EXAMPLE_SOLUTION
	// note - we give a little bit more example code here than normal,
	// so you can see how this works

	if (arcLength->value()) {
		float vel = ew.physics->value() ? physicsSpeed(this) : dir * (float)speed->value();
		world.trainU += arclenVtoV(world.trainU, vel, this);
	} else {
		world.trainU +=  dir * ((float)speed->value() * .1f);
	}

	float nct = static_cast<float>(world.points.size());
	if (world.trainU > nct) world.trainU -= nct;
	if (world.trainU < 0) world.trainU += nct;
#endif

    if(PhysicButton->value() && arcLength->value()) {
        m_Track.trainU += dir * ((float) m_Track.getPhysicsV(m_Track.trainU) * (float) speed->value() * .1f);
    }else if(arcLength->value()){
        m_Track.trainU +=  dir * ((float)speed->value() * m_Track.virtualPoints.size() / m_Track.points.size() * .1f);
    }else{
        m_Track.trainU +=  dir * ((float)speed->value() * .5f);
    }

//    if (arcLength->value()) {
////        float vel = ew.physics->value() ? physicsSpeed(this) : dir * (float)speed->value();
//        float vel = dir * (float)speed->value();
//        //todo : v to version arcLen
////        m_Track.trainU +=  dir * ((float)speed->value() * .1f);
////        m_Track.trainU +=  dir * ((float)m_Track.getArcV() * (float)speed->value() * .1f);
//        m_Track.trainU +=  dir * ((float)m_Track.getPhysicsV(m_Track.trainU) * (float)speed->value() * .1f);
//    } else {
//        m_Track.trainU +=  dir * ((float)speed->value() * .1f);
//    }

    float nct = static_cast<float>(arcLength->value() ? m_Track.virtualPoints.size() : m_Track.virtualPoints.size());
    if (m_Track.trainU > nct) m_Track.trainU -= nct;
    if (m_Track.trainU < 0) m_Track.trainU += nct;
}