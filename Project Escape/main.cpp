#include "stdafx.h"
#include "Engine.h"

int _tmain(int argc, _TCHAR* argv[])
{
	esc::Engine engine;

	engine.initialize();
	engine.run();
	engine.cleanup();
}