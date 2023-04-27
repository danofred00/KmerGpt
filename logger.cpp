#include "logger.h"

#include <iostream>
#include <fstream>
#include <string>

Logger::Logger()
{
    // set default value of our stream to std::cout
}

void Logger::log(const std::string & msg, ILogLevel level)
{
    if(stream) {
        stream << '[' << logLevel2Str(level) << ']';
        stream << " " << msg << std::endl;
    } else
    {
        std::cout << '[' << logLevel2Str(level) << ']';
        std::cout << " " << msg << std::endl;
    }

}

Logger * Logger::toFile(const std::string & filename)
{
    // declarations
    Logger * logger;

    // init vars
    logger = new Logger();

    // create file if is not exists
    FILE * fp = std::fopen(filename.c_str(), "a+");
    if(fp)
        std::fclose(fp);

    logger->stream.open(filename, std::ios_base::in);

    // update stream
    if(!logger->stream.is_open())
        std::cout << "[ERROR] unable to open a file : " << filename << std::endl;

    return logger;
}

std::string Logger::logLevel2Str(ILogLevel level)
{
    switch(level)
    {
    case ILogLevel::DEBUG: return "DEBUG";
    case ILogLevel::CRITICAL: return "CRITICAL";
    case ILogLevel::ERROR: return "ERROR";
    case ILogLevel::WARNING: return "WARNING";
    default: return "UNKNOW";
    }
}

void Logger::d(const std::string & msg)
{
    log(msg, ILogLevel::DEBUG);
}

void Logger::w(const std::string & msg)
{
    log(msg, ILogLevel::WARNING);
}

void Logger::e(const std::string & msg)
{
    log(msg, ILogLevel::ERROR);
}

void Logger::c(const std::string & msg)
{
    log(msg, ILogLevel::CRITICAL);
}
