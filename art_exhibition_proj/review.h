#ifndef REVIEW_H
#define REVIEW_H

#include "My_string.h"
class Artwork;

class Review {
private:
    int reviewID;
    int rating;
    MyString reviewText;
    Artwork* artwork;

public:
    Review(int id, int r, const MyString& text, Artwork* art);

    void printReview();
    int getReviewID() const;
    int getRating() const;
    MyString getReviewText() const;
    Artwork* getArtwork() const;
};

#endif
