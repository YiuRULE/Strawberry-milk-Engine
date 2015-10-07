#include "Physic.hh"

namespace HeroesSoul
{
	extern "C"
	{
		__declspec(dllexport) StrawberryMilk::System *create(void)
		{
			return dynamic_cast<StrawberryMilk::System *>(new PhysicSystem);
		}
	}

	PhysicSystem::PhysicSystem()
	{
		std::cout << "Construct" << std::endl;
	}

	PhysicSystem::~PhysicSystem()
	{
		std::cout << "Destruct" << std::endl;
	}

	void PhysicSystem::init(StrawberryMilk::Engine *)
	{
		std::cout << "Init" << std::endl;
	}

	void PhysicSystem::update(StrawberryMilk::Engine *engine, std::chrono::duration<double>)
	{
		for (auto entity = m_entities.begin(); entity != m_entities.end(); ++entity)
		{
			try
			{
				auto entityNext = entity;
				++entityNext;

				for (; entityNext != m_entities.end(); ++entityNext)
				{
					//CompareEntities(*entity, *entityNext, engine);
				}
			}
			catch (...)
			{
				//LOGGING FOR BAD ENTITY (NO RIGIDBODY)
			}
		}
	}

	void PhysicSystem::destroy(StrawberryMilk::Engine *)
	{

	}

	bool PhysicSystem::registerEntity(StrawberryMilk::Entity::ID entity)
	{
		std::cout << "ADDED TO PHYSIC SYSTEM" << std::endl;

		m_entities.push_back(entity);
		return (true);
	}

	void PhysicSystem::CompareEntities(StrawberryMilk::Entity::ID entity, StrawberryMilk::Entity::ID collisionCandidate, StrawberryMilk::Engine *engine)
	{
		RigidBody *body[2];
		Transform *transform[2];
		int test = 0;

		body[0] = engine->getComponentFromEntity<RigidBody>(entity);
		transform[0] = engine->getComponentFromEntity<Transform>(entity);

		body[1] = engine->getComponentFromEntity<RigidBody>(collisionCandidate);
		transform[1] = engine->getComponentFromEntity<Transform>(collisionCandidate);

		test += body[0]->IsCircle() ? -1 : 1;
		test += body[1]->IsCircle() ? -1 : 1;

		if (test == 0)
		{
			if (body[0]->IsCircle())
			{
				RigidBody *swapBody = body[0];
				Transform *swapTransform = transform[0];

				body[0] = body[1];
				body[1] = swapBody;
				transform[0] = transform[1];
				transform[1] = swapTransform;
			}
			if (CompareRectCircle(body, transform))
			{

			}
		}
		else if (test == -2)
		{
			if (CompareCircles(body, transform))
			{

			}
		}
		else
		{
			if (CompareRects(body, transform))
			{
				//SEND MESSAGE TO COLLIDING RECTS
			}
		}
	}

	bool PhysicSystem::CompareRects(RigidBody **body, Transform **transform)
	{
		Square square1(body[0], transform[0]);
		Square square2(body[0], transform[0]);

		return (square1.ResolveCollision(square2));
	}

	bool PhysicSystem::CompareCircles(RigidBody **, Transform **)
	{
		return (false);
	}

	bool PhysicSystem::CompareRectCircle(RigidBody **, Transform **)
	{
		return (false);
	}

	Square::Square(RigidBody *body, Transform *transform)
	{
		min = body->GetDimensions() / 2;
		max = min;

		min -= transform->Position();
		max += transform->Position();
	}

	bool Square::ResolveCollision(const Square &square2)
	{
		if (max.x < square2.min.x || min.x > square2.max.x) return false;
		if (max.y < square2.min.y || min.y > square2.max.y) return false;
		
		return true;
	}
};