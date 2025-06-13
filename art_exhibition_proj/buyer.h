#ifndef BUYER_H
#define BUYER_H

#include "Person.h"
class Artwork;

class Buyer : public Person {
private:
    int buyerID;
    MyString address;

public:
    Buyer(int personId, const MyString& name, const MyString& email,
        const MyString& dob, int buyerId, const MyString& addr);
    void displayInfo()const override;
    void purchaseArtwork(Artwork* artwork);
    void browseArtworks(const Dynamic_array<Artwork*>& artworks);
    int getBuyerID() const;
    MyString getAddress() const;
    void setAddress(const MyString& addr);
};

#endif