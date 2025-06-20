#include "duplicateArtworkException.h"
using namespace std;
DuplicateArtworkException::DuplicateArtworkException(const MyString& msg, int code, int id)
    : Exception(msg, code), artworkID(id) {}

int DuplicateArtworkException::getArtworkID() const {
    return artworkID;
}