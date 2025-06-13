#ifndef ARTIST_H
#define ARTIST_H

#include "Person.h"
#include "Dynamic_array.h"
#include "Exception.h"
class Artwork;

class Artist : public Person {
private:
    int artistID;
    MyString country;
    MyString artStyle;
    Dynamic_array<Artwork*> artworks;

public:
    Artist(int personId, const MyString& name, const MyString& email,
        const MyString& dob, int artId, const MyString& country, const MyString& style);

    void displayInfo()const override;
    void createArtwork();
    void addArtwork(Artwork* artwork); 
    void listArtworks();
    int getArtistID() const;
    MyString getCountry() const;
    MyString getArtStyle() const;
    Dynamic_array<Artwork*>& getArtworks();
};

#endif