#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include <memory>
#include<string>

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:

		struct FrameDescription
		{
			FrameDescription(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV, const uint64_t _duration):
				leftBottomUV(_leftBottomUV),
				rightTopUV(_rightTopUV),
				duration(_duration)
			{}
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			uint64_t duration;
		};

		Sprite(const std::shared_ptr<Texture2D> pTexure,
			const std::string initialSubTexture,
			const std::shared_ptr<ShaderProgram> pShaderProgram);


		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void insertFrames(std::vector<FrameDescription> framesDescriptions);

		void render(const glm::vec2& position,const glm::vec2& size, const float rotation, const float layer = 0.f, const size_t frameId = 0) const;
		uint64_t getFrameDuration(const size_t frameId) const;
		size_t getFrameCount() const;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;

		VertexArray m_vertexArray;

		VertexBuffer m_vertexCoordBuffer;
		VertexBuffer m_textureCoordBuffer;

		IndexBuffer m_indexBuffer;



		glm::vec2 m_currentLeftBotomUV;
		glm::vec2 m_currentRightTopUV;

		std::vector<FrameDescription> m_framesDescriptions;
		mutable size_t m_lastframeId;

	};

}