#include "Curator.h"
#include "Exhibition.h"
#include <iostream>
#include "logger.h"
#include "fileIOException.h"
#include "NullReferenceException.h"
Curator::Curator(int personId, const MyString& name, const MyString& email,
    const MyString& dob, int curId, const MyString& spec)
    : Person(personId, name, email, dob), curatorID(curId), specialization(spec) {}

void Curator::displayInfo()const {
    std::cout << "Curator Information:" << std::endl;
    std::cout << "ID: " << personID << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Date of Birth: " << dateOfBirth << std::endl;
    std::cout << "Curator ID: " << curatorID << std::endl;
    std::cout << "Specialization: " << specialization << std::endl;
}


void Curator::organizeExhibition(Exhibition* exhibition) {
    Logger logger("log.txt");

    if (!exhibition) {
        logger.logError("Null Exhibition passed to Curator.");
        throw NullReferenceException("Exhibition object is null", 201, "Exhibition");
    }

    std::cout << "Organizing exhibition: " << exhibition->getName() << std::endl;
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
