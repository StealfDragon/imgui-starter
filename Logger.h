#pragma once
#include <string>
#include <vector>
#include <fstream>

enum LogType {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
    public:
        static Logger& GetInstance();

        //void LogInfo(const std::string& message, bool gameType = false);
        void LogInfo(const std::string& message, const std::string& category = "SYSTEM");
        void LogWarning(const std::string& message, const std::string& category = "SYSTEM");
        void LogError(const std::string& message, const std::string& category = "SYSTEM");

        static std::string getTime();
        void DrawConsole();

    private:
        Logger() = default;

        void WriteToFile(const std::string& message, LogType type, const std::string& category, const std::string& time);
        
        std::vector<std::string> logMessages;
        std::vector<LogType> logTypes;
};