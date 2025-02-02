#pragma once
#include <memory>
#include "Sprite.h"

namespace RenderEngine
{
	class Sprite;
	class SpriteAnimator
	{
	public:
		SpriteAnimator(std::shared_ptr<Sprite> pSprite);
		size_t getCurrentFrame() const { return m_currentFrame;};
		void update(const double delta);
		double getTotalDuration() const { return m_totalDuration; }
		void reset();
	private:
		std::shared_ptr<Sprite> m_pSprite;
		size_t m_currentFrame;
		double m_curentFrameDuration;
		double m_curentAnimationTime;
		double m_totalDuration;
	};
}