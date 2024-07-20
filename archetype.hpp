#ifndef ODIS_ECS_ARCHETYPE_HPP
#define ODIS_ECS_ARCHETYPE_HPP

#include "entity.hpp"
#include "type_id.hpp"

namespace odis
{
	template <concepts::entity Entity, concepts::component ... Components>
	class archetype
	{
	public:
		using entity_type = Entity;

		constexpr archetype(const std::initializer_list<odis::type_id> type_ids) : component_types{type_ids}
		{

		}

		constexpr bool operator == (const archetype& one) const
		{
			return one.component_types == component_types;
		}

		constexpr void emplace_back(entity_type entity, Components&& ... components)
		{

		}

		template <concepts::component Component>
		[[nodiscard]] constexpr bool contains() const noexcept
		{
			constexpr auto type_id = make_type_id<Component>();
			return std::ranges::contains(component_types, type_id);
		}

		[[nodiscard]] constexpr bool contains(const type_id type_id) const noexcept
		{
			return std::ranges::contains(component_types, type_id);
		}
	private:
		std::vector<odis::type_id> component_types;

		std::vector<entity_type> entities;

	};


	template <concepts::entity Entity, concepts::component ... Components>
	constexpr archetype<Entity> make_archetype()
	{
		return archetype<Entity>{(make_type_id<Components>(), ...)};
	}

} // odis

#endif //ODISECS_ARCHETYPE_HPP
