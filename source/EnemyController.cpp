#include "EnemyController.hpp"
#include "EventSystem.hpp"

REGISTER_COMPONENT(EnemyController)

static void on_damage(const DynVector::Event& event) noexcept
{
	const auto damage_event = dynamic_cast<const DynVector::Damage&>(event);
	Unigine::Log::warning("%s that is an enemy take %d points of damage.\n", damage_event.damaged_node_->getName(), damage_event.amount_);
}

void EnemyController::initialize()
{
	DynVector::EventSystem::instance().subscribe(node->getID(), std::make_pair(DynVector::EventType::damage, on_damage));
}