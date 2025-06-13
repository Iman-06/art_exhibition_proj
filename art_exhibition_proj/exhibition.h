#ifndef EXHIBITION_H
#define EXHIBITION_H

#include "My_string.h"
#include "Dynamic_array.h"
#include "Exception.h"
class Artwork;
class Curator;

class Exhibition {
private:
    int exhibitionID;
    MyString name;
    MyString startDate;
    MyString endDate;
    MyString status;
    Curator* organizedBy;
    Dynamic_array<Artwork*> artworks;

public:
    Exhibition(int id, const MyString& n, const MyString& start,
        const MyString& end, Curator* curator);

    void addArtwork(Artwork* artwork); // throws DuplicateArtworkException
    void removeArtwork(int artworkID);
    bool checkArtworkExists(int artworkID);
    void displayAllPaintings();
    void generateExhibitionReport();
    int getTotalArtworks();
    void saveToBinary(const MyString& path); // throws FileIOException
    void loadFromBinary(const MyString& path); // throws FileIOException
    template<typename T>
    void sortArtworksBy(T comparator);
    int getExhibitionID() const;
    MyString getName() const;
    MyString getStartDate() const;
    MyString getEndDate() const;
    MyString getStatus() const;
    Curator* getOrganizedBy() const;
    Dynamic_array<Artwork*>& getArtworks();
    void setName(const MyString& n);
    void setStatus(const MyString& s);
};

#endif