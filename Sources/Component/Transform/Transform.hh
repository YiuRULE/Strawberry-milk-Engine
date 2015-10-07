#pragma once

#include "../../../engine/Component/Component.hh"
#include "Vector2.hh"

class Transform : public StrawberryMilk::Component::Component, public IJsonSerializable
{
public:
	Transform();
	Transform(StrawberryMilk::Component::Type::IDComponent id);
	virtual ~Transform();
	Transform(Transform const &&) = delete;
	Transform(Transform const &) = delete;
	void operator=(Transform const &) = delete;

	// system loop
public:
	virtual void init(std::string const &);
	virtual void update();
	virtual void destroy();

public:
	virtual void Serialize(Json::Value &root)
	{
		
	}

	virtual void Deserialize(Json::Value &root)
	{
		m_position.x = root["Position"]["x"].asFloat();
		m_position.y = root["Position"]["y"].asFloat();

		printf("%f %f\n", m_position.x, m_position.y);
	}

public:
	StrawberryMilk::Math::Vector2 &Position() { return m_position; };
	StrawberryMilk::Math::Vector2 &Rotation() { return m_rotation; };
	StrawberryMilk::Math::Vector2 &Scale() { return m_scale; };

private:
	StrawberryMilk::Math::Vector2 m_position;
	StrawberryMilk::Math::Vector2 m_rotation;
	StrawberryMilk::Math::Vector2 m_scale;
};