#ifndef IMAGE_LOAD_EXCEPTION_H
#define IMAGE_LOAD_EXCEPTION_H
#include "exception.h"
class ImageLoadException : public Exception {
private:
    MyString filePath;

public:
    ImageLoadException(const MyString& msg, int code, const MyString& path);
    MyString getFilePath() const;
};
#endif 
