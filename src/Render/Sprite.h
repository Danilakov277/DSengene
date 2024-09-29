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
		Sprite(const std::shared_ptr<Texture2D> pTexure,
			const std::string initialSubTexture,
			const std::shared_ptr<ShaderProgram> pShaderProgram);


		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		virtual void render(const glm::vec2& position,const glm::vec2& size, const float rotation) const;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;

		VertexArray m_vertexArray;

		VertexBuffer m_vertexCoordBuffer;
		VertexBuffer m_textureCoordBuffer;

		IndexBuffer m_indexBuffer;



		glm::vec2 m_currentLeftBotomUV;
		glm::vec2 m_currentRightTopUV;

	};

}