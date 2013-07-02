#include "SceneNode.h"
#include "PS_GLFuncs.h"

SceneNode::SceneNode(): m_bVisible(true) {
}

SceneNode::~SceneNode() {

}

void SceneNode::drawBBox() const
{
    DrawAABB(m_bbox.lower(), m_bbox.upper(), vec3f(0,0,1), 1.0f);
}


void SceneNode::setShaderEffectProgram(U32 glEffect)
{
    if(glEffect != INVALID_GLBUFFER)
    {
        m_uShaderEffectProgram = glEffect;
        m_effectType = setCustom;
    }
}

bool SceneNode::select(const Ray& ray) const {
    return m_bbox.intersect(ray, 0.0f, FLT_MAX);
}

void SceneNode::resetTransform() {
    if(m_spTransform == NULL)
        m_spTransform = SmartPtrSceneNodeTransform(new SceneNodeTransform());
    else
        m_spTransform->reset();
}
