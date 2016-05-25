//
// Created by root on 18.05.16.
//
#include "Animation.h"

AnimationPart::AnimationPart(Transformation transformationTarget, int frames){
        m_MaxFrames = frames;
        m_CurrentFrame = 0;

        m_Step.m_Translation = transformationTarget.m_Translation/ frames;
        m_Step.m_Scale = transformationTarget.m_Scale/ frames;
        m_Step.m_Rotation = transformationTarget.m_Rotation/ frames;
        m_Step.m_Angle = transformationTarget.m_Angle / frames; }

void AnimationPart::reload(){
    m_CurrentFrame = 0;
}

/*
 * Returns the Transformation for one frame
 */
Transformation* AnimationPart::getTickChange(){
    if(m_CurrentFrame < m_MaxFrames) {
        m_CurrentFrame++;
        return &m_Step;
    }
    else
        return NULL;
}

// Animation

Animation::Animation(){
    m_CurrentPart = 0;
    m_CurrentLoop = 0;
    m_MaxLoops = 0;
}

void Animation::addAnimationPart(AnimationPart part){
	m_AnimationParts.push_back(part);
}

/*
 * Evaluates the current animationpart and returns the Transformation of a single frame.
 */
Transformation* Animation::tick(){

	if (m_CurrentPart >= m_AnimationParts.size()){
        if(m_CurrentLoop == m_MaxLoops){
            return NULL;
        }
        m_CurrentLoop++;
        m_CurrentPart = 0;
        return tick();
    }else{
		Transformation *transformation = m_AnimationParts[m_CurrentPart].getTickChange();

        if(transformation == NULL){
			m_AnimationParts[m_CurrentPart].reload();
            m_CurrentPart++;
            return tick();
        }
        return transformation;
    }
}

void Animation::reload(){
    m_CurrentLoop = 0;
    m_CurrentPart = 0;
}

void Animation::setMaxLoops(int maxLoops){
    m_MaxLoops = maxLoops-1;
}
