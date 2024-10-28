#include "Game.h"

#include "../Resources/ResourcesManger.h"
#include "../Render/ShaderProgram.h"
#include "../Render/Sprite.h"
#include "../Render/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "GameObjects/Tank.h"
#include "GLFW/glfw3.h"
#include "Level.h"

#include <iostream>

Game::Game(const glm::ivec2& windowSize):
	m_eCurrentGameState(EGameState::Active),
    m_windowSize(windowSize)
{
	m_keys.fill(false);
}

Game::~Game()
{
}

void Game::render()
{
    //ResourceManger::getAnimatedSprite("NewAnimatedSprite")->render();
    if (m_pTank) {
        m_pTank->render();
    }
    if (m_pLevel)
    {
        m_pLevel->render();
    }

}

void Game::update(const uint64_t delta)
{
    //ResourceManger::getAnimatedSprite("NewAnimatedSprite")->update(delta);
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }
    if (m_pTank) {

        if (m_keys[GLFW_KEY_W] || m_keys[GLFW_KEY_UP])
        {
            m_pTank->setOrintation(Tank::EOrintation::top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A] || m_keys[GLFW_KEY_LEFT])
        {
            m_pTank->setOrintation(Tank::EOrintation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D] || m_keys[GLFW_KEY_RIGHT])
        {
            m_pTank->setOrintation(Tank::EOrintation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S] || m_keys[GLFW_KEY_DOWN])
        {
            m_pTank->setOrintation(Tank::EOrintation::Bottom);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }
        m_pTank->update(delta);
    }
}

void Game::setKey(const int key, const int action)
{



	m_keys[key] = action;
}

bool Game::init()
{
    ResourceManger::loadJSONResources("res/resources.json");

    auto pSpriteShaderProgram = ResourceManger::getShaderProgram("SpriteShader");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Cant find shader program" << "spriteShader" << std::endl;
        return false;
    }

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);


    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);



    m_pTank = std::make_unique<Tank>(0.000000015f, glm::vec2(0), glm::vec2(16.f, 16.f));
    m_pLevel = std::make_unique<Level>(ResourceManger::getLevels()[1]);


    return true;
}
