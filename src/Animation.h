//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_ANIMATION_H
#define SPACEINVADERS3D_ANIMATION_H

#include <vector>
#include <stddef.h>
#include <iostream>
#include "util.h"

class AnimationPart{
public:
    AnimationPart(Transformation transformationTarget, int frames){
        m_Transformation = transformationTarget;

        m_MaxFrames = frames;
        m_CurrentFrame = 0;


        m_Step.m_Translation = transformationTarget.m_Translation/ frames;
        m_Step.m_Scale = transformationTarget.m_Scale/ frames;
        m_Step.m_Rotation = transformationTarget.m_Rotation/ frames;
        m_Step.m_Angle = transformationTarget.m_Angle / frames;
       //s m_Step = m_Transformation / frames;
    }

    void reload(){
        m_CurrentFrame = 0;
    }

    Transformation* getTickChange(){
        if(m_CurrentFrame < m_MaxFrames) {
            m_CurrentFrame++;
            return &m_Step;
        }
        else
            return NULL;
    }

private:
    Transformation m_Transformation;
    Transformation m_Step;

    int m_CurrentFrame, m_MaxFrames;
};

class Animation{
public:
    Animation(){
        m_CurrentPart = 0;
        m_CurrentLoop = 0;
        m_MaxLoops = 0;
    }

    void addAnimationPart(AnimationPart part){
        animationParts.push_back(part);
    }

    /*
     * @param int : Amount. if -1 endless
     */
    Transformation* tick(){

        if(m_CurrentPart >= animationParts.size()){
            if(m_CurrentLoop == m_MaxLoops){
                return NULL;
            }
            m_CurrentLoop++;
            m_CurrentPart = 0;
            return tick();
        }else{
            Transformation *transformation = animationParts[m_CurrentPart].getTickChange();

            if(transformation == NULL){
                animationParts[m_CurrentPart].reload();
                m_CurrentPart++;
                return tick();
            }
            return transformation;
        }
    }

    void reload(){
        m_CurrentLoop = 0;
        m_CurrentPart = 0;
    }

    void setMaxLoops(int maxLoops){
        m_MaxLoops = maxLoops-1;
    }

private:
    vector<AnimationPart> animationParts;
    int m_CurrentPart, m_CurrentLoop, m_MaxLoops;
};

#endif //SPACEINVADERS3D_ANIMATION_H
