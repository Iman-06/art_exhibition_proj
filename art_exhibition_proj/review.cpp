#include "Review.h"
#include "Artwork.h"
#include <iostream>

Review::Review(int id, int r, const MyString& text, Artwork* art)
    : reviewID(id), rating(r), reviewText(text), artwork(art) {}

void Review::printReview() {
    std::cout << "Review ID: " << reviewID << std::endl;
    std::cout << "Rating: " << rating << "/5" << std::endl;
    std::cout << "Review: " << reviewText << std::endl;
    if (artwork) {
        std::cout << "Artwork: " << artwork->getTitle() << std::endl;
    }
    std::cout << "------------------------" << std::endl;
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