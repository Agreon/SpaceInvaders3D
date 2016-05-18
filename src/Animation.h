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
    AnimationPart(Transformation transformationTarget, int frames);

    void reload();

    Transformation* getTickChange();
private:
    Transformation m_Transformation;
    Transformation m_Step;

    int m_CurrentFrame, m_MaxFrames;
};

class Animation{
public:
    Animation();

    void addAnimationPart(AnimationPart part);

    /*
     * @param int : Amount. if -1 endless
     */
    Transformation* tick();

    void reload();

    void setMaxLoops(int maxLoops);

private:
    vector<AnimationPart> animationParts;
    int m_CurrentPart, m_CurrentLoop, m_MaxLoops;
};

#endif //SPACEINVADERS3D_ANIMATION_H
