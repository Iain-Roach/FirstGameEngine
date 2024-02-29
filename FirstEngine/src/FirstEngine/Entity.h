#pragma once

class Entity
{
public:
	// Constructor
	Entity() : m_id(0) {}
	Entity(size_t id) : m_id(id) {}

	// Add and Remove Components from the entity here? probably not

private:
	size_t m_id;
};

