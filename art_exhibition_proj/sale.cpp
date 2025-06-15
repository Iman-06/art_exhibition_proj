#include "Sale.h"
#include "Buyer.h"
#include "Artwork.h"
#include "nullReferenceException.h"
#include <iostream>
#include "Logger.h"
using namespace std;
Sale::Sale(int id, const MyString& d, Buyer* b)
    : saleID(id), date(d), buyer(b), totalAmount(0.0f) {}

void Sale::addArtwork(Artwork* artwork, float price) {
    if (artwork && price > 0) {
        artworks.push(artwork);
        prices.push(price);
        cout << "Added artwork to sale: " << artwork->getTitle()
            << " for $" << price << endl;
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
    cout << "\n========== RECEIPT ==========" << endl;
    cout << "Sale ID: " << saleID << endl;
    cout << "Date: " << date << endl;

    if (buyer) {
        cout << "Buyer: " << buyer->getName() << endl;
        cout << "Address: " << buyer->getAddress() << endl;
    }
    else {
        cout << "Buyer: Unknown (record deleted)" << endl;
    }

    cout << "\nItems:" << endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        cout << "- " << artworks[i]->getTitle()
            << " ... $" << prices[i] << endl;
    }

    cout << "\nTotal Amount: $" << calculateTotal() << endl;
    cout << "============================\n" << endl;
}

void Sale::finalizeSale() {
	Logger logger("log.txt");
    if (!buyer) {
		logger.logError("Finalize failed: Null Buyer");
        throw NullReferenceException("Buyer cannot be null", 400, "Buyer");
    }

    if (artworks.getLength() == 0) {
		logger.logError("Finalize failed: No artworks in sale");
        throw NullReferenceException("No artworks in sale", 401, "Artworks");
    }
    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]) {
            artworks[i]->setStatus("Sold");
        }
    }

    calculateTotal();
    generateReceipt();
	logger.logEvent("Sale finalized: ID " + MyString(saleID) + ", Total $" + MyString(totalAmount));
    cout << "Sale finalized successfully!" << endl;
}
int Sale::getSaleID() const { return saleID; }
MyString Sale::getDate() const { return date; }
float Sale::getTotalAmount() const { return totalAmount; }
Buyer* Sale::getBuyer() const { return buyer; }
Dynamic_array<Artwork*>& Sale::getArtworks() { return artworks; }
Dynamic_array<float>& Sale::getPrices() { return prices; }
Sale::~Sale() {
    artworks.clear();
   // Logger::log("Sale destroyed");
}
