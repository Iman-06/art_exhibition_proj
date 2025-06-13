#ifndef CURATOR_H
#define CURATOR_H

#include "Person.h"
class Exhibition;

class Curator : public Person {
private:
    int curatorID;
    MyString specialization;

public:
    Curator(int personId, const MyString& name, const MyString& email,
        const MyString& dob, int curId, const MyString& spec);
    void displayInfo()const override;
    void organizeExhibition(Exhibition* exhibition);
    int getCuratorID() const;
    MyString getSpecialization() const;
    void setSpecialization(const MyString& spec);
};

#endif