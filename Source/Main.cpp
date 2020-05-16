#include <memory>

#include "Render/Renderer.hpp"
#include "Render/Terminal.hpp"
#include "Scene/ManagerScene.hpp"

using namespace Gen;

int main(int argc, char* argv[])
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Terminal>();

	ManagerScene managerScene(renderer);

	// Main Loop
	while (managerScene.isRunning())
	{
		managerScene.clear();
		managerScene.draw();
		managerScene.event();
		managerScene.update();
	}
}
