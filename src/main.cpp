#include <iostream>
#include "base/Platform.h"
#include "system/EntityManager.h"
#include "game/TestComp.h"
#include "game/Game.h"

using namespace std;

int main()
{
	if(!programInitialize())
	{
		// @TODO - Log this error!
		return -1;
	}

	Game game;
	GameAttributes attributes(1600, 1200, "Tetrad " + VERSION_STRING, false, 8);
	if(!game.Initialize(attributes))
	{
		return -1;
	}
	
	game.Run();
	game.Shutdown();

	return 0;
}
