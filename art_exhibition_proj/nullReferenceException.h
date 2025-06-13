#ifndef NULL_REFERENCE_EXCEPTION_H
#define NULL_REFERENCE_EXCEPTION_H
#include "exception.h"
class NullReferenceException : public Exception {
private:
    MyString objectName;

public:
    NullReferenceException(const MyString& msg, int code, const MyString& objName);
    MyString getObjectName() const;
};

#endif
