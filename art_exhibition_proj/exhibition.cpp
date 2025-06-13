#include "Exhibition.h"
#include "Curator.h"
#include "Artwork.h"
#include "Artist.h"
#include <iostream>
#include "duplicateArtworkException.h"
#include "FileIOException.h"
#include <fstream>

Exhibition::Exhibition(int id, const MyString& n, const MyString& start,
    const MyString& end, Curator* curator)
    : exhibitionID(id), name(n), startDate(start), endDate(end),
    organizedBy(curator), status("Planned") {}

void Exhibition::addArtwork(Artwork* artwork) {
    if (!artwork) return;

    if (checkArtworkExists(artwork->getArtworkID())) {
        throw DuplicateArtworkException("Artwork already in exhibition", 201, artwork->getArtworkID());
    }

    artworks.push(artwork);
}

void Exhibition::removeArtwork(int artworkID) {
    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]->getArtworkID() == artworkID) {
            for (int j = i; j < artworks.getLength() - 1; j++) {
                artworks[j] = artworks[j + 1];
            }
            artworks.pop();
            break;
        }
    }
}

bool Exhibition::checkArtworkExists(int artworkID) {
    for (int i = 0; i < artworks.getLength(); i++) {
        if (artworks[i]->getArtworkID() == artworkID) {
            return true;
        }
    }
    return false;
}

void Exhibition::displayAllPaintings() {
    std::cout << "Exhibition: " << name << std::endl;
    std::cout << "Artworks:" << std::endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        std::cout << "- " << artworks[i]->getTitle()
            << " by " << artworks[i]->getCreatedBy()->getName() << std::endl;
    }
}

void Exhibition::generateExhibitionReport() {
    std::cout << "Exhibition Report" << std::endl;
    std::cout << "=================" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Start Date: " << startDate << std::endl;
    std::cout << "End Date: " << endDate << std::endl;
    std::cout << "Status: " << status << std::endl;
    std::cout << "Organized by: " << organizedBy->getName() << std::endl;
    std::cout << "Total Artworks: " << getTotalArtworks() << std::endl;
    displayAllPaintings();
}

int Exhibition::getTotalArtworks() {
    return artworks.getLength();
}
//needs imlpementation 
//void Exhibition::saveToBinary(const MyString& path) {
//    std::ofstream file(path.return_array(), std::ios::binary);
//    if (!file.is_open()) {
//        throw FileIOException("Cannot open file for writing", 300, path);
//    }
//
//    // Save basic data
//    file.write(reinterpret_cast<const char*>(&exhibitionID), sizeof(exhibitionID));
//    // Note: For a complete implementation, you'd need to handle MyString serialization
//
//    file.close();
//}
//
//void Exhibition::loadFromBinary(const MyString& path) {
//    std::ifstream file(path.return_array(), std::ios::binary);
//    if (!file.is_open()) {
//        throw FileIOException("Cannot open file for reading", 301, path);
//    }
//
//    // Load basic data
//    file.read(reinterpret_cast<char*>(&exhibitionID), sizeof(exhibitionID));
//    // Note: For a complete implementation, you'd need to handle MyString deserialization
//
//    file.close();
//}
template<typename T>
void Exhibition::sortArtworksBy(T comparator) {
    for (int i = 0; i < artworks.getLength() - 1; i++) {
        for (int j = 0; j < artworks.getLength() - i - 1; j++) {
            if (!comparator(artworks[j], artworks[j + 1])) {
                Artwork* temp = artworks[j];
                artworks[j] = artworks[j + 1];
                artworks[j + 1] = temp;
            }
        }
    }
}


int Exhibition::getExhibitionID() const { return exhibitionID; }
MyString Exhibition::getName() const { return name; }
MyString Exhibition::getStartDate() const { return startDate; }
MyString Exhibition::getEndDate() const { return endDate; }
MyString Exhibition::getStatus() const { return status; }
Curator* Exhibition::getOrganizedBy() const { return organizedBy; }
Dynamic_array<Artwork*>& Exhibition::getArtworks() { return artworks; }
void Exhibition::setName(const MyString& n) { name = n; }
void Exhibition::setStatus(const MyString& s) { status = s; }
