#pragma once

#include "cppRedis.h"

//TODO
//상속을 허용하지 않는다면 final 처리를 하시는것이 좋습니다
class RedisTestSenario 
{
//TODO
/*
인터페이스 노출 순서는
public 함수 변수,
protected 함수 변수,
private 함수 변수,
순이어야 합니다.

이유는 타인이 읽는 순서와 연관이 있습니다.
이 클래스를 사용하는 사람에게 필요한것은 public.
이 클래스를 상속받는 사람에게 필요한것은 protected.
이기 때문입니다. 언제가 가장 중요한것은 사용자 입니다.
*/

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