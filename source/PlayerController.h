#pragma once

#include <UnigineComponentSystem.h>

class PlayerController final : public Unigine::ComponentBase {
	COMPONENT_DEFINE(PlayerController, Unigine::ComponentBase);
	COMPONENT_INIT(initialize);
	COMPONENT_UPDATE(update)

private:
	void initialize();
	void update();
};