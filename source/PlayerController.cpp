#include "PlayerController.h"
#include "EventSystem.hpp"

#include <UnigineInput.h>

REGISTER_COMPONENT(PlayerController)

static void on_damage(const DynVector::Event& event) noexcept
{
	const auto damage_event = dynamic_cast<const DynVector::Damage&>(event);
	Unigine::Log::warning("%s take %d points of damage.\n", damage_event.damaged_node_->getName(), damage_event.amount_);
}

void PlayerController::initialize()
{
	using namespace DynVector;

	EventSystem::instance().subscribe(node->getID(), make_event(EventType::damage, on_damage));
}

void PlayerController::update()
{
	using namespace DynVector;

	if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON::MOUSE_BUTTON_RIGHT))
		EventSystem::instance().unsubscribe(node->getID(), EventType::damage);
}