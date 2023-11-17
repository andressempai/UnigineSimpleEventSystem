#pragma once

#include <UnigineComponentSystem.h>

class EnemyController final : public Unigine::ComponentBase {
	COMPONENT_DEFINE(EnemyController, Unigine::ComponentBase);
	COMPONENT_INIT(initialize);

private:
	void initialize();
};