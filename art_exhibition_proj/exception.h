#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "My_string.h"
class Exception {
protected:
    MyString message;
    int errorCode;

public:
    Exception(const MyString& msg, int code);
    virtual ~Exception() = default;

    MyString getMessage() const;
    int getErrorCode() const;
};
#endif