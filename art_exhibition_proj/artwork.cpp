#include "Artwork.h"
#include "Artist.h"
#include "Review.h"
#include "Logger.h"
#include "nullReferenceException.h"
#include "ImageLoadException.h"
#include "FileIOException.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
Artwork::Artwork()
    : artworkID(0), title(""), price(0.0f), medium(""), creationYear(0),
    createdBy(nullptr), status("Available") {
}

Artwork::Artwork(int id, const MyString& t, float p, const MyString& m, int year, Artist* artist, const MyString& path)
    : artworkID(id), title(t), price(p), medium(m), creationYear(year), createdBy(artist), status("Available"), imagePath(path) {}
Artwork::~Artwork() {
      imageData.release();  // frees image memory
    for (int i = 0; i < reviews.getLength(); i++) { 
        delete reviews[i];
    }
    reviews.clear(); 

}
const MyString& Artwork::getImagePath() const {
    return imagePath;
}

void Artwork::setImagePath(const MyString& path) {
    imagePath = path;
}
void Artwork::loadImageFromFile(const MyString& fileName) {
    Logger logger("log.txt");

    try {
        MyString baseFolder = "C:\\Users\\LENOVO\\source\\repos\\sem2_proj\\art_exhibition_proj\\art_exhibition_proj\\images\\";
        MyString fullPath = baseFolder.concat(fileName);

        imageData = cv::imread(fullPath.return_array());
        imagePath = fileName;
        if (imageData.empty()) {
            logger.logError("Failed to load image: " + fileName);
            throw ImageLoadException("Failed to load image", 101, fileName);
        }

        logger.logEvent("Image loaded successfully: " + fileName);
    }
    catch (const FileIOException& ex) {
        logger.logError("File I/O error in loadImageFromFile: " + ex.getFileName());
    }
}
void Artwork::displayImage() {
    Logger logger("log.txt");

    try {
        if (imageData.empty()) {
            logger.logError("No image loaded. displayImage() called on empty image.");
            cout << "No image to display." << endl;
            return;
        }

        cv::namedWindow("Artwork Image", cv::WINDOW_NORMAL);
        cv::Mat resizedImage;
        cv::resize(imageData, resizedImage, cv::Size(800, 600));
        cv::imshow("Artwork Image", resizedImage);
        logger.logEvent("Displayed artwork image successfully.");
        cv::waitKey(0);
    }
    catch (...) {
        logger.logError("Unknown error occurred in displayImage().");
    }
}

void Artwork::addReview(Review* review) {
    if (review) {
        reviews.push(review);
        Logger logger("log.txt");
        logger.logEvent("Review added for artwork: " + title + " with rating: " + MyString(review->getRating()));
        cout << "Review added successfully." << endl;
    }
    else
    {
		throw NullReferenceException("Review cannot be null", 300, "Review");//catch in main
    }
	
}

void Artwork::listReviews() {
    cout << "Reviews for " << title << ":" << endl;
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
Artist* Artwork::getCreatedBy() const { 
    if (createdBy) {
        return createdBy;
    }
    else {
        cout << "Artist: Unknown (deleted)" << endl;
        return nullptr;
    }
    }
void Artwork::setTitle(const MyString& t) { title = t; }
void Artwork::setPrice(float p) { price = p; }
void Artwork::setStatus(const MyString& s) { status = s; }
void Artwork::setMedium(const MyString& m) { medium = m; }
void Artwork::setCreationYear(int year) { creationYear = year; }
