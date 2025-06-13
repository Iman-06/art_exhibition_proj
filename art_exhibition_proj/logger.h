#ifndef LOGGER_H
#define LOGGER_H

#include "My_string.h"

class Logger {
private:
    MyString logFilePath;

public:
    Logger(const MyString& path);
    void log(const MyString& message);
    void logError(const MyString& message);
    void logEvent(const MyString& message);
};

#endif