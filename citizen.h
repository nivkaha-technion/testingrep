//
// Created by nivka on 25-Nov-18.
//
#ifndef CITIZEN_H
#define CITIZEN_H

#include "uniqueOrderedList/uniqueOrderedList.h"

typedef  struct citizen_t{
    char* name;
    int age;
    int id_number;
    int years_of_education;
    uniqueOrderedList preferences;
    int city_id;
}*Citizen;


Citizen CitizenCopy(Citizen source);

void CitizenFree(Citizen this);

bool CitizenEquals (Citizen first, Citizen second );

bool CitizenGreaterThan (Citizen first, Citizen second );

bool CitizenGreaterThanByName (Citizen first,Citizen second );

//ToAdd: CitizenCreate function - Make a new citizen with the given params. Then make citizen copy use citizen create.
Citizen CitizenCreate (char* name, int age, int id_number,
                       int years_of_education, int city_id);

void CitizenChangeAddress (Citizen this, int new_city_id);

MtmElectionResult CitizenSupportCandidate(Citizen this, Citizen candidate,
                                          int priority);
void CitizenRemoveSupportForCandidate (Citizen this, int candidate_id);

#endif //CITIZEN_H
