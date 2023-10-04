#ifndef _INTERNAL_LOGGING_H
#define _INTERNAL_LOGGING_H

#include "system.hpp"
#include <iostream>

namespace debug
{
    class Logger : public core::System
    {
    public:
        Logger(const char* name);
        ~Logger();

        void Info(const char* message);
        void Error(const char* message);
        void Warn(const char* message);

        void LogMessage(const char* message, const char* level);
    };

}

#ifdef _DEBUG
    #define LOG_INFO(x) std::cout << "[INFO] : " << x << "\n";
    #define LOG_WARN(x) std::cout << "[WARN] : " << x << "\n";
#else
    #define LOG_WARN(x) std::cout << "[WARN] : " << x;
#endif



#endif
