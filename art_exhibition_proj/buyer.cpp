#include "Buyer.h"
#include "Artwork.h"
#include "Dynamic_array.h"
#include "Logger.h"
#include "nullReferenceException.h"
#include "imageLoadException.h"
#include <iostream>
using namespace std;

Buyer::Buyer(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int buyerId, const MyString& addr)
    : Person(personId, name, email, dob), buyerID(buyerId), address(addr) {}

void Buyer::displayInfo()const {
    cout << "Buyer Information:" << endl;
    cout << "ID: " << personID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Buyer ID: " << buyerID << endl;
    cout << "Address: " << address << endl;
}

void Buyer::purchaseArtwork(Artwork* artwork) {
    if (artwork && artwork->isAvailableForSale()) {
        cout << "Purchasing artwork: " << artwork->getTitle()
            << " for $" << artwork->getPrice() << endl;
        artwork->setStatus("Sold");
    }
    else {
        cout << "Artwork not available for purchase" << endl;
    }
}
void Buyer::viewArtwork(Artwork* artwork) {
    if (!artwork) {
        Logger logger("log.txt");
        logger.logError("Attempted to view a null artwork.");
        throw NullReferenceException("Null artwork passed to viewArtwork", 301, "Artwork");
    }

    try {
        artwork->loadImageFromFile(artwork->getImagePath());
        artwork->displayImage();
    }
    catch (const ImageLoadException& ex) {
        Logger logger("log.txt");
        logger.logError("Image load failed for artwork: " + artwork->getTitle() + " | " + ex.getMessage());
    }
}

void Buyer::browseArtworks(const Dynamic_array<Artwork*>& artworks) {
    cout << "Browsing available artworks...\n" << endl;

    for (int i = 0; i < artworks.getLength(); ++i) {
        if (artworks[i]->isAvailableForSale()) {
            cout << "Artwork ID: " << artworks[i]->getArtworkID() << endl;
            cout << "Title: " << artworks[i]->getTitle() << endl;
            cout << "Price: $" << artworks[i]->getPrice() << endl;
            cout << "---------------------------" << endl;
        }
    }
}
int Buyer::getBuyerID() const { return buyerID; }
MyString Buyer::getAddress() const { return address; }
void Buyer::setAddress(const MyString& addr) { address = addr; }
