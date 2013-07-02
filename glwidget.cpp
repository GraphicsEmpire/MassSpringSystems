//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
#include "GL/glew.h"

#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include "glwidget.h"
#include "PS_GLFuncs.h"

#define Left	-2.0
#define Right	+2.0
#define Bottom	-2.0
#define Top	+2.0
#define Near    -10.0
#define Far     +10.0


//Directions
const int L =	0;  /* left direction:	-x, -i */
const int R =	1;  /* right direction:	+x, +i */
const int B =	2;  /* bottom direction: -y, -j */
const int T =	3;  /* top direction:	+y, +j */
const int N =	4;  /* near direction:	-z, -k */
const int F =	5;  /* far direction:	+z, +k */
const int ALL = 6;

//CORNERS
const int LBN =	0;  /* left bottom near corner  */
const int LBF =	1;  /* left bottom far corner   */
const int LTN =	2;  /* left top near corner     */
const int LTF =	3;  /* left top far corner      */
const int RBN =	4;  /* right bottom near corner */
const int RBF =	5;  /* right bottom far corner  */
const int RTN =	6;  /* right top near corner    */
const int RTF =	7;  /* right top far corner     */

GLfloat vertices [][3] = {{-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
{1.0, -1.0, 1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0},
{1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}};

GLfloat xyzVertices [][3] = {{-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f},
{-1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f},
{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}};

GLfloat clGray[3] = {0.5f, 0.5f, 0.5f};
GLfloat colors [][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0},
{0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

////////////////////////////////////////////////
//Vertex Shader Code
const char * g_lpVertexShaderCode =
    "varying vec3 N;"
    "varying vec3 V; "
    "void main(void) {"
    "gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
    "gl_FrontColor = gl_Color;"
    "N = normalize(gl_NormalMatrix * gl_Normal);"
    "V = vec3(gl_ModelViewMatrix * gl_Vertex); }";

//Fragment Shader Code
const char* g_lpFragShaderCode =
    "varying vec3 N;"
    "varying vec3 V;"
    "void main(void) {"
    "vec3 L = normalize(gl_LightSource[0].position.xyz - V);"
    "vec3 E = normalize(-V);"
    "vec3 R = normalize(-reflect(L, N));"
    "vec4 Iamb = 0.5 * gl_LightSource[0].ambient * gl_Color;"
    "vec4 Idif = (gl_LightSource[0].diffuse * gl_Color) * max(dot(N,L), 0.0);"
    "vec4 Ispec = (gl_LightSource[0].specular * (vec4(0.8, 0.8, 0.8, 0.8) + 0.2 * gl_Color)) * pow(max(dot(R, E), 0.0), 32.0);"
    "gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idif + Ispec;	}";

////////////////////////////////////////////////////////////////////////////////////////


#define MAX_X 2.0f
#define MAX_Y 2.0f


GLWidget::GLWidget(QWidget *parent)
: QGLWidget(parent)
{
    m_lpDumble = NULL;


	m_bCenterCamera = false;
	m_bWireFrame = false;
	m_bTetra = false;
	m_tetraSpace = 0;
	m_face = ALL;

	m_dragdir = ddNone;

	m_theta[0] = 0.0f;
	m_theta[1] = 0.0f;
	m_theta[2] = 0.0f;

	m_axis = 0;
	m_timer = new QTimer(this);
    m_timer->setInterval(1000/60);
    m_timer->start();

    connect(m_timer, SIGNAL(timeout()), this,SLOT(advanceAnimation()));
}

void GLWidget::advanceAnimation()
{
    if(m_lpDumble)
        m_lpDumble->timestep(1000/60);

	updateGL();
}

GLWidget::~GLWidget()
{    
	makeCurrent();

    SAFE_DELETE(m_lpDumble);
}

void GLWidget::initializeGL()
{
    glewInit();

    //Dumble
    CompileShaderCode(g_lpVertexShaderCode, g_lpFragShaderCode, m_uiPhongShader);
    m_lpDumble = new SpringDumble();
    m_lpDumble->setShaderEffectAll(m_uiPhongShader);



	//Background color will be white
	glClearColor(0.0, 0.0, 0.0, 1.0);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(2.0f);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLWidget::paintGL()
{
	makeCurrent();

	//Clear target buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the camera position, orientation and target
    vec3f p = m_camera.getPos();
    gluLookAt(p.x, p.y, p.z, 0, 0, 0, 0, 1, 0);

	glRotated(m_theta[0], 1.0, 0.0, 0.0);
	glRotated(m_theta[1], 0.0, 1.0, 0.0);
	glRotated(m_theta[2], 0.0, 0.0, 1.0);

    if(m_lpDumble)
        m_lpDumble->draw();

}

void GLWidget::showTetra(bool bEnable)
{
	m_bTetra = bEnable;
	updateGL();
}

void GLWidget::setTetraSpace(int space)
{
	m_tetraSpace = space;
	updateGL();
}

void GLWidget::drawTetraHedra(int a, int b, int c, int d)
{
	drawTetraHedra(a, b, c, d, m_bWireFrame);
	if(!m_bWireFrame)
	{
		glColor3fv(clGray);
		drawTetraHedra(a, b, c, d, true);
	}
}

void GLWidget::drawTetraHedra(int a, int b, int c, int d, bool bWired)
{	
    vec3f dir;
    vec3f tetra[4];
    vec3f cubeCenter = vec3f(0.0, 0.0, 0.0);
    vec3f tetraCenter= vec3f(0.0, 0.0, 0.0);
	
    tetra[0] = vec3f(xyzVertices[a]);
    tetra[1] = vec3f(xyzVertices[b]);
    tetra[2] = vec3f(xyzVertices[c]);
    tetra[3] = vec3f(xyzVertices[d]);
	for(int i=0; i<4; i++)
	{
        tetraCenter = tetraCenter + tetra[i];
	}

    tetraCenter = tetraCenter * 0.25f;

	dir = tetraCenter - cubeCenter;
    dir.normalize();
	for(int i=0; i<4; i++)
	{			
        tetra[i] = tetra[i] + dir * static_cast<float>(m_tetraSpace / 100.0f);
	}

    vec3f va,vb,vc,vd;
	va = tetra[0];
	vb = tetra[1];
	vc = tetra[2];
	vd = tetra[3];

	if(bWired)
	{
		glLineWidth(2.0f);
		glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vd.x, vd.y, vd.z);

			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vc.x, vc.y, vc.z);
			glVertex3f(vd.x, vd.y, vd.z);

			glVertex3f(vd.x, vd.y, vd.z);
			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vc.x, vc.y, vc.z);

			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vc.x, vc.y, vc.z);
		glEnd();
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glBegin(GL_TRIANGLES);
			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vd.x, vd.y, vd.z);

			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vc.x, vc.y, vc.z);
			glVertex3f(vd.x, vd.y, vd.z);

			glVertex3f(vd.x, vd.y, vd.z);
			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vc.x, vc.y, vc.z);

			glVertex3f(va.x, va.y, va.z);
			glVertex3f(vb.x, vb.y, vb.z);
			glVertex3f(vc.x, vc.y, vc.z);
		glEnd();
		glPopMatrix();
	}

}

void GLWidget::drawCubeFace(int a, int b, int c, int d)
{
	drawCubeFace(a, b, c, d, m_bWireFrame);
}

void GLWidget::drawCubeFace(int a, int b, int c, int d, bool bWired)
{
	if(bWired)
	{
		glLineWidth(4.0f);
		glPushMatrix();
			glBegin(GL_LINE_LOOP);	
				glVertex3fv(xyzVertices[a]);
				glVertex3fv(xyzVertices[b]);
				glVertex3fv(xyzVertices[c]);
				glVertex3fv(xyzVertices[d]);
			glEnd();
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
			glBegin(GL_POLYGON);	
				glVertex3fv(xyzVertices[a]);
				glVertex3fv(xyzVertices[b]);
				glVertex3fv(xyzVertices[c]);
				glVertex3fv(xyzVertices[d]);
			glEnd();
		glPopMatrix();
	}
}

void GLWidget::showWireFrame(bool bWireFrame)
{
	m_bWireFrame = bWireFrame;
	updateGL();
}

void GLWidget::showFaces(int face)
{
	m_face = face;
	updateGL();
}

void GLWidget::xSliderChanged(int value)
{
	m_theta[0] = value;
	updateGL();
}

void GLWidget::ySliderChanged(int value)
{
	m_theta[1] = value;
	updateGL();
}

void GLWidget::zSliderChanged(int value)
{
	m_theta[2] = value;
	updateGL();
}

void GLWidget::setKSpring(double ks) {
    if(m_lpDumble)
        m_lpDumble->setKSpring(static_cast<float>(ks));
}

void GLWidget::setKDamper(double kd) {
    if(m_lpDumble)
        m_lpDumble->setKDamper(static_cast<float>(kd));
}

void GLWidget::setMass(double m) {
    if(m_lpDumble)
        m_lpDumble->setMass(static_cast<float>(m));
}

void GLWidget::setTimerInterval(double dt) {
    if(m_lpDumble)
        m_lpDumble->setTimeStep(static_cast<float>(dt));
}


void GLWidget::enableSpin(bool bEnable)
{
	if(bEnable)
		m_timer->start();
	else
		m_timer->stop();
}

void GLWidget::resizeGL(int width, int height)
{
	GLfloat fieldOfView = 60.0f;
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(fieldOfView,(GLdouble) width/height, 1, 3000);
    //glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		m_axis = 0;
		m_dragdir = ddLeft;
	}
    else if(event->buttons() & Qt::MidButton)  {
		m_axis = 1;
        m_lpDumble->force();
    }
	else if(event->buttons() & Qt::RightButton)
	{
		m_axis = 2;
		m_dragdir = ddRight;
	}
	else
		m_axis = 0;

	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();

	int dx = x - m_lastPos.x();
	int dy = m_lastPos.y() - y;

	if(m_dragdir == ddLeft)        
	{
        m_camera.setRoll(m_camera.getRoll() + (0.3 * dx));
        m_camera.setTilt(m_camera.getTilt() + (0.3 * dy));
	}
	else if(m_dragdir ==  ddRight)
	{
        m_camera.setZoom(m_camera.getZoom() + 0.1 * dy);
	}

	m_lastPos = event->pos();
	updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	m_dragdir = ddNone;
}



