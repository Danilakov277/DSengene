#include"Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace RenderEngine
{
	Sprite::Sprite(const std::shared_ptr<Texture2D> pTexure,
		const std::string initialSubTexture,
		const std::shared_ptr<ShaderProgram> pShaderProgram):
		m_pTexture(std::move(pTexure)),
		m_pShaderProgram(std::move(pShaderProgram)),
		m_lastframeId(0)
	{
		const GLfloat vertexCoord[] =
		{
			0.f,0.f,
			0.f,1.f,
			1.f,1.f,
			1.f,0.f
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoord[] =
		{
			subTexture.leftBottomUV.x,subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x,subTexture.rightTopUV.y,
			subTexture.rightTopUV.x,subTexture.rightTopUV.y,
			subTexture.rightTopUV.x,subTexture.leftBottomUV.y
		};
		const GLint indices[] =
		{
          0,1,2,
		  2,3,0
		};

		

		m_vertexCoordBuffer.init(&vertexCoord,2*4*sizeof(GL_FLOAT));
		VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBufer(m_vertexCoordBuffer, vertexCoordsLayout);


		m_textureCoordBuffer.init(&textureCoord, 2 * 4 * sizeof(GL_FLOAT));
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBufer(m_textureCoordBuffer, textureCoordsLayout);


		m_indexBuffer.init(indices, 6);

		m_vertexArray.unbind();
		m_indexBuffer.unbind();

	}
	Sprite::~Sprite()
	{
		
	}
	void Sprite::insertFrames(std::vector<FrameDescription> framesDescriptions)
	{
		m_framesDescriptions = std::move(framesDescriptions);
	}
	void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation,const float layer, const size_t frameId) const
	{
		if (m_lastframeId != frameId)
		{
			m_lastframeId = frameId;
		const FrameDescription& currentFrameDescription = m_framesDescriptions[frameId];

		const GLfloat textureCoord[] =
		{
			currentFrameDescription.leftBottomUV.x,currentFrameDescription.leftBottomUV.y,
			currentFrameDescription.leftBottomUV.x,currentFrameDescription.rightTopUV.y,
			currentFrameDescription.rightTopUV.x,currentFrameDescription.rightTopUV.y,
			currentFrameDescription.rightTopUV.x,currentFrameDescription.leftBottomUV.y
		};

		m_textureCoordBuffer.update(&textureCoord, 2 * 4 * sizeof(GLfloat));
	}

		m_pShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.f));

		m_pShaderProgram->setMatrix4("modelMat", model);
		m_pShaderProgram->setFloat("layer", layer);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();


		Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);

	}

	double Sprite::getFrameDuration(const size_t frameId) const
	{
		return m_framesDescriptions[frameId].duration;
	}

	size_t Sprite::getFrameCount() const
	{
		return m_framesDescriptions.size();
	}

}