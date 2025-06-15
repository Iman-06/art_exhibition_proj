#include "Curator.h"
#include "Exhibition.h"
#include <iostream>
#include "logger.h"
#include "fileIOException.h"
#include "NullReferenceException.h"
using namespace std;


Curator::Curator(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int curId, const MyString& spec)
    : Person(personId, name, email, dob), curatorID(curId), specialization(spec) {}

void Curator::displayInfo()const {
    cout << "Curator Information:" << endl;
    cout << "ID: " << personID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Curator ID: " << curatorID << endl;
    cout << "Specialization: " << specialization << endl;
}


void Curator::organizeExhibition(Exhibition* exhibition) {
    Logger logger("log.txt");

    if (!exhibition) {
        logger.logError("Null Exhibition passed to Curator.");
        throw NullReferenceException("Exhibition object is null", 201, "Exhibition");
    }

    cout << "Organizing exhibition: " << exhibition->getName() << endl;
    logger.logEvent("Curator started organizing exhibition: " + exhibition->getName());
    try {
        exhibition->generateExhibitionReport();
        logger.log("Exhibition report generated successfully for: " + exhibition->getName());
    }
    catch (const FileIOException& ex) {
        logger.logError("Failed to generate report: " + ex.getMessage());
    }
}
int Curator::getCuratorID() const { return curatorID; }
MyString Curator::getSpecialization() const { return specialization; }
void Curator::setSpecialization(const MyString& spec) { specialization = spec; }
