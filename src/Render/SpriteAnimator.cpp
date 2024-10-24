#include "SpriteAnimator.h"

RenderEngine::SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) :
	m_pSprite(std::move(pSprite)),
	m_currentFrame(0),
	m_curentFrameDuration(m_pSprite->getFrameDuration(0)),
	m_curentAnimationTime(0)
{
}

void RenderEngine::SpriteAnimator::update(const uint64_t delta)
{

    m_curentAnimationTime += delta;
    while (m_curentAnimationTime >= m_curentFrameDuration)
    {

        m_curentAnimationTime -= m_curentFrameDuration;
        ++m_currentFrame;
        if (m_currentFrame == m_pSprite->getFrameCount())
        {
            m_currentFrame = 0;
        }
        m_curentFrameDuration = m_pSprite->getFrameDuration(m_currentFrame);
    }
}
