#ifndef ODIS_ECS_TYPEID_HPP
#define ODIS_ECS_TYPEID_HPP

namespace odis
{
	namespace detail
	{
		template <typename T>
		static constexpr void unique_address() noexcept { }
	}

	// A unique compile time id for T

	struct type_id
	{
		constexpr type_id() noexcept : address{nullptr}
		{}

		friend constexpr bool operator==(const type_id&, const type_id&);

		template <typename T>
		friend constexpr type_id make_type_id();

		[[nodiscard]] constexpr auto size_bytes() noexcept { return sizeof(decltype(*this)); }
		[[nodiscard]] constexpr auto size_bytes() const noexcept { return sizeof(decltype(*this)); }

		template <typename T>
		T as()
		{
			return static_cast<T>(address);
		}

		auto operator&() const
		{
			return address;
		}

		void(*address)();
	private:

		constexpr explicit type_id(void(*address)()) noexcept : address{address}
		{}
	};

	constexpr bool operator == (const type_id& one, const type_id& two)
	{
		if (one.address == nullptr or two.address == nullptr)
			throw std::exception("Type id not set");
		return one.address == two.address;
	}

	template <typename T>
	[[nodiscard]] constexpr type_id make_type_id()
	{
		return type_id(&detail::unique_address<T>);
	}
}

/*
template <>
struct std::formatter<odis::type_id> : std::formatter<std::string>
{
	auto format(odis::type_id type_id, format_context& ctx) const
	{
		return formatter<string>::format(
		  std::format("{}", type_id), ctx);
	}
};
*/

#endif //ODIS_ECS_TYPEID_HPP
