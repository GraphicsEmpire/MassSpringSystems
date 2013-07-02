#include <GL/glew.h>
#include "MassSpringSystem.h"

#define DEFAULT_ROW_COUNT 64
#define DEFAULT_COL_COUNT 64
#define DEFAULT_KSPRING 1.0f
#define DEFAULT_KDAMPER 0.3f

#define TIMESTEP 1000.0f/60.0f

MassPoint::MassPoint() {
    setup(vec3f(-1, -1, -1), vec3f(1, 1, 1), vec4f(1, 0, 0, 1));
}

MassPoint::MassPoint(float side, const vec3f& center, const vec4f& color) {
    float hs = side * 0.5f;
    setup(center - vec3f(hs, hs, hs), center + vec3f(hs, hs, hs), color);
}

MassPoint::~MassPoint() {
    GLMeshBuffer::cleanup();
}

void MassPoint::setup(const vec3f& lo, const vec3f& hi, const vec4f& color)
{
    float l = lo.x;
    float r = hi.x;
    float b = lo.y;
    float t = hi.y;
    float n = lo.z;
    float f = hi.z;

    float vertices[][3] = { { l, b, f }, { l, t, f }, { r, t, f },
                            { r, b, f }, { l, b, n }, { l, t, n }, { r, t, n }, { r, b, n } };

    float normals[][3] = { { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, -1, 1 },
                            { -l, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 1, -1, -1 } };


    const int ctVertices = 8;
    vector<float> arrVertices;
    arrVertices.resize(24);
    for(int i=0; i < ctVertices; i++)
    {
        arrVertices[i*3 + 0] = vertices[i][0];
        arrVertices[i*3 + 1] = vertices[i][1];
        arrVertices[i*3 + 2] = vertices[i][2];
    }

    vector<float> arrNormals;
    arrNormals.resize(24);
    for(int i=0; i < ctVertices; i++)
    {
        vec3f n(&normals[i][0]);
        n.normalize();
        arrNormals[i*3 + 0] = n.x;
        arrNormals[i*3 + 1] = n.y;
        arrNormals[i*3 + 2] = n.z;
    }

    vector<U32> arrIndices;
    arrIndices.resize(24);
    arrIndices[0] = 0;
    arrIndices[1] = 3;
    arrIndices[2] = 2;
    arrIndices[3] = 1;

    arrIndices[4] = 4;
    arrIndices[5] = 5;
    arrIndices[6] = 6;
    arrIndices[7] = 7;

    arrIndices[8] = 3;
    arrIndices[9] = 0;
    arrIndices[10] = 4;
    arrIndices[11] = 7;

    arrIndices[12] = 1;
    arrIndices[13] = 2;
    arrIndices[14] = 6;
    arrIndices[15] = 5;

    arrIndices[16] = 2;
    arrIndices[17] = 3;
    arrIndices[18] = 7;
    arrIndices[19] = 6;

    arrIndices[20] = 5;
    arrIndices[21] = 4;
    arrIndices[22] = 0;
    arrIndices[23] = 1;

    //Setup Buffers
    setupVertexAttribs(arrVertices, 3, vatPosition);
    setupVertexAttribs(arrNormals, 3, vatNormal);
    setupPerVertexColor(color, ctVertices, 4);
    setupIndexBufferObject(arrIndices, ftQuads);

}

void MassPoint::draw() {
    glPushMatrix();

    if(m_spTransform)
        glMultMatrixf(m_spTransform->forward().cptr());
    GLMeshBuffer::draw();


    glPopMatrix();
}

//Dumble
SpringDumble::SpringDumble() {
    setup();
}

SpringDumble::~SpringDumble() {
    SAFE_DELETE(m_lpMassTop);
    SAFE_DELETE(m_lpMassBottom);
}

void SpringDumble::setup() {
    m_timestep = 1000.0f/60.0f/100.0f;
    m_top = vec3f(0, 0.5, 0);
    m_bottom = vec3f(0, -0.5, 0);
    m_restLen = m_prevLen = vec3f::distance(m_top, m_bottom);
    m_lpMassTop = new MassPoint(0.2f, vec3f(0, 0, 0), vec4f(0, 1, 0, 1));
    m_lpMassTop->resetTransform();
    m_lpMassTop->transform()->translate(m_top);

    m_lpMassBottom = new MassPoint(0.2f, vec3f(0, 0, 0), vec4f(1, 0, 0, 1));
    m_lpMassBottom->resetTransform();
    m_lpMassBottom->transform()->translate(m_bottom);
    m_kspring = DEFAULT_KSPRING;
    m_kdamper = DEFAULT_KDAMPER;
    m_prevVel = 0;
    m_massTop = 1.0f;
    m_massBottom = 1.0f;
}

void SpringDumble::draw() {
    m_lpMassTop->draw();
    m_lpMassBottom->draw();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_LINES);
        glVertex3fv(m_bottom.ptr());
        glVertex3fv(m_top.ptr());
    glEnd();
    glPopAttrib();
}

void SpringDumble::timestep(U64 timer) {
    PS_UNUSED(timer);

    float len = (m_top - m_bottom).length();
    float vs = (len - m_prevLen) / m_timestep;

    float fs = - m_kspring * (len - m_restLen) - m_kdamper * vs;
    float acc = fs / m_massBottom;
    float vel = acc * m_timestep;

    m_bottom = m_bottom - vec3f(0, 1, 0) * 0.5 * (m_prevVel + vel) * m_timestep;
    m_lpMassBottom->transform()->reset();
    m_lpMassBottom->transform()->translate(m_bottom);

    m_prevLen = len;
    m_prevVel = vel;
}

void SpringDumble::setShaderEffectAll(U32 uiShader) {
    m_lpMassBottom->setShaderEffectProgram(uiShader);
    m_lpMassTop->setShaderEffectProgram(uiShader);
}

void SpringDumble::force() {
    m_bottom = m_bottom - vec3f(0, 0.2, 0);
    m_lpMassBottom->transform()->translate(m_bottom);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Grid
Grid::Grid() {
    setup();
}

Grid::~Grid() {

}

void Grid::setup(int nx, int ny) {
    m_mass = 1.0f;
    m_kspring = DEFAULT_KSPRING;
    m_kdamper = DEFAULT_KDAMPER;
    m_ctPoints = nx * ny;

    const float slen = 0.1f;
    int index = 0;
    m_vCenters.resize(m_ctPoints);
    m_vSprings.resize(0);
    for(int i=0; i < nx; i++) {
        for(int j=0; j<ny; j++) {
            m_vCenters[index] = vec3f(i * slen, j * slen, 0);
            index++;
        }
    }

    //Data
    m_vPrevLengths.resize(m_ctPoints);
    m_vRestLengths.resize(m_ctPoints);
    m_vPrevVelocity.resize(m_ctPoints);

    std::fill(m_vPrevLengths.begin(), m_vPrevLengths.end(), slen);
    std::fill(m_vRestLengths.begin(), m_vRestLengths.end(), slen);
    std::fill(m_vPrevVelocity.begin(), m_vPrevVelocity.end(), 0.0f);
}

void Grid::draw() {
/*
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_LINES);
        glVertex3fv(m_bottom.ptr());
        glVertex3fv(m_top.ptr());
    glEnd();
    glPopAttrib();

    for(int i=0;i<m_vCenters.size(); i++) {

    }
    */
}

void Grid::timestep(U64 timer) {

}

void Grid::setShaderEffectAll(U32 uiShader) {

}

