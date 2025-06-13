#ifndef GALLERY_H
#define GALLERY_H

#include "My_string.h"
#include "Dynamic_array.h"
class Curator;
class Exhibition;

class Gallery {
private:
    int galleryID;
    MyString name;
    MyString location;
    int capacity;
    Dynamic_array<Curator*> curators;
    Dynamic_array<Exhibition*> exhibitions;

public:
    Gallery(int id, const MyString& n, const MyString& loc, int cap);

    void hostExhibition(Exhibition* exhibition);
    void addCurator(Curator* curator);
    void removeCurator(int curatorID);
    void listAllExhibitions();
    void searchArtwork(const MyString& title);
    int getGalleryID() const;
    MyString getName() const;
    MyString getLocation() const;
    int getCapacity() const;
    Dynamic_array<Curator*>& getCurators();
    Dynamic_array<Exhibition*>& getExhibitions();
    void setName(const MyString& n);
    void setLocation(const MyString& loc);
    void setCapacity(int cap);
};

#endif