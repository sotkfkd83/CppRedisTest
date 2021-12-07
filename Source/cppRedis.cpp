#include "stdafx.h"
#include "cppRedis.h"


cppRedis::cppRedis()
{
}

cppRedis::~cppRedis()
{
}

void cppRedis::Initialize(const string& address, const int port, const size_t poolSize)
{
	ConnectionOptions option;
	option.host = address;
	option.port = port;
	option.db = 0;
	//option.password = "auth";   // Optional. No password by default.
	
	ConnectionPoolOptions poolOption;
	poolOption.size = poolSize;
	// 풀이 최대 상태일때 얼마나 대기할지...
	poolOption.wait_timeout = chrono::milliseconds(1000);
	// 라이프사이클은 계속 연결로...
	//poolOption.connection_lifetime = std::chrono::minutes(10);

	Initialize(option, poolOption);
}

void cppRedis::Initialize(const ConnectionOptions& option, const ConnectionPoolOptions& poolOption)
{
	m_connectionContext = make_shared<Redis>(Redis(option));
}

shared_ptr<Redis>& cppRedis::CreateRedis(int databaase)
{
	_ASSERT(m_connectionContext);
	return m_connectionContext;
}

void cppRedis::Log(const string_view& mesage)
{
	cout << mesage << endl;
}

bool cppRedis::TryConnection()
{
	try
	{
		auto redis = cppRedis::CreateRedis();
		auto pingRespnse = redis->ping();
		return pingRespnse._Equal("PONG");
	}
	catch (const Error& err)
	{
		Log(err.what());
	}
	return false;
}

bool cppRedis::StringSet(const string_view& key, const string_view& value, const chrono::milliseconds& ttl)
{
	try
	{
		auto redis = CreateRedis();
		return redis->set(key, value, ttl);
	}
	catch (const Error& err)
	{
		Log(err.what());
	}

	return false;
}

string cppRedis::StringGet(const string_view& key)
{
	try
	{
		auto redis = CreateRedis();
		auto getResult = redis->get(key);
		if (getResult.has_value())
		{
			return getResult.value();
		}
	}
	catch (const Error& err)
	{
		Log(err.what());
	}

	return "";
}

bool cppRedis::StringDel(const string_view& key)
{
	try
	{
		auto redis = CreateRedis();
		auto deleteResult = redis->del(key);
		return deleteResult > 0;
	}
	catch (const Error& err)
	{
		Log(err.what());
	}

	return false;
}

double cppRedis::SortedSetAdd(const string_view& key, const string_view& member, const double value)
{
	try
	{
		auto redis = CreateRedis();
		return redis->zincrby(key, value, member);
	}
	catch (const Error& err) 
	{
		Log(err.what());
	}
	return 0;
}

pair<long long, double> cppRedis::SortedSetGetRankAndScore(const string_view& key, const string_view& member, bool orderbydescending)
{
	long long rankResult = -1;
	double scoreResult = 0;
	try
	{
		auto redis = CreateRedis();
		auto pipe = redis->pipeline();
		auto replies = pipe.zrank(key, member).zscore(key, member).zcount(key, UnboundedInterval<double>{}).exec();

		auto rank = replies.get<OptionalLongLong>(0);
		if (rank.has_value())
		{
			rankResult = rank.value() + 1;
		}

		auto score = replies.get<OptionalDouble>(1);

		if (score.has_value())
		{
			scoreResult = score.value();
		}
		
		auto memberCount = replies.get<OptionalLongLong>(2);
		if (orderbydescending && memberCount.has_value())
		{
			rankResult = memberCount.value() - rankResult;
		}
	}
	catch (const Error& err)
	{
		Log(err.what());
	}
	return make_pair(rankResult, scoreResult);
}


long long cppRedis::SortedSetDel(const string_view& key, const string_view& member)
{
	try
	{
		auto redis = CreateRedis();
		return redis->zrem(key, member);
	}
	catch (const Error& err)
	{
		Log(err.what());
	}
	return 0;
}

void cppRedis::SortedSetGetScoreRange(const string_view& key, const double min, const double max, std::vector<std::pair<std::string, double>>& result)
{
	try
	{
		auto redis = CreateRedis();
		redis->zrangebyscore(key, BoundedInterval<double>(min, max, BoundType::CLOSED), std::back_inserter(result));
	}
	catch (const Error& err)
	{
		Log(err.what());
	}
}

void cppRedis::SortedSetGetRankRange(const string_view& key, const long long start, const long long end, std::vector<std::pair<std::string, double>>& result)
{
	try
	{
		auto redis = CreateRedis();
		redis->zrange(key, start, end, std::back_inserter(result));
	}
	catch (const Error& err)
	{
		Log(err.what());
	}
}