#include <chrono>
#include <iostream>

class Timer
{
	using clock_t = std::chrono::high_resolution_clock;
	using microseconds = std::chrono::microseconds;
public:
	Timer()
	: start_(clock_t::now())
	{
	}

	~Timer()
	{
 		const auto finish = clock_t::now();
		const auto us =
			std::chrono::duration_cast<microseconds>
		(finish - start_).count();
		std::cout << us << " us" << std::endl;
	}

private:
	const clock_t::time_point start_;
};

int main()
{
	Timer t;
	int maxRows = 5000, maxColumns = 6000;
	int array[maxRows][maxColumns];
	int Sum = 0;

	for(int j = 0; j < maxColumns; ++j)
		for(int i = 0; i < maxRows; ++i)
			Sum += array[i][j];
	std::cout << "I'm sub_by_columns program" << std::endl;

	return 0;
}

