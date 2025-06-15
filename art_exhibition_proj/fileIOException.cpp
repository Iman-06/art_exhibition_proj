#include "fileIOException.h"
using namespace std;

FileIOException::FileIOException(const MyString& msg, int code, const MyString& file)
    : Exception(msg, code), fileName(file) {}

MyString FileIOException::getFileName() const {
    return fileName;
}