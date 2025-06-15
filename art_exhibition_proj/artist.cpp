#include "Artist.h"
#include "Artwork.h"
#include "duplicateArtworkException.h"
#include "ImageLoadException.h"
#include "Logger.h"
#include <iostream>
using namespace std;

Artist::Artist(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int artId, const MyString& country, const MyString& style)
    : Person(personId, name, email, dob), artistID(artId), country(country), artStyle(style) {}

void Artist::displayInfo()const {
    cout << "Artist Information:" << endl;
    cout << "ID: " << personID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Artist ID: " << artistID << endl;
    cout << "Country: " << country << endl;
    cout << "Art Style: " << artStyle << endl;
    cout << "Number of Artworks: " << artworks.getLength() << endl;
}

//void Artist::createArtwork() {
//    cout << "Creating new artwork for artist: " << name << endl;
//
//    int artworkID;
//    MyString title, medium, status, imagePath;
//    float price;
//    int year;
//
//    cout << "Enter artwork ID: ";
//    cin >> artworkID;
//    cout << "Enter title: ";
//    cin >> title;
//    cout << "Enter price: ";
//    cin >> price;
//    cout << "Enter medium: ";
//    cin >> medium;
//    cout << "Enter creation year: ";
//    cin >> year;
//    cout << "Enter status: ";
//    cin >> status;
//    cout << "Enter image file path: ";
//    cin >> imagePath;
//
//    Artwork* newArtwork = new Artwork(artworkID, title, price, medium, year, this);
//
//    try {
//        newArtwork->loadImageFromFile(imagePath); 
//    }
//    catch (const ImageLoadException& ex) {
//        Logger logger("log.txt");
//        logger.logError(ex.getMessage());
//        cout << "Failed to load image: " << ex.getMessage().return_array() << endl;
//        delete newArtwork; 
//        return;
//    }
//
//    try {
//        addArtwork(newArtwork); 
//    }
//    catch (const DuplicateArtworkException& ex) {
//        Logger logger("log.txt");
//        logger.logError(ex.getMessage());
//        cout << "Duplicate artwork: " << ex.getMessage().return_array() << endl;
//        delete newArtwork;
//        return;
//    }
//
//    cout << "Artwork created and added successfully." << endl;
//}


void Artist::addArtwork(Artwork* artwork) {
    if (!artwork) return;

    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]->getArtworkID() == artwork->getArtworkID()) {
            //catch in main
            throw DuplicateArtworkException("Artwork already exists", 200, artwork->getArtworkID());
        }
    }

    artworks.push(artwork);
	Logger logger("log.txt");
	logger.logEvent("Artwork created for artist: " + name + " - " + artwork->getTitle());
	cout << "Artwork added: " << artwork->getTitle() << endl;
}

void Artist::listArtworks() {
    cout << "Artworks by " << name << ":" << endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        cout << "- " << artworks[i]->getTitle()
            << " ($" << artworks[i]->getPrice() << ")" << endl;
    }
}
int Artist::getArtistID() const { return artistID; }
MyString Artist::getCountry() const { return country; }
MyString Artist::getArtStyle() const { return artStyle; }
Dynamic_array<Artwork*>& Artist::getArtworks() { return artworks; }
