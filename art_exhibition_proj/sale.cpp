#include "Sale.h"
#include "Buyer.h"
#include "Artwork.h"
#include "nullReferenceException.h"
#include <iostream>

Sale::Sale(int id, const MyString& d, Buyer* b)
    : saleID(id), date(d), buyer(b), totalAmount(0.0f) {}

void Sale::addArtwork(Artwork* artwork, float price) {
    if (artwork && price > 0) {
        artworks.push(artwork);
        prices.push(price);
        std::cout << "Added artwork to sale: " << artwork->getTitle()
            << " for $" << price << std::endl;
    }
}

float Sale::calculateTotal() {
    totalAmount = 0.0f;
    for (int i = 0; i < prices.getLength(); i++) {
        totalAmount += prices[i];
    }
    return totalAmount;
}

void Sale::generateReceipt() {
    std::cout << "\n========== RECEIPT ==========" << std::endl;
    std::cout << "Sale ID: " << saleID << std::endl;
    std::cout << "Date: " << date << std::endl;

    if (buyer) {
        std::cout << "Buyer: " << buyer->getName() << std::endl;
        std::cout << "Address: " << buyer->getAddress() << std::endl;
    }

    std::cout << "\nItems:" << std::endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        std::cout << "- " << artworks[i]->getTitle()
            << " ... $" << prices[i] << std::endl;
    }

    std::cout << "\nTotal Amount: $" << calculateTotal() << std::endl;
    std::cout << "============================\n" << std::endl;
}

void Sale::finalizeSale() {
    if (!buyer) {
        throw NullReferenceException("Buyer cannot be null", 400, "Buyer");
    }

    if (artworks.getLength() == 0) {
        throw NullReferenceException("No artworks in sale", 401, "Artworks");
    }
    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]) {
            artworks[i]->setStatus("Sold");
        }
    }

    calculateTotal();
    generateReceipt();
    std::cout << "Sale finalized successfully!" << std::endl;
}
int Sale::getSaleID() const { return saleID; }
MyString Sale::getDate() const { return date; }
float Sale::getTotalAmount() const { return totalAmount; }
Buyer* Sale::getBuyer() const { return buyer; }
Dynamic_array<Artwork*>& Sale::getArtworks() { return artworks; }
Dynamic_array<float>& Sale::getPrices() { return prices; }
//Sale::~Sale() {
//    Logger::log("Sale destroyed");
//}
