#include "Logger.h"
#include <fstream>
#include <iostream>
#include <ctime>

Logger::Logger(const MyString& path) : logFilePath(path) {}

void Logger::log(const MyString& message) {
    std::ofstream file(logFilePath.return_array(), std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        char* timeStr = ctime(&now);
        file << "[LOG] " << timeStr << " - " << message << std::endl;
        file.close();
    }
}

void Logger::logError(const MyString& message) {
    std::ofstream file(logFilePath.return_array(), std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        char* timeStr = ctime(&now);
        file << "[ERROR] " << timeStr << " - " << message << std::endl;
        file.close();
    }
}

void Logger::logEvent(const MyString& message) {
    std::ofstream file(logFilePath.return_array(), std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        char* timeStr = ctime(&now);
        file << "[EVENT] " << timeStr << " - " << message << std::endl;
        file.close();
    }
}