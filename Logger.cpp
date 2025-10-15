#include "Logger.h"
#include "imgui/imgui.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::LogInfo(const std::string& message, const std::string& category) {
    std::string msg = "[" + getTime() + "] [" + "INFO" + "] [" + category + "] " + message;
    logMessages.push_back(msg);
    logTypes.push_back(LogType::INFO);
    WriteToFile(message, LogType::INFO, category, getTime());
}

void Logger::LogWarning(const std::string& message, const std::string& category) {
    std::string msg = "[" + getTime() + "] [" + "WARN" + "] [" + category + "] " + message;
    logMessages.push_back(msg);
    logTypes.push_back(LogType::WARN);
    WriteToFile(message, LogType::WARN, category, getTime());
}

void Logger::LogError(const std::string& message, const std::string& category) {
    std::string msg = "[" + getTime() + "] [" + "ERROR" + "] [" + category + "] " + message;
    logMessages.push_back(msg);
    logTypes.push_back(LogType::ERROR);
    WriteToFile(message, LogType::ERROR, category, getTime());
}

void Logger::WriteToFile(const std::string& message, LogType type, const std::string& category, const std::string& time) {
    std::ofstream file("/Users/Cassian/School_Local/CMPM_123/Week2/imgui-starter/log.txt", std::ios::app);
    if (!file.is_open()) return;

    std::string typeStr;
    switch (type) {
        case LogType::INFO:  typeStr = "INFO";  break;
        case LogType::WARN:  typeStr = "WARN";  break;
        case LogType::ERROR: typeStr = "ERROR"; break;
        case LogType::DEBUG: typeStr = "DEBUG"; break;
    }

    file << "[" << time << "][" << category << "][" << typeStr << "] " << message << std::endl;
}

std::string Logger::getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_c);

    std::ostringstream ss;
    ss << std::put_time(&local_tm, "%H:%M:%S"); // Format as HH:MM:SS
    return ss.str();
}

void Logger::DrawConsole() {
    //ImGui::Text("Testing game log window");
    if (ImGui::Button("Clear")) {
        logMessages.clear();
        logTypes.clear();
    }
    ImGui::SameLine(); 
    if (ImGui::Button("Test Info")) {
        LogInfo("This is a test info message");
    }
    ImGui::SameLine(); 
    if (ImGui::Button("Test Warning")) {
        LogWarning("This is a test warning message");
    }
    ImGui::SameLine(); 
    if (ImGui::Button("Test Error")) {
        LogError("This is a test error message");
    }
    ImGui::Separator();

    ImGui::BeginChild("LogRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (size_t i = 0; i < logMessages.size(); ++i) {
        ImVec4 color;
        switch (logTypes[i]) {
            case LogType::INFO:  color = ImVec4(1, 1, 1, 1); break;       // White
            case LogType::WARN:  color = ImVec4(1, 1, 0.4f, 1); break;    // Yellowish
            case LogType::ERROR: color = ImVec4(1, 0.4f, 0.4f, 1); break; // Redish
            case LogType::DEBUG: color = ImVec4(0.6f, 0.8f, 1, 1); break; // Blueish
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(logMessages[i].c_str());
        ImGui::PopStyleColor();
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
}