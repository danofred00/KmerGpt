#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class ILogger
{
public:

    enum ILogLevel {DEBUG, CRITICAL, WARNING, ERROR};
    virtual void log(const std::string & msg, ILogLevel level = ILogLevel::DEBUG) = 0;
    virtual void d(const std::string & msg) = 0;
    virtual void w(const std::string & msg) = 0;
    virtual void e(const std::string & msg) = 0;
    virtual void c(const std::string & msg) = 0;

private:
    virtual std::string logLevel2Str(ILogLevel level) = 0;

};

class Logger : public ILogger {
public:
    Logger();
    static Logger * toFile(const std::string & filename);

    void log(const std::string & msg, ILogLevel level = ILogLevel::DEBUG) override;
    void d(const std::string & msg) override;
    void w(const std::string & msg) override;
    void e(const std::string & msg) override;
    void c(const std::string & msg) override;
private:
    std::string logLevel2Str(ILogLevel level) override;
    std::ofstream stream;
};


#endif // LOGGER_H
