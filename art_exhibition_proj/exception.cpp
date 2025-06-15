#include "Exception.h"
using namespace std;

Exception::Exception(const MyString& msg, int code) : message(msg), errorCode(code) {}

MyString Exception::getMessage() const {
    return message;
}

int Exception::getErrorCode() const {
    return errorCode;
}