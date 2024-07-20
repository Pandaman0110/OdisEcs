#ifndef ODIS_ECS_COMPONENT_HPP
#define ODIS_ECS_COMPONENT_HPP

#include <type_traits>

namespace odis
{
	namespace concepts
	{
		template <typename T>
		concept component = requires(T component)
		{
			{ std::is_aggregate_v<T> };
		};
	}


}

#endif //ODIS_ECS_COMPONENT_HPP
