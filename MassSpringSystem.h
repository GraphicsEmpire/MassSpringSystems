#ifndef SPRING_H
#define SPRING_H

#include "PS_Vector.h"
#include "PS_GLMeshBuffer.h"

using namespace PS;
using namespace PS::MATH;

class MassPoint : public GLMeshBuffer {
public:
    MassPoint();
    MassPoint(float side, const vec3f& center, const vec4f& color);
    virtual ~MassPoint();
    void draw();

protected:
    void setup(const vec3f& lo, const vec3f& hi, const vec4f& color);
};

/*!
 * Simple Spring Test
 */
class SpringDumble : SceneNode {
public:
    SpringDumble();
    virtual ~SpringDumble();

    void setKSpring(float kspring) { m_kspring = kspring;}
    void setKDamper(float kdamper) { m_kdamper = kdamper;}
    void setMass(float mass) { m_massTop = m_massBottom = mass;}
    void setTimeStep(float dt) { m_timestep = dt;}

    void draw();
    void timestep(U64 timer);
    void setShaderEffectAll(U32 uiShader);

    void force();
protected:
    void setup();

private:
    float m_timestep;
    float m_kspring;
    float m_kdamper;
    float m_massTop;
    float m_massBottom;

    MassPoint* m_lpMassTop;
    MassPoint* m_lpMassBottom;
    vec3f m_top;
    vec3f m_bottom;

    float m_restLen;
    float m_prevLen;
    float m_prevVel;
};

/*!
 * \brief The Grid class
 */
class Grid : SceneNode {
public:
    Grid();
    virtual ~Grid();

    void setKSpring(float kspring) { m_kspring = kspring;}
    void setKDamper(float kdamper) { m_kdamper = kdamper;}
    void setMass(float mass) { m_mass = mass;}
    void setTimeStep(float dt) { m_timestep = dt;}

    void draw();
    void timestep(U64 timer);
    void setShaderEffectAll(U32 uiShader);

protected:
    void setup(int nx = 20, int ny = 20);

private:
    float m_timestep;
    float m_kspring;
    float m_kdamper;
    float m_mass;

    int m_ctPoints;

    vector<vec2i> m_vSprings;
    vector<vec3f> m_vCenters;
    vector<float> m_vPrevLengths;
    vector<float> m_vRestLengths;

    vector<float> m_vPrevVelocity;

};


#endif // SPRING_H
