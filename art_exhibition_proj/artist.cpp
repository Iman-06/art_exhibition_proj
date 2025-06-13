#include "Artist.h"
#include "Artwork.h"
#include "duplicateArtworkException.h"
#include "ImageLoadException.h"
#include "Logger.h"
#include <iostream>

Artist::Artist(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int artId, const MyString& country, const MyString& style)
    : Person(personId, name, email, dob), artistID(artId), country(country), artStyle(style) {}

void Artist::displayInfo()const {
    std::cout << "Artist Information:" << std::endl;
    std::cout << "ID: " << personID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Date of Birth: " << dateOfBirth << std::endl;
    std::cout << "Artist ID: " << artistID << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Art Style: " << artStyle << std::endl;
    std::cout << "Number of Artworks: " << artworks.getLength() << std::endl;
}

void Artist::createArtwork() {
    std::cout << "Creating new artwork for artist: " << name << std::endl;

    int artworkID;
    MyString title, medium, status, imagePath;
    float price;
    int year;

    std::cout << "Enter artwork ID: ";
    std::cin >> artworkID;
    std::cout << "Enter title: ";
    std::cin >> title;
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter medium: ";
    std::cin >> medium;
    std::cout << "Enter creation year: ";
    std::cin >> year;
    std::cout << "Enter status: ";
    std::cin >> status;
    std::cout << "Enter image file path: ";
    std::cin >> imagePath;

    Artwork* newArtwork = new Artwork(artworkID, title, price, medium, year, this);

    try {
        newArtwork->loadImageFromFile(imagePath); 
    }
    catch (const ImageLoadException& ex) {
        Logger logger("log.txt");
        logger.logError(ex.getMessage());
        std::cout << "Failed to load image: " << ex.getMessage().return_array() << std::endl;
        delete newArtwork; 
        return;
    }

    try {
        addArtwork(newArtwork); 
    }
    catch (const DuplicateArtworkException& ex) {
        Logger logger("log.txt");
        logger.logError(ex.getMessage());
        std::cout << "Duplicate artwork: " << ex.getMessage().return_array() << std::endl;
        delete newArtwork;
        return;
    }

    std::cout << "Artwork created and added successfully." << std::endl;
}


void Artist::addArtwork(Artwork* artwork) {
    if (!artwork) return;

    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]->getArtworkID() == artwork->getArtworkID()) {
            throw DuplicateArtworkException("Artwork already exists", 200, artwork->getArtworkID());
        }
    }

    artworks.push(artwork);
}

void Artist::listArtworks() {
    std::cout << "Artworks by " << name << ":" << std::endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        std::cout << "- " << artworks[i]->getTitle()
            << " ($" << artworks[i]->getPrice() << ")" << std::endl;
    }
}
int Artist::getArtistID() const { return artistID; }
MyString Artist::getCountry() const { return country; }
MyString Artist::getArtStyle() const { return artStyle; }
Dynamic_array<Artwork*>& Artist::getArtworks() { return artworks; }
