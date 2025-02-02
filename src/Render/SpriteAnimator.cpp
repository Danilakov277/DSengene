#include "SpriteAnimator.h"

RenderEngine::SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) :
	m_pSprite(std::move(pSprite)),
	m_currentFrame(0),
	m_curentFrameDuration(m_pSprite->getFrameDuration(0)),
	m_curentAnimationTime(0),
    m_totalDuration(0)
{
    for (size_t currentFrameId = 0; currentFrameId < m_pSprite->getFrameCount(); ++currentFrameId)
    {
        m_totalDuration += m_pSprite->getFrameDuration(currentFrameId);
    }
}

void RenderEngine::SpriteAnimator::update(const double delta)
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

void RenderEngine::SpriteAnimator::reset()
{
    m_currentFrame = 0;
    m_curentFrameDuration = m_pSprite->getFrameDuration(0);
    m_curentAnimationTime = 0;
}
