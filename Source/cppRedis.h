#pragma once

#include <sw/redis++/redis++.h>

using namespace std;
using namespace sw::redis;

class cppRedis
{
public:
	cppRedis();
	~cppRedis();

	void Initialize(const string& address, const int port, const size_t poolSize = 1000);
	void Initialize(const ConnectionOptions& option, const ConnectionPoolOptions& poolOption);
	bool TryConnection();
public:
	// string Command
	bool StringSet(const string_view& key, const string_view& value, const chrono::milliseconds& ttl = chrono::milliseconds(0));
	string StringGet(const string_view& key);
	bool StringDel(const string_view& key);

	// sortedSet
	double SortedSetAdd(const string_view& key, const string_view& member, const double value);
	pair<long long, double> SortedSetGetRankAndScore(const string_view& key, const string_view& member, bool orderbydescending = true);
	long long SortedSetDel(const string_view& key, const string_view& member);
	void SortedSetGetScoreRange(const string_view& key, const double min, const double max, std::vector<std::pair<std::string, double>>& result);
	void SortedSetGetRankRange(const string_view& key, const long long start, const long long end, std::vector<std::pair<std::string, double>>& result);
private:
	shared_ptr<Redis> m_connectionContext;
	shared_ptr<Redis>& CreateRedis(int databaase = 0);

	void Log(const string_view& mesage);
};

