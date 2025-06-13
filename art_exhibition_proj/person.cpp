#include "Person.h"

Person::Person() : personID(0), name(""), email(""), dateOfBirth("") {}

Person::Person(int id, const MyString& name, const MyString& email, const MyString& dob)
    : personID(id), name(name), email(email), dateOfBirth(dob) {}
int Person::getPersonID() const {
    return personID;
}

MyString Person::getName() const {
    return name;
}

MyString Person::getEmail() const {
    return email;
}

MyString Person::getDateOfBirth() const {
    return dateOfBirth;
}

void Person::setName(const MyString& n) {
    name = n;
}

void Person::setEmail(const MyString& e) {
    email = e;
}

void Person::setDateOfBirth(const MyString& dob) {
    dateOfBirth = dob;
}