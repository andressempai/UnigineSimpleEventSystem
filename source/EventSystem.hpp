#ifndef __EVENT_SYSTEM_HPP__
#define __EVENT_SYSTEM_HPP__

#include <UnigineNode.h>

#include <unordered_map>
#include <functional>
#include <algorithm>

namespace DynVector {
	enum struct EventType {
			damage
		,	dead
	};

	struct Event {
		explicit Event(EventType type) noexcept : type_{ type } {}
		virtual ~Event() = default;

		EventType type_;
	};

	struct Damage : Event {
		Damage(Unigine::NodePtr damaged_node, int16_t amount) noexcept
			:	Event{ EventType::damage }
			,	damaged_node_{ damaged_node }
			,	amount_{ amount }
		{}

		Unigine::NodePtr damaged_node_;
		int16_t amount_;
	};

	struct Dead : Event {
		Dead(Unigine::NodePtr dead_node, Unigine::NodePtr killer) noexcept
			:	Event{ EventType::dead }
			,	dead_node_{ dead_node }
			,	killer_{ killer }
		{}

		Unigine::NodePtr dead_node_;
		Unigine::NodePtr killer_;
	};

	using Callback = std::function<void(const Event&)>;
	using EventData = std::pair<EventType, Callback>;

	[[nodiscard]] EventData make_event(const EventType type, Callback callback) noexcept
	{
		return std::make_pair(type, std::move(callback));
	}

	class EventSystem {
		EventSystem() = default;
		~EventSystem() = default;
	
	public:
		EventSystem(const EventSystem&) = delete;
		EventSystem(EventSystem&&) = delete;
	
		EventSystem& operator=(const EventSystem&) = delete;
		EventSystem& operator=(EventSystem&&) = delete;
	
		static EventSystem& instance() noexcept
		{
			static EventSystem event_system{};
	
			return event_system;
		}
	
		void subscribe(int id, EventData event)
		{
			events_.insert(std::make_pair(id, std::move(event)));
		}

		void unsubscribe(int id, EventType event_type)
		{
            for (auto [begin, end] = events_.equal_range(id); begin != end; ++begin) {
                if (auto [type, _] = begin->second; type == event_type) {
					events_.erase(begin);
					break;
				}
			}
		}

		void send(int id, const Event& event)
		{
			for (auto [begin, end] = events_.equal_range(id); begin != end; ++begin)
				if (auto [type, function] = begin->second; type == event.type_)
					function(event);
		}

	private:
		std::unordered_multimap<int, EventData> events_{};
	};
}

#endif	// !__EVENT_SYSTEM_HPP__