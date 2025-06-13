#include "nullReferenceException.h"
NullReferenceException::NullReferenceException(const MyString& msg, int code, const MyString& objName)
    : Exception(msg, code), objectName(objName) {}

MyString NullReferenceException::getObjectName() const {
    return objectName;
}
