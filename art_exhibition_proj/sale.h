#ifndef SALE_H
#define SALE_H

#include "My_string.h"
#include "Dynamic_array.h"
#include "Exception.h"
class Artwork;
class Buyer;

class Sale {
private:
    int saleID;
    MyString date;
    float totalAmount;
    Buyer* buyer;
    Dynamic_array<Artwork*> artworks;
    Dynamic_array<float> prices;

public:
    Sale(int id, const MyString& d, Buyer* b);
    ~Sale();
    void addArtwork(Artwork* artwork, float price);
    float calculateTotal();
    void generateReceipt();
    void finalizeSale(); // throws NullReferenceException
    int getSaleID() const;
    MyString getDate() const;
    float getTotalAmount() const;
    Buyer* getBuyer() const;
    Dynamic_array<Artwork*>& getArtworks();
    Dynamic_array<float>& getPrices();
};

#endif