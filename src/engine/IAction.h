#pragma once

#include "Base.h"
#include "EntityManager.h"
#include "InputConstants.h"

/**
 * @brief Interface for game actions.
 * 
 * Implemented as a functor. Thus, child classes should be
 * modifying the operator() to override functionality.
 */
class IAction
{
public:
	IAction(){}
	virtual ~IAction(){}

	virtual bool operator()() = 0;
};

