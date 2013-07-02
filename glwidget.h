//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
//These two lines are header guiardians against multiple includes
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "PS_ArcBallCamera.h"
#include "MassSpringSystem.h"

using namespace PS;

typedef enum DragDirection {ddNone, ddLeft, ddRight};

//This is our OpenGL Component we built it on top of QGLWidget
class GLWidget : public QGLWidget
{
	Q_OBJECT

public slots:
	void showFaces(int face);	
	void showWireFrame(bool bEnable);
	void showTetra(bool bEnable);
	void setTetraSpace(int space);

	void xSliderChanged(int value);
	void ySliderChanged(int value);
	void zSliderChanged(int value);

    void setKSpring(double ks);
    void setKDamper(double kd);
    void setMass(double m);
    void setTimerInterval(double dt);


	void enableSpin(bool bEnable);
    void advanceAnimation();
signals:

	void rotateX(int value);
	void rotateY(int value);
	void rotateZ(int value);
public:
	//Constructor for GLWidget
	GLWidget(QWidget *parent = 0);

	//Destructor for GLWidget
	~GLWidget();

protected:
	//Initialize the OpenGL Graphics Engine
	void initializeGL();

	//All our painting stuff are here
	void paintGL();

	//When user resizes main window, the scrollArea will be resized and it will call this function from
	//its attached GLWidget
	void resizeGL(int width, int height);

	//Handle mouse press event in scrollArea
	void mousePressEvent(QMouseEvent *event);

	//Handle mouse move event in scrollArea
	void mouseMoveEvent(QMouseEvent *event);

	//Handle mouse release event in scrollArea
	void mouseReleaseEvent(QMouseEvent *event);

private:
	//Makes each face of the polygon
	void drawTetraHedra(int a, int b, int c, int d);
	void drawTetraHedra(int a, int b, int c, int d, bool bWired);

	void drawCubeFace(int a, int b, int c, int d);
	void drawCubeFace(int a, int b, int c, int d, bool bWired);

	//It is much more efficient if you create all the objects in a scene
	//in one place and group them in a list. Then this will be plugged into graphics hardware at runtime.
	GLdouble m_theta[3];
	int m_axis;
	int m_face;
	int m_tetraSpace;

	bool m_bWireFrame;
	bool m_bTetra;
	bool m_bCenterCamera;

    U32 m_uiPhongShader;

	//Camera
    ArcBallCamera m_camera;

	//Drag Direction
	DragDirection m_dragdir;

	//Timer
	QTimer * m_timer;

	//Holds the last mouse position
    QPoint m_lastPos;

    SpringDumble* m_lpDumble;
};


#endif
