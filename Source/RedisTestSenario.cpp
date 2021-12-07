#include "stdafx.h"
#include "RedisTestSenario.h"
#include "xStopWatch.h"
#include "RandomInt.h"


RedisTestSenario::RedisTestSenario()
{
    m_runThreadLoopTest = false;
}

RedisTestSenario::~RedisTestSenario()
{
    Stop();
}

void RedisTestSenario::Setup(const string& address, const unsigned int port, int threadPool)
{
    m_rediClient = std::make_shared<cppRedis>();
    m_rediClient->Initialize(address, port, threadPool);
}

void RedisTestSenario::StartUnitTest()
{
    Log("start unit test");
    UnitTest();
}

void RedisTestSenario::StartThreadLoopTest()
{
    Log("start ThreadLoop test");
    ThreadLoop();
}

void RedisTestSenario::Stop()
{
    m_runThreadLoopTest = false;
    StopThreadLoop();
}

void RedisTestSenario::StopThreadLoop()
{
    if (m_threadVector.size() > 0)
    {
        for (int i = 0; i < m_threadVector.size(); ++i)
        {
            m_threadVector[i]->join();
        }

        m_threadVector.clear();
    }
}

int RedisTestSenario::GetThreadTestCount()
{
    return m_threadVector.size();
}

void RedisTestSenario::UnitTest()
{
    int testCount = 10000;
    SenarioStringSet(testCount);
    SenarioStringGet(testCount);
    SenarioStringTTL(testCount);
    SenarioStringSet(testCount);
    SenarioStringDel(testCount);
}

void RedisTestSenario::ThreadLoop()
{
    m_runThreadLoopTest = true;
    
    m_threadVector.push_back(SenarioStringSetThreadLoop());
    m_threadVector.push_back(SenarioStringGetThreadLoop());
    m_threadVector.push_back(SenarioStringTTLThreadLoop());
}

void RedisTestSenario::Log(const string_view& message)
{
    std::cout << message << std::endl;
}

void RedisTestSenario::SenarioStringSet(int testCount)
{
	xStopWatch stopWatch;
	stopWatch.Start();
	for (int i = 0; i < testCount; ++i)
	{
		auto value = to_string(i);
		if (m_rediClient->StringSet(value, value) == false)
		{
			Log(format("StringSet Fail. Key: {}", i));
		}
	}

	stopWatch.Stop();
	Log(format("SenarioStringSet End. Count: {} Elapse = {}ms", testCount, stopWatch.ElapseMillisecond()));
}
	
void RedisTestSenario::SenarioStringGet(int testCount)
{
	xStopWatch stopWatch;
	stopWatch.Start();
	for (int i = 0; i < testCount; ++i)
	{
		auto getResult = m_rediClient->StringGet(to_string(i));
		if (getResult.empty())
		{
			Log(format("StringGet Empty Error. Key: {}", i));
		}
	}

	stopWatch.Stop();
	Log(format("SenarioStringGet End. Count: {} Elapse = {}ms", testCount, stopWatch.ElapseMillisecond()));
}

void RedisTestSenario::SenarioStringDel(int testCount)
{
	xStopWatch stopWatch;
	stopWatch.Start();

	for (int i = 0; i < testCount; ++i)
	{
		auto value = to_string(i);
		if (m_rediClient->StringDel(value) == false)
		{
			Log(std::format("StringDelTest Del fail. Key: {}", i));
		}
	}

	stopWatch.Stop();
	Log(format("SenarioStringDel End. Count: {} Elapse = {}ms", testCount, stopWatch.ElapseMillisecond()));
}


void RedisTestSenario::SenarioStringTTL(int testCount)
{
	xStopWatch stopWatch;
	stopWatch.Start();

	for (int i = 0; i < testCount; ++i)
	{
		auto value = to_string(i);
		if (m_rediClient->StringSet(value, value, chrono::milliseconds(1)) == false)
		{
			Log(format("StringSetTTL Set Fail. Key: {}", i));
		}
	}

	this_thread::sleep_for(chrono::microseconds(1));

	for (int i = 0; i < testCount; ++i)
	{
		auto value = to_string(i);
		auto getResult = m_rediClient->StringGet(value);
		if (getResult.empty() == false)
		{
			Log(format("StringSetTTL TTL Fail. Not Empty. Key: {}", i));
		}
	}

	stopWatch.Stop();
	Log(format("SenarioStringTTL End. Count: {} Elapse = {}ms", testCount, stopWatch.ElapseMillisecond()));
}

shared_ptr<thread> RedisTestSenario::SenarioStringSetThreadLoop()
{
    return make_shared<thread>([this]
    {
        Log(format("SenarioStringSetThreadLoop Start. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));

        RandomInt rand{ 0, 10000 };
        while (m_runThreadLoopTest)
        {
            auto keyAndValue = to_string(rand());
            m_rediClient->StringSet(keyAndValue, keyAndValue);
        }

        Log(format("SenarioStringSetThreadLoop Stop. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));
    });
}

shared_ptr<thread> RedisTestSenario::SenarioStringGetThreadLoop()
{
    return make_shared<thread>([this]
    {
        Log(format("SenarioStringGetThreadLoop Start. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));

        RandomInt rand{ 0, 10000 };
        while (m_runThreadLoopTest)
        {
            m_rediClient->StringGet(to_string(rand()));
        }

        Log(format("SenarioStringGetThreadLoop Stop. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));
    });
}

shared_ptr<thread> RedisTestSenario::SenarioStringTTLThreadLoop()
{
    return make_shared<thread>([this]
    {
        Log(format("SenarioStringTTLThreadLoop Start. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));

        RandomInt rand{ 0, 10000 };
        while (m_runThreadLoopTest)
        {
            auto keyAndValue = to_string(rand());
            m_rediClient->StringSet(keyAndValue, keyAndValue, chrono::milliseconds(1));
        }

        Log(format("SenarioStringTTLThreadLoop Stop. ThreadId: {}", std::hash<std::thread::id>()(std::this_thread::get_id())));
    });
}