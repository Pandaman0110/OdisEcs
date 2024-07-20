#ifndef ODIS_ECS_ENTITY_HPP
#define ODIS_ECS_ENTITY_HPP

#include <cstdint>

namespace odis
{
	namespace concepts
	{
		template <typename T>
		concept entity = requires(T entity)
		{
			{ std::unsigned_integral<T> };
		};
	}

	using default_entity = uint8_t;

	template <concepts::entity Entity>
	[[nodiscard]] std::size_t max_entities() { return std::numeric_limits<Entity>::max(); }
}

#endif //ODIS_ECS_ENTITY_HPP
