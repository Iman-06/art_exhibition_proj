#include "Gallery.h"
#include "Curator.h"
#include "Exhibition.h"
#include "artwork.h"
#include <iostream>
using namespace std;

Gallery::Gallery(int id, const MyString& n, const MyString& loc, int cap)
    : galleryID(id), name(n), location(loc), capacity(cap) {}
void Gallery::hostExhibition(Exhibition* exhibition) {
        if (exhibitions.getLength() >= capacity) {
            cout << "Cannot host more exhibitions. Capacity full." << endl;
            return;
        }
        for (int i = 0; i < exhibitions.getLength(); ++i) {
            if (exhibitions[i] == exhibition) {
                cout << "Exhibition already hosted in the gallery." << endl;
                return;
            }
        }

        exhibitions.push(exhibition);
        cout << "Exhibition '" << exhibition->getName() << "' hosted successfully." << endl;
    }
void Gallery::addCurator(Curator* curator) {
    if (curator) {
        curators.push(curator);
        cout << "Added curator: " << curator->getName() << endl;
    }
}

void Gallery::removeCurator(int curatorID) {
    for (int i = 0; i < curators.getLength(); i++) {
        if (curators[i]->getCuratorID() == curatorID) {
            for (int j = i; j < curators.getLength() - 1; j++) {
                curators[j] = curators[j + 1];
            }
            curators.pop();
            cout << "Removed curator with ID: " << curatorID << endl;
            break;
        }
    }
}

void Gallery::listAllExhibitions() {
    cout << "Exhibitions at " << name << ":" << endl;
    for (int i = 0; i < exhibitions.getLength(); i++) {
        cout << "- " << exhibitions[i]->getName()
            << " (" << exhibitions[i]->getStatus() << ")" << endl;
    }
}

void Gallery::searchArtwork(const MyString& title) {
    cout << "Searching for artwork: " << title << endl;
    bool found = false;

    for (int i = 0; i < exhibitions.getLength(); i++) {
        Dynamic_array<Artwork*>& artworks = exhibitions[i]->getArtworks();
        for (int j = 0; j < artworks.getLength(); j++) {
            if (artworks[j]->getTitle().equalsIgnoreCaseTrimmed(title)){
                cout << "Found in exhibition: " << exhibitions[i]->getName() << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Artwork not found in any exhibition" << endl;
    }
}
int Gallery::getGalleryID() const { return galleryID; }
MyString Gallery::getName() const { return name; }
MyString Gallery::getLocation() const { return location; }
int Gallery::getCapacity() const { return capacity; }
Dynamic_array<Curator*>& Gallery::getCurators() { return curators; }
Dynamic_array<Exhibition*>& Gallery::getExhibitions() { return exhibitions; }
void Gallery::setName(const MyString& n) { name = n; }
void Gallery::setLocation(const MyString& loc) { location = loc; }
void Gallery::setCapacity(int cap) { capacity = cap; }
Gallery::~Gallery() {
	curators.clear();
	exhibitions.clear();
}