#include "Review.h"
#include "Artwork.h"
#include <iostream>
using namespace std;

Review::Review(int id, int r, const MyString& text, Artwork* art)
    : reviewID(id), rating(r), reviewText(text), artwork(art) {}

void Review::printReview() {
    cout << "Review ID: " << reviewID << endl;
    cout << "Rating: " << rating << "/5" << endl;
    cout << "Review: " << reviewText << endl;
    if (artwork) {
        cout << "Artwork: " << artwork->getTitle() << endl;
    }
    cout << "------------------------" << endl;
}

int Review::getReviewID() const {
    return reviewID;
}

int Review::getRating() const {
    return rating;
}

MyString Review::getReviewText() const {
    return reviewText;
}

Artwork* Review::getArtwork() const {
    return artwork;
}