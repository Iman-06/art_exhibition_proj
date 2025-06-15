#include "logger.h"
#include "FileIOException.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;
Logger::Logger(const MyString& path) : logFilePath(path) {}

MyString getCurrentTimestamp() {
    char buffer[100];
    time_t now = time(0);
    tm timeStruct;
    localtime_s(&timeStruct, &now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeStruct);

    return MyString(buffer);
}

void Logger::log(const MyString& message) {
    try {
        ofstream file(logFilePath.return_array(), ios::app);
        if (!file.is_open()) {
            throw FileIOException( MyString("Failed to open log file for writing"),104, logFilePath);
        }
        file << "[LOG] " << getCurrentTimestamp().return_array() << ": " << message.return_array() << "\n";
        file.close();
    }
    catch (const FileIOException& ex) {
        cerr << "Logging failed: " << ex.getMessage().return_array() << endl;
    }
}

void Logger::logError(const MyString& message) {
    try {
        ofstream file(logFilePath.return_array(), ios::app);
        if (!file.is_open()) {
            throw FileIOException(MyString("Failed to open log file for writing"), 104, logFilePath);
        }
        file << "[ERROR] " << getCurrentTimestamp().return_array() << ": " << message.return_array() << "\n";
        file.close();
    }
    catch (const FileIOException& ex) {
        cerr << "Error logging failed: " << ex.getMessage().return_array() << endl;
    }
}

void Logger::logEvent(const MyString& message) {
    try {
        ofstream file(logFilePath.return_array(), ios::app);
        if (!file.is_open()) {
            throw FileIOException(MyString("Failed to open log file for writing"), 104, logFilePath);
        }
        file << "[EVENT] " << getCurrentTimestamp().return_array() << ": " << message.return_array() << "\n";
        file.close();
    }
    catch (const FileIOException& ex) {
        cerr << "Event logging failed: " << ex.getMessage().return_array() << endl;
    }
}
