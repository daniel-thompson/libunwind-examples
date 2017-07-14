#include <functional>
#include <random>

auto bitgen = std::bind(std::uniform_int_distribution<int>(0,1), 
			std::mt19937());

int main()
{
	while (1) {
		auto bit = bitgen();
		(void) bit;
	}

	// not reached
	return 1;
}
