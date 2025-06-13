#ifndef PERSON_H
#define PERSON_H

#include "my_string.h"

class Person {
protected:
    int personID;
    MyString name;
    MyString email;
    MyString dateOfBirth;

public:
    Person();
    Person(int id, const MyString& name, const MyString& email, const MyString& dob);
    virtual void displayInfo() const = 0; 
    virtual ~Person() = default;
    int getPersonID() const;
    MyString getName() const;
    MyString getEmail() const;
    MyString getDateOfBirth() const;
    void setName(const MyString& n);
    void setEmail(const MyString& e);
    void setDateOfBirth(const MyString& dob);
};

#endif
