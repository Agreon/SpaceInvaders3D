//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_ANIMATION_H
#define SPACEINVADERS3D_ANIMATION_H

#include <vector>
#include <stddef.h>
#include <iostream>
#include "util.h"

/*
 * Every AnimationPart has a defined transformation which is applied in a defined amount of frames.
 */
class AnimationPart{
public:
    AnimationPart(Transformation transformationTarget, int frames);

    void reload();

    Transformation* getTickChange();
private:
    Transformation m_Step;

    int m_CurrentFrame, m_MaxFrames;
};

/*
 * One Animation consists of AnimationParts which are called one after another
 */
class Animation{
public:
    Animation();

    void addAnimationPart(AnimationPart part);

    Transformation* tick();

    void reload();

    void setMaxLoops(int maxLoops);

private:
    vector<AnimationPart> m_AnimationParts;
    int m_CurrentPart, m_CurrentLoop, m_MaxLoops;
};

#endif //SPACEINVADERS3D_ANIMATION_H
