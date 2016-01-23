#include "DrawSystem.h"
#include <iostream>

using namespace sf;

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

bool DrawSystem::Initialize()
{
	m_DrawComponents = ComponentManager<DrawComponent>::GetAll();
	m_TransformComponents = ComponentManager<TransformComponent>::GetAll();

	return true;
}

void DrawSystem::Shutdown()
{
}

void DrawSystem::Tick(deltaTime_t dt)
{
	m_pWindow->clear();
	(void)dt;
	// Iterate over all drawables and draw them
	/*
	for(size_t i = 0; i < m_DrawComponents.size(); ++i)
	{
		
	}
	*/
	m_pWindow->display();
}

