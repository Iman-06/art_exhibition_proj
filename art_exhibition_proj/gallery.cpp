#include "Gallery.h"
#include "Curator.h"
#include "Exhibition.h"
#include "artwork.h"
#include <iostream>

Gallery::Gallery(int id, const MyString& n, const MyString& loc, int cap)
    : galleryID(id), name(n), location(loc), capacity(cap) {}
void Gallery::hostExhibition(Exhibition* exhibition) {
        if (exhibitions.getLength() >= capacity) {
            std::cout << "Cannot host more exhibitions. Capacity full." << std::endl;
            return;
        }
        for (int i = 0; i < exhibitions.getLength(); ++i) {
            if (exhibitions[i] == exhibition) {
                std::cout << "Exhibition already hosted in the gallery." << std::endl;
                return;
            }
        }

        exhibitions.push(exhibition);
        std::cout << "Exhibition '" << exhibition->getName() << "' hosted successfully." << std::endl;
    }
void Gallery::addCurator(Curator* curator) {
    if (curator) {
        curators.push(curator);
        std::cout << "Added curator: " << curator->getName() << std::endl;
    }
}

void Gallery::removeCurator(int curatorID) {
    for (int i = 0; i < curators.getLength(); i++) {
        if (curators[i]->getCuratorID() == curatorID) {
            // Remove curator by shifting elements
            for (int j = i; j < curators.getLength() - 1; j++) {
                curators[j] = curators[j + 1];
            }
            curators.pop();
            std::cout << "Removed curator with ID: " << curatorID << std::endl;
            break;
        }
    }
}

void Gallery::listAllExhibitions() {
    std::cout << "Exhibitions at " << name << ":" << std::endl;
    for (int i = 0; i < exhibitions.getLength(); i++) {
        std::cout << "- " << exhibitions[i]->getName()
            << " (" << exhibitions[i]->getStatus() << ")" << std::endl;
    }
}

void Gallery::searchArtwork(const MyString& title) {
    std::cout << "Searching for artwork: " << title << std::endl;
    bool found = false;

    for (int i = 0; i < exhibitions.getLength(); i++) {
        Dynamic_array<Artwork*>& artworks = exhibitions[i]->getArtworks();
        for (int j = 0; j < artworks.getLength(); j++) {
            if (artworks[j]->getTitle() == title) {
                std::cout << "Found in exhibition: " << exhibitions[i]->getName() << std::endl;
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "Artwork not found in any exhibition" << std::endl;
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
