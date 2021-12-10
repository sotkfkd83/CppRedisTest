#pragma once

#include <random>

using namespace std;

//TODO
//사용하지 않는 using 은 권장 되지 않습니다.
using my_engine = default_random_engine;
using mydistribution = uniform_int_distribution<>;

class RandomInt
{
public:
	//TODO
	//Initialize list 는 외부 클래스에서도 마찬가지로 사용에 주의를 요합니다.
	//dist(low, high) 형태가 더욱 권장 됩니다.
	RandomInt(int low, int high) : 
		dist{low, high}
	{
	}

	//TODO
	// 생성자와 소멸자는 '= default' 명시적으로 비우기를 권장합니다
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