#include "Game.h"

#include "../Resources/ResourcesManger.h"
#include "../Render/AnimatedSprite.h"
#include "../Render/ShaderProgram.h"
#include "../Render/Sprite.h"
#include "../Render/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

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
    ResourceManger::getAnimatedSprite("NewAnimatedSprite")->render();
}

void Game::update(const uint64_t delta)
{
    ResourceManger::getAnimatedSprite("NewAnimatedSprite")->update(delta);
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool Game::init()
{
    auto pDefaultShaderProgram = ResourceManger::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "cant create shader program: " << "Defaultshader" << std::endl;
        return false;
    }
    auto pSpriteShaderProgram = ResourceManger::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "cant create shader program: " << "Spriteshader" << std::endl;
        return false;
    }

    auto tex = ResourceManger::loadTexture("DefayltTextures", "res/textures/map_8x8.png");

    std::vector<std::string> subTexturesNames = {
        "block",
        "topLeftBlock",
        "topRightBlock",
        "topBlock",
        "bottomLeftBlock",
        "rightBlock",
        "bottomLeftTopRightBlock",
        "bottomRightZeroBlock",
        "bottomRightBlock",
        "topLeftBottomRightBlock",
        "leftBlock",
        "bottomLeftZerroBlock",
        "bottomBlock",
        "topRightZerroBlock",
        "topLeftZerroBlock",
        "woter_1",
        "woter_2",
        "woter_3",
        "beton",
        "bush" };
    auto pTextureAtlas = ResourceManger::loatTextureAtlas("DefaultTextureAtlas", subTexturesNames, "res/textures/map_8x8.png", 8, 8);

    auto pSprite = ResourceManger::loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "bush");
    pSprite->setPosition(glm::vec2(300.f, 100.f));

    auto pAnimatedSprite = ResourceManger::loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "bush");
    pAnimatedSprite->setPosition(glm::vec2(300.f, 300.f));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_3", 1000000000));

    pAnimatedSprite->insertState("woterState", std::move(waterState));

    pAnimatedSprite->setState("woterState");


    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);


    pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);


    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    return true;
}
