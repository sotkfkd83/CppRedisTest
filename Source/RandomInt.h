#pragma once

#include <random>

using namespace std;

using my_engine = default_random_engine;
using mydistribution = uniform_int_distribution<>;

class RandomInt
{
public:
	RandomInt(int low, int high) : 
		dist{low, high}
	{
	}
	~RandomInt()
	{
	}

	int operator()()  
	{
		return dist(re);
	}
	void seed(int s)
	{
		re.seed(s);
	}

private:
	default_random_engine re;
	uniform_int_distribution<> dist;
};