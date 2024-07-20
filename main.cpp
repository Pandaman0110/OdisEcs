#include <functional>
#include <iostream>
#include <print>
#include <thread>

#include "world.hpp"


struct position
{
	float x, y;
};

struct velocity
{
	float x, y;
};

int main()
{
    std::cout << "odis ecs test\n";

	std::cout << "Number of real cores: " << std::jthread::hardware_concurrency() << std::endl;
	std::cout << "Size of L1 cache line: " << std::hardware_constructive_interference_size << std::endl;

	std::cout << "Alignment of: " << alignof(nullptr_t) << std::endl;

	//std::cout << (sizeof(uint32_t) *  std::numeric_limits<uint32_t>::max()) / 1024 / 1024 / 1024 << std::endl;

	std::cout <<  sizeof(std::array<uint16_t, std::numeric_limits<uint16_t>::max()>) / 1024  << std::endl;

	auto allocator = std::allocator<std::byte>{};

	constexpr auto buffer_size = 64;

    auto buffer = allocator.allocate(buffer_size);

	std::cout << &buffer << std::endl;

	auto* int_ptr = new(buffer) uint32_t[buffer_size / sizeof(uint32_t)]{};

	int_ptr[15] = 5;

	std::cout << int_ptr[1] << std::endl;

	allocator.deallocate(buffer, 64);

	odis::world world;

	world.emplace_back(position{0.0f, 0.0f}, velocity{0.0f, 0.0f});
	world.emplace_back(int{0});
	world.emplace_back(velocity{1.0f, 0.0f}, float{});
	world.emplace_back(int{3});



    return 0;

}
