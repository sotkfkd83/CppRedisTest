#pragma once

#include "cppRedis.h"

class RedisTestSenario
{
public:
	RedisTestSenario();
	~RedisTestSenario();

	void Setup(const string& address, const unsigned int port, int threadPool);

	void StartUnitTest();
	void StartThreadLoopTest();
	void Stop();

	int GetThreadTestCount();
private:
	shared_ptr<cppRedis> m_rediClient;
	vector<shared_ptr<thread>> m_threadVector;
	bool m_runThreadLoopTest;

protected:
	void Log(const string_view& message);
	void UnitTest();
	void ThreadLoop();
	void StopThreadLoop();
	void SenarioStringSet(int testCount);
	void SenarioStringGet(int testCount);
	void SenarioStringDel(int testCount);
	void SenarioStringTTL(int testCount);

	shared_ptr<thread> SenarioStringSetThreadLoop();
	shared_ptr<thread> SenarioStringGetThreadLoop();
	shared_ptr<thread> SenarioStringTTLThreadLoop();
};