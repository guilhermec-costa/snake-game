#pragma once
#include <ctime>
#include <iostream>

using string = std::string;

class Logger
{
private:
	Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	~Logger();
public:
	static Logger& s_get_instance();
	void log(string&);
	void log_err(string&);
private:
	time_t* m_rawtime;
	struct tm* m_timeinfo;
};
