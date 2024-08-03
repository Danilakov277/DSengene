#include"AnimatedSprite.h"
#include"Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include<iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Renderer
{
    AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2D> pTexure,
        const std::string initialSubTexture,
        const std::shared_ptr<ShaderProgram> pShaderProgram,
        const glm::vec2& position,
        const glm::vec2& size,
        const float rotation):
        Sprite(std::move(pTexure),std::move(initialSubTexture),std::move(pShaderProgram),position,size,rotation)
    {
        m_pCurrentAnimationDurations = m_statesMap.end();
    }
    void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
    {
        m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
    }
	void AnimatedSprite::render() const
	{

        if (m_dirty)
        {

        auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);



        const GLfloat textureCoord[] =
        {
            subTexture.leftBottomUV.x,subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x,subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,subTexture.rightTopUV.y,

            subTexture.rightTopUV.x,subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x,subTexture.leftBottomUV.y
        };

        glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoord), &textureCoord);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_dirty = false;
        }

        Sprite::render();

	}
    void AnimatedSprite::update(const uint64_t delta)
    {
        if (m_pCurrentAnimationDurations != m_statesMap.end())
        {
            m_currentAnimationTime += delta;
            while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second)
            {
                m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
                ++m_currentFrame;
                m_dirty = true;
                if (m_currentFrame == m_pCurrentAnimationDurations->second.size())
                {
                    m_currentFrame = 0;
                }
            }

        }
    }
    void AnimatedSprite::setState(const std::string& newState)
    {
        auto it = m_statesMap.find(newState);
        if (it == m_statesMap.end())
        {
            std::cout << "Cant Found animation state: " << newState << std::endl;
            return;
        }
        if (it != m_pCurrentAnimationDurations) {
            m_currentAnimationTime = 0;
            m_currentFrame = 0;
            m_pCurrentAnimationDurations = it;
            m_dirty = true;
        }
    }
}