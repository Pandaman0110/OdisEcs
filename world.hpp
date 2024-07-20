#ifndef ODIS_ECS_WORLD_HPP
#define ODIS_ECS_WORLD_HPP

#include <vector>
#include <algorithm>
#include <ranges>


#include "component.hpp"
#include "archetype.hpp"
#include "entity.hpp"
#include "type_id.hpp"


namespace odis
{
	inline constexpr auto max_archetypes = sizeof(uint8_t);
	inline constexpr auto max_component_types = sizeof(uint8_t);

	template <concepts::entity Entity = default_entity>
	class world
	{
	public:
		using entity_type = Entity;

		struct entity_reference
		{
			explicit entity_reference(entity_type id):
				world{this},
				id{id}
			{}

			world& world;
			entity_type id;

			
			[[nodiscard]] bool expired() const noexcept
			{
				return std::ranges::contains(world, id);
			}
		};


		using reference = entity_reference;
		using archetype_type = archetype<entity_type>;

		constexpr world() :
			the_archetypes{},
			component_types{}
		{}

		template <concepts::component ... Components>
		constexpr entity_type emplace_back(Components&& ... components) noexcept
		{
			// add any new components to our component type list
			(register_component<Components>(), ...);

			auto entity_id = next_entity_id();

			auto archetype = get_archetype<Components...>();
			//archetype.emplace_back(entity_id, std::forward<Components>(components)...);

			return {};
		}

		[[nodiscard]] constexpr std::size_t max_size() const noexcept { return std::numeric_limits<entity_type>::max(); }
	private:
		template <concepts::component Component>
		constexpr void register_component()
		{
			if (constexpr auto type_id = make_type_id<Component>(); !std::ranges::contains(component_types, type_id))
				component_types.emplace_back(type_id);
		}

		template <concepts::component ... Component>
		constexpr archetype_type& get_archetype()
		{
			auto archetype = make_archetype<entity_type, Component...>();

			auto iterator = std::ranges::find(the_archetypes, archetype);

			if (iterator != the_archetypes.end())
				return *iterator;

			the_archetypes.emplace_back(archetype);
			return the_archetypes.back();
		}

		//////////////////////////////

		std::vector<entity_type> the_entities;

		entity_type next_available_id{};
		constexpr entity_type next_entity_id() { return next_available_id++; }

		//////////////////////////////

		std::vector<archetype_type> the_archetypes;

		std::vector<odis::type_id> component_types;
	};
}

#endif //ODIS_ECS_WORLD_HPP
