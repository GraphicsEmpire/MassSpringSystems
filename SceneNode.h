#ifndef SCENENODE_H
#define SCENENODE_H

#include "loki/SmartPtr.h"
#include "SceneNodeTransform.h"
#include "PS_Box.h"
#include "PS_Vector.h"

using namespace Loki;
using namespace std;
using namespace PS;
using namespace PS::MATH;


//class PS::MESH::MeshMaterial;

/*!
 * \brief Defines a 1,2,3 dimensional texture to be applied on the scene node for rendering.
 * provides mechanisms for reading and writing to/from png files using lodepng lib.
 */
class EffectTexture{
public:
    EffectTexture() {}
    virtual ~EffectTexture() {}
private:
    vec2i m_dim;
    U32 m_uiTexture;
};

/*!
 * The entire animation scene is modeled in a giant scene graph structure.
 * SceneGraph is serializable and supports mesh-based and non-mesh based models.
 * SceneGraph is generic and can be scripted through python bindings.
 * SceneGraph is highly optimized for fast rasterization.
 * For future work scenegraph will be sent to OpenCL Ray-Tracer for building high-quality output.
 */
class SceneNodeEffect{
public:
    SceneNodeEffect() {}
    virtual ~SceneNodeEffect() {}
    enum EffectType {etMaterial, etTexture, etCustomShader};



    EffectType etype() const {return m_effectType;}
private:
    EffectType m_effectType;
    //PS::SHADER::GLShaderProgram* m_lpShader;
    //PS::MESH::MeshMaterial* m_lpMaterial;
};

//SmartPtrSceneEffect
typedef Loki::SmartPtr<
        SceneNodeEffect,
        RefCounted,
        AllowConversion,
        AssertCheck,
        DefaultSPStorage > SmartPtrSceneNodeEffect;

enum ShaderEffectType {setFixedFunction, setCustom};

/*!
 * \brief The SceneNode class is an element in the scenegraph can have
 * effect and transformation associated with.
 */
class SceneNode {
public:
    static const U32 INVALID_GLBUFFER = ~0;

    SceneNode();
    virtual ~SceneNode();

    //Pure virtual function for all kids to override
    virtual void draw() = 0;
    virtual void drawBBox() const;

    //Advances animation
    virtual void timestep(U64 timer) {
        PS_UNUSED(timer);
    }

    //Computes the bounding box of the model
    void setBBox(const AABB& box) { m_bbox = box;}
    virtual AABB bbox() const { return m_bbox;}

    //Effect
    void setShaderEffectProgram(U32 glEffect);
    U32 getShaderEffectProgram() const {return m_uShaderEffectProgram;}

    void setEffectType(ShaderEffectType effect) { m_effectType = effect;}
    ShaderEffectType getEffectType() const {return m_effectType;}


    //Selection
    virtual bool select(const Ray& ray) const;

    //TODO: Method for marshalling this node in a compact data-structure
    //The compact structure will serve as input to high performance rendering
    //Algorithms such as: Ray-tracing
    void marshal() {}

    //Name for hashing and fetching of the nodes
    string name() const {return m_name;}
    void setName(const string& name) {m_name = name;}

    //Visibility
    bool isVisible() const {return m_bVisible;}
    void setVisible(bool visible) {m_bVisible = visible;}

    //Effect to be managed by asset and shadermanager collections
    SmartPtrSceneNodeEffect effect() const {return m_spEffect;}
    void setEffect(const SmartPtrSceneNodeEffect& spEffect) { m_spEffect = spEffect;}

    //Transformation
    SmartPtrSceneNodeTransform transform() const { return m_spTransform;}
    void setTransform(const SmartPtrSceneNodeTransform& spTransform) {
        m_spTransform = spTransform;
    }
    void resetTransform();

    //TODO: IO to be able to read and write scene nodes to disk in very fast binary format
    bool read() {return false;}
    bool write() {return false;}
protected:
    //Each scene node should have its associated bounding box.
    //For selection, Hidden Surface Culling and Ray-tracing
    AABB m_bbox;

    //Attribs
    string m_name;
    bool m_bVisible;

    //Shader and Effect
    U32 m_uShaderEffectProgram;
    ShaderEffectType m_effectType;

    //bool m_bAnimated;
    SmartPtrSceneNodeEffect m_spEffect;
    SmartPtrSceneNodeTransform m_spTransform;
};

#endif // SCENENODE_H
