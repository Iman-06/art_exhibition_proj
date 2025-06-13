#ifndef FILE_IO_EXCEPTION_H
#define FILE_IO_EXCEPTION_H
#include "exception.h"
class FileIOException : public Exception {
private:
    MyString fileName;

public:
    FileIOException(const MyString& msg, int code, const MyString& file);
    MyString getFileName() const;
};
#endif 
