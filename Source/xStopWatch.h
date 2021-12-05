#pragma once

#include "stdafx.h"

class xStopWatch
{
public:
	xStopWatch()
	{
		m_running = false;
	}
	~xStopWatch()
	{
	}

	void Start()
	{
		if (m_running)
		{
			return;
		}
		m_running = true;
		m_startTime = chrono::system_clock::now();
	}

	void Stop()
	{
		if (m_running == false)
		{
			return;
		}

		m_endTime = chrono::system_clock::now();
	}

	void Reset()
	{
		m_running = false;
	}

	long long ElapseMillisecond()
	{
		auto value = m_endTime.time_since_epoch();
		if (value.count() <= 0)
		{
			auto result = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - m_startTime);
			return result.count();
		}

		auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime);
		return elapse.count();
	}

private:
	bool m_running;
	chrono::system_clock::time_point m_startTime;
	chrono::system_clock::time_point m_endTime;
};