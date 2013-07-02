//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department 
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
#include <QtGui>
#include <QtOpenGL>

#include "glwidget.h"
#include "window.h"


//------------------------------------------------------------------------------------
// Creates and initializes the main window for application
//------------------------------------------------------------------------------------
Window::Window(QWidget *parent):QDialog(parent)
{
	//We create an instance of GLWidget component we built in glwidget.h
	m_glWidget = new GLWidget;

	//Setup application interface. Creates all the required components and sliders.
	setupUi(this);

	//We need to attach our m_glWidget to glWidgetArea
	//All our drawings will be on glWidgetArea
	glWidgetArea->setWidget(m_glWidget);

	//Setting up all the SIGNALS and SLOTS
	connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));

    connect(spKSpring, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setKSpring(double)));
    connect(spKDamper, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setKDamper(double)));
    connect(spKMass, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setMass(double)));
    connect(spInterval, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setTimerInterval(double)));

}
