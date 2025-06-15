#ifndef ARTWORK_H
#define ARTWORK_H

#include "My_string.h"
#include "Dynamic_array.h"
#include "Exception.h"
#include <opencv2/opencv.hpp>
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
    // The Artist object must remain alive as long as any Artwork references it.
    Artist* createdBy; //association
    MyString imagePath;
    cv::Mat imageData;
    Dynamic_array<Review*> reviews;


public:
    Artwork();
    Artwork(int id, const MyString& t, float p, const MyString& m, int year, Artist* artist, const MyString& path);
    ~Artwork();
    const MyString& getImagePath() const;
    void setImagePath(const MyString& path);
    Artwork(const Artwork&) = delete; //artworks are unique
    Artwork& operator=(const Artwork&) = delete;
    void loadImageFromFile(const MyString& fileName); // throws ImageLoadException
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
	void setMedium(const MyString& m);
	void setCreationYear(int year);
	void setArtworkID(int id) { artworkID = id; }
};

#endif
