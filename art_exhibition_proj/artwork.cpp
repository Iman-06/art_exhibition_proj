#include "Artwork.h"
#include "Artist.h"
#include "Review.h"
#include <iostream>

Artwork::Artwork(int id, const MyString& t, float p, const MyString& m, int year, Artist* artist)
    : artworkID(id), title(t), price(p), medium(m), creationYear(year), createdBy(artist), status("Available") {}
Artwork::~Artwork() {
    //  imageData.release();  // Frees image memory
      // Optionally clear other vectors if needed
    for (int i = 0; i < reviews.getLength(); i++) { 
        delete reviews[i];
    }
}

//void Artwork::loadImageFromFile(const MyString& path) {
//    try {
//        imageData = cv::imread(path.return_array());
//        if (imageData.empty()) {
//            throw ImageLoadException("Failed to load image", 100, path);
//        }
//    }
//    catch (const ImageLoadException& e) {
//        std::cerr << "Error loading image: " << e.getMessage() << " from " << e.getFilePath() << std::endl;
//        throw;
//    }
//}

//void Artwork::displayImage() {
//    if (!imageData.empty()) {
//        cv::imshow("Artwork: " + title.return_array(), imageData);
//        cv::waitKey(0);
//        cv::destroyAllWindows();
//    }
//    else {
//        std::cout << "No image data available for " << title << std::endl;
//    }
//}

void Artwork::addReview(Review* review) {
    if (review) {
        reviews.push(review);
    }
}

void Artwork::listReviews() {
    std::cout << "Reviews for " << title << ":" << std::endl;
    for (int i = 0; i < reviews.getLength(); i++) {
        reviews[i]->printReview();
    }
}

void Artwork::updatePrice(float newPrice) {
    if (newPrice > 0) {
        price = newPrice;
    }
}

float Artwork::getAverageRating() {
    if (reviews.getLength() == 0) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < reviews.getLength(); i++) {
        sum += reviews[i]->getRating();
    }
    return sum / reviews.getLength();
}

bool Artwork::isAvailableForSale() {
    return status == "Available";
}
int Artwork::getArtworkID() const { return artworkID; }
MyString Artwork::getTitle() const { return title; }
float Artwork::getPrice() const { return price; }
MyString Artwork::getMedium() const { return medium; }
int Artwork::getCreationYear() const { return creationYear; }
MyString Artwork::getStatus() const { return status; }
Artist* Artwork::getCreatedBy() const { return createdBy; }
void Artwork::setTitle(const MyString& t) { title = t; }
void Artwork::setPrice(float p) { price = p; }
void Artwork::setStatus(const MyString& s) { status = s; }
