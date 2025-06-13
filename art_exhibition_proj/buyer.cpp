#include "Buyer.h"
#include "Artwork.h"
#include "Dynamic_array.h"
#include <iostream>

Buyer::Buyer(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int buyerId, const MyString& addr)
    : Person(personId, name, email, dob), buyerID(buyerId), address(addr) {}

void Buyer::displayInfo()const {
    std::cout << "Buyer Information:" << std::endl;
    std::cout << "ID: " << personID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Date of Birth: " << dateOfBirth << std::endl;
    std::cout << "Buyer ID: " << buyerID << std::endl;
    std::cout << "Address: " << address << std::endl;
}

void Buyer::purchaseArtwork(Artwork* artwork) {
    if (artwork && artwork->isAvailableForSale()) {
        std::cout << "Purchasing artwork: " << artwork->getTitle()
            << " for $" << artwork->getPrice() << std::endl;
        artwork->setStatus("Sold");
    }
    else {
        std::cout << "Artwork not available for purchase" << std::endl;
    }
}

void Buyer::browseArtworks(const Dynamic_array<Artwork*>& artworks) {
    std::cout << "Browsing available artworks...\n" << std::endl;

    for (int i = 0; i < artworks.getLength(); ++i) {
        if (artworks[i]->isAvailableForSale()) {
            std::cout << "Artwork ID: " << artworks[i]->getArtworkID() << std::endl;
            std::cout << "Title: " << artworks[i]->getTitle() << std::endl;
            std::cout << "Price: $" << artworks[i]->getPrice() << std::endl;
            std::cout << "---------------------------" << std::endl;
        }
    }
}
int Buyer::getBuyerID() const { return buyerID; }
MyString Buyer::getAddress() const { return address; }
void Buyer::setAddress(const MyString& addr) { address = addr; }
