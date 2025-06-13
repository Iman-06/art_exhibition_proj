#ifndef DUPLICATE_ARTWORK_EXCEPTION_H
#define DUPLICATE_ARTWORK_EXCEPTION_H
#include "exception.h"
class DuplicateArtworkException : public Exception {
private:
    int artworkID;

public:
    DuplicateArtworkException(const MyString& msg, int code, int id);
    int getArtworkID() const;
};
#endif 
