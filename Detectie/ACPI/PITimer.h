#pragma once
#include <chrono>

class PITimer
{
	std::chrono::time_point<std::chrono::system_clock> st, en;
public:

	void start()
	{
		st = std::chrono::system_clock::now();
	}

	void stop()
	{
		en = std::chrono::system_clock::now();
	}

	double elapsed()
	{
		auto sec = std::chrono::duration_cast<std::chrono::duration<double>>(en - st);
		return sec.count();
	}
};