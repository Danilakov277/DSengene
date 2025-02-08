#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"


namespace Physics {


	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;
	void PhysicsEngine::init()
	{
	}

	void PhysicsEngine::terminate()
	{
		m_dynamicObjects.clear();
		m_pCurrentLevel.reset();
	}

	void PhysicsEngine::update(const double delta)
	{
		for (auto& currentDunamicObject : m_dynamicObjects)
		{
			if (currentDunamicObject->getCurrentVelocity() > 0)
			{
				if (currentDunamicObject->getCurrentDirection().x != 0.f) // right and left
				{
					currentDunamicObject->getCurrentPosition() = glm::vec2(currentDunamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDunamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
				}
				else if (currentDunamicObject->getCurrentDirection().y != 0.f) // top and bottom
				{
					currentDunamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDunamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f, currentDunamicObject->getCurrentPosition().y);
				}
				const auto newPosition = currentDunamicObject->getCurrentPosition() + currentDunamicObject->getCurrentDirection() * static_cast<float>(currentDunamicObject->getCurrentVelocity() * delta);

				std::vector<std::shared_ptr<IGameObject>> objectToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, newPosition + currentDunamicObject->getSize());
				const auto& colliders = currentDunamicObject->getColliders();
				bool hasCollision = false;

				ECollisionDirection dunaicObjectCollisionDirection = ECollisionDirection::Right;
				if (currentDunamicObject->getCurrentDirection().x < 0) dunaicObjectCollisionDirection = ECollisionDirection::Left;
				else if (currentDunamicObject->getCurrentDirection().y > 0)dunaicObjectCollisionDirection = ECollisionDirection::Top;
				else if (currentDunamicObject->getCurrentDirection().y < 0)dunaicObjectCollisionDirection = ECollisionDirection::Bottom;

				ECollisionDirection objectCollisionDirection = ECollisionDirection::Left;
				if (currentDunamicObject->getCurrentDirection().x < 0) objectCollisionDirection = ECollisionDirection::Right;
				else if (currentDunamicObject->getCurrentDirection().y > 0)objectCollisionDirection = ECollisionDirection::Bottom;
				else if (currentDunamicObject->getCurrentDirection().y < 0)objectCollisionDirection = ECollisionDirection::Top;



				for (const auto& currentDumamicObjectToCheck : colliders)
				{
					for (const auto& currentObjectToCheck : objectToCheck)
					{
						const auto& collidersToCheck = currentObjectToCheck->getColliders();
						if (currentObjectToCheck->collides(currentDunamicObject->getObjectType()) && !collidersToCheck.empty())
						{
							for (const auto& currentObjectCollider : currentObjectToCheck->getColliders())
							{
								if (currentObjectCollider.isActive && hasIntersection(currentDumamicObjectToCheck, newPosition, currentObjectCollider, currentObjectToCheck->getCurrentPosition()))
								{
									hasCollision = true;
									if (currentObjectCollider.onCollisionCallback)
									{
										currentObjectCollider.onCollisionCallback(*currentDunamicObject, objectCollisionDirection);
									}
									if (currentDumamicObjectToCheck.onCollisionCallback)
									{
										currentDumamicObjectToCheck.onCollisionCallback(*currentObjectToCheck, dunaicObjectCollisionDirection);
									}

								}
							}
						}
					}
				}
				if (!hasCollision)
				{
					currentDunamicObject->getCurrentPosition() = newPosition;
				}
				else
				{
					if (currentDunamicObject->getCurrentDirection().x != 0.f)
					{
						currentDunamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDunamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f, currentDunamicObject->getCurrentPosition().y);
					}
					else if (currentDunamicObject->getCurrentDirection().y != 0.f)
					{
						currentDunamicObject->getCurrentPosition() = glm::vec2(currentDunamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDunamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
					}
				}

			}
		}
	}

	void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}

	void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel)
	{
		m_pCurrentLevel.swap(pLevel);
	}
	bool PhysicsEngine::hasIntersection(const Collider& collider1, const glm::vec2& position1, const Collider& collider2, const glm::vec2& position2)
	{
		const glm::vec2 currentColider1_bottomLeft_world = collider1.boundingBox.bottomLeft + position1;
		const glm::vec2 currentColider1_topRight_world = collider1.boundingBox.topRight + position1;
		
			const glm::vec2 currentColider2_bottomLeft_world = collider2.boundingBox.bottomLeft + position2;
			const glm::vec2 currentColider2_topRight_world = collider2.boundingBox.topRight + position2;
			if (currentColider1_bottomLeft_world.x >= currentColider2_topRight_world.x)
			{
				return false;

			}
			if (currentColider1_topRight_world.x <= currentColider2_bottomLeft_world.x)
			{
				return false;
			}

			if (currentColider1_bottomLeft_world.y >= currentColider2_topRight_world.y)
			{
				return false;

			}
			if (currentColider1_topRight_world.y <= currentColider2_bottomLeft_world.y)
			{
				return false;
			}
			return true;
			
    }
}