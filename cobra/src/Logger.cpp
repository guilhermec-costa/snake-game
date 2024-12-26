#include "Logger.h"
#include <iostream>

Logger::Logger() 
	: m_rawtime(new time_t), m_timeinfo(new tm)
{}
Logger& Logger::operator=(const Logger&) {
	return *this;
}

Logger::Logger(Logger const&)
	: m_rawtime(nullptr), m_timeinfo(nullptr)
{}

Logger& Logger::s_get_instance()
{
	static Logger* logger = new Logger();
	return *logger;
}

void Logger::log(string& msg)
{
	std::cout << "[INFO] >> " << msg << std::endl;
}

void Logger::log_err(string& msg)
{
	time(m_rawtime);
	struct tm tmp = *localtime(m_rawtime);
	*m_timeinfo = tmp;
	std::cerr << "[ERROR] >> " << msg << " at " << asctime(m_timeinfo) << std::endl;
}

Logger::~Logger()
{
	delete m_rawtime;
	delete m_timeinfo;
}