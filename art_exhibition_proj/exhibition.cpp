#include "Exhibition.h"
#include "Curator.h"
#include "Artwork.h"
#include "Artist.h"
#include "duplicateArtworkException.h"
#include "FileIOException.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
using namespace std;
Exhibition::Exhibition(int id, const MyString& n, const MyString& start,
    const MyString& end, Curator* curator)
    : exhibitionID(id), name(n), startDate(start), endDate(end),
    organizedBy(curator), status("Planned") {}

void Exhibition::addArtwork(Artwork* artwork) {
    if (!artwork) return;

    if (checkArtworkExists(artwork->getArtworkID())) {
        throw DuplicateArtworkException("Artwork already in exhibition", 201, artwork->getArtworkID());
    }
	Logger logger("log.txt");

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
    cout << "Exhibition: " << name << endl;
    cout << "Artworks:" << endl;
    for (int i = 0; i < artworks.getLength(); i++) {
        cout << "- " << artworks[i]->getTitle()
            << " by " << artworks[i]->getCreatedBy()->getName() << endl;
    }
}

void Exhibition::generateExhibitionReport() {
    cout << "Exhibition Report" << endl;
    cout << "=================" << endl;
    cout << "Name: " << name << endl;
    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;
    cout << "Status: " << status << endl;
    if (organizedBy)
        cout << "Organized by: " << organizedBy->getName() << endl;
    else
        cout << "Curator: Unknown (record deleted)" << endl;
    cout << "Total Artworks: " << getTotalArtworks() << endl;
    displayAllPaintings();
}

int Exhibition::getTotalArtworks() {
    return artworks.getLength();
}
void Exhibition::saveToBinary(const MyString& path) {
    Logger logger("log.txt");
    try {
        std::ofstream outFile(path.return_array(), std::ios::binary);
        if (!outFile) {
            throw FileIOException("Cannot open file for writing", 401, path);
        }

        int count = artworks.getLength();
        outFile.write(reinterpret_cast<char*>(&count), sizeof(count));
        logger.logEvent("Saving artworks count: " + MyString(count));
        for (int i = 0; i < count; ++i) {
            Artwork* a = artworks[i];

            int id = a->getArtworkID();
            outFile.write(reinterpret_cast<char*>(&id), sizeof(int));

            MyString title = a->getTitle();
            int len = title.length(title.return_array());
            outFile.write(reinterpret_cast<char*>(&len), sizeof(int));
            outFile.write(title.return_array(), len);

            float price = a->getPrice();
            outFile.write(reinterpret_cast<char*>(&price), sizeof(float));

            MyString medium = a->getMedium();
            len = medium.length(medium.return_array());
            outFile.write(reinterpret_cast<char*>(&len), sizeof(int));
            outFile.write(medium.return_array(), len);

            int year = a->getCreationYear();
            outFile.write(reinterpret_cast<char*>(&year), sizeof(int));

            MyString status = a->getStatus();
            len = status.length(status.return_array());
            outFile.write(reinterpret_cast<char*>(&len), sizeof(int));
            outFile.write(status.return_array(), len);

            MyString img = a->getImagePath();
            len = img.length(img.return_array());
            outFile.write(reinterpret_cast<char*>(&len), sizeof(int));
            outFile.write(img.return_array(), len);
            logger.logEvent("Saving artwork with title: " + a->getTitle());
        }
    }

    catch (const FileIOException& ex) {
        logger.logError("Binary Save Error: " + ex.getMessage());
    }
}
void Exhibition::loadFromBinary(const MyString& path) {
    Logger logger("log.txt");

    try {
        std::ifstream inFile(path.return_array(), std::ios::binary);
        if (!inFile) {
            throw FileIOException("Cannot open file for reading", 402, path);
        }

        int count;
        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));

        for (int i = 0; i < count; ++i) {
            Artwork* a = new Artwork();
            int id;
            inFile.read(reinterpret_cast<char*>(&id), sizeof(int));
            a->setArtworkID(id);
            int len;
            inFile.read(reinterpret_cast<char*>(&len), sizeof(int));
            char* buffer = new char[len + 1];
            inFile.read(buffer, len);
            buffer[len] = '\0';
            a->setTitle(MyString(buffer));
            delete[] buffer;
            float price;
            inFile.read(reinterpret_cast<char*>(&price), sizeof(float));
            a->setPrice(price);
            inFile.read(reinterpret_cast<char*>(&len), sizeof(int));
            buffer = new char[len + 1];
            inFile.read(buffer, len);
            buffer[len] = '\0';
            a->setMedium(MyString(buffer));
            delete[] buffer;

            // Read year
            int year;
            inFile.read(reinterpret_cast<char*>(&year), sizeof(int));
            a->setCreationYear(year);

            // Read status
            inFile.read(reinterpret_cast<char*>(&len), sizeof(int));
            buffer = new char[len + 1];
            inFile.read(buffer, len);
            buffer[len] = '\0';
            a->setStatus(MyString(buffer));
            delete[] buffer;

            inFile.read(reinterpret_cast<char*>(&len), sizeof(int));
            buffer = new char[len + 1];
            inFile.read(buffer, len);
            buffer[len] = '\0';
            a->setImagePath(MyString(buffer));
            delete[] buffer;

            artworks.push(a);
        }

        inFile.close();
        logger.logEvent("Exhibition loaded from binary successfully.");
    }
    catch (const FileIOException& ex) {
        logger.logError("Binary Load Error: " + ex.getMessage());
    }
}
Exhibition::~Exhibition() {
    artworks.clear();
}

int Exhibition::getExhibitionID() const { return exhibitionID; }
MyString Exhibition::getName() const { return name; }
MyString Exhibition::getStartDate() const { return startDate; }
MyString Exhibition::getEndDate() const { return endDate; }
MyString Exhibition::getStatus() const { return status; }
Curator* Exhibition::getOrganizedBy() const {
    if (organizedBy)
        return organizedBy;
    else{
        cout << "Curator: Unknown (record deleted)" << endl;
        return nullptr;

    }
}
Dynamic_array<Artwork*>& Exhibition::getArtworks() { return artworks; }
void Exhibition::setName(const MyString& n) { name = n; }
void Exhibition::setStatus(const MyString& s) { status = s; }
