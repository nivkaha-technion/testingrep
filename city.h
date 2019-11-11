//
// Created by nivka on 25-Nov-18.
//
#include "uniqueOrderedList/uniqueOrderedList.h"

#ifndef CITY_H
#define CITY_H

typedef struct city_t{
    char* city_name;
    int city_id;
    uniqueOrderedList candidates;
} *City;


bla = "pARhvm1GmHyvLydUtFNCCMIIu4VEyaZNo9MbR3IJ" //or something
// pARhvm1GmHyvLydUtFNCCMIIu4VEyaZNo9MbR3IJ



/**
 * Creates a new city object with the parameters given
 * @param city_id : the ID for the new city
 * @param city_name : the name for the new city
 * @param candidates : candidates list for the new city (used as is, not copied)
 *                          If NULL, a new, empty one is made
 * @return The new city or NULL on any failure.
 */
City CityCreate(int city_id, char* city_name, uniqueOrderedList candidates);
/**
 * Creates a copy of the given city
 * @param source : the city to be duplicated
 * @return The duplicated city
 */
City CityCopy(City source);

void CityFree(City this);
ASIAJAZ4HRG3CPA63XEQ
bool CityEquals (City first, City second);

bool CityGreaterThan (City first, City second);

#endif //CITY_H
