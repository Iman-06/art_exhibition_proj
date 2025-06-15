#include "imageLoadException.h"
using namespace std;

ImageLoadException::ImageLoadException(const MyString& msg, int code, const MyString& path)
    : Exception(msg, code), filePath(path) {}

MyString ImageLoadException::getFilePath() const {
    return filePath;
}