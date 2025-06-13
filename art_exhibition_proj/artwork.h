#ifndef ARTWORK_H
#define ARTWORK_H

#include "My_string.h"
#include "Dynamic_array.h"
#include "Exception.h"
//#include <opencv2/opencv.hpp>
class Artist;
class Review;

class Artwork {
private:
    int artworkID;
    MyString title;
    float price;
    MyString medium;
    int creationYear;
    MyString status;
    Artist* createdBy;
   // cv::Mat imageData;
    Dynamic_array<Review*> reviews;

public:
    Artwork(int id, const MyString& t, float p, const MyString& m, int year, Artist* artist);
    ~Artwork();
    Artwork(const Artwork&) = delete; //artworks are unique
    Artwork& operator=(const Artwork&) = delete;
    void loadImageFromFile(const MyString& path); // throws ImageLoadException
    void displayImage();
    void addReview(Review* review);
    void listReviews();
    void updatePrice(float newPrice);
    float getAverageRating();
    bool isAvailableForSale();
    int getArtworkID() const;
    MyString getTitle() const;
    float getPrice() const;
    MyString getMedium() const;
    int getCreationYear() const;
    MyString getStatus() const;
    Artist* getCreatedBy() const;
    void setTitle(const MyString& t);
    void setPrice(float p);
    void setStatus(const MyString& s);
};

#endif
