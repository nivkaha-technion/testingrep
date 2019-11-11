//
// Created by nivka on 25-Nov-18.
//

#include "uniqueOrderedList/uniqueOrderedList.h"
#include "city.h"
#include "candidate.h"
#include <string.h>

City CityCreate(int city_id, char* city_name, uniqueOrderedList candidates){
    City new_city =(City) malloc (sizeof(struct city_t));
    if (new_city == NULL){
        return NULL;
    }
    // size of new string for city name is length of given name +1 for '\0'
    new_city->city_name = (char *) malloc(sizeof(char)*(strlen(city_name) + 1));
    if (new_city->city_name == NULL){
        free(new_city);
        return NULL;
    }
    new_city->city_name = strcpy(new_city->city_name, city_name);
    new_city->city_id = city_id;
    // if we got a valid candidates we can use that, otherwise we make empty one
    if (candidates == NULL) {
        candidates = uniqueOrderedListCreate(CandidateCopy,
                                             CandidateFree,
                                             CandidateEquals,
                                             CandidateGreaterThan);
    }
    new_city->candidates = candidates;
    if (candidates == NULL) {
        CityFree(new_city);
        return NULL;
    }
    return new_city;
}
City CityCopy(City source) {
    UniqueOrderedList candidates = uniqueOrderedListCopy(source->candidates);
    if (candidates == NULL){
        return NULL;
    }
    City duplicate = CityCreate(source->city_id, source->city_name, candidates);
    if (duplicate == NULL){
        return NULL;
    }
    return duplicate;
}

void CityFree(City this) {
    uniqueOrderedListDestroy(this->candidates);
    free(this->city_name);
    free(this);
}

bool CityEquals (City first,City second){
    return (first->city_id == second->city_id);
}

bool CityGreaterThan (City first,City second ){
    return (first->city_id > second->city_id);
}


//TODO: Delete commended function
/*
UniqueOrderedList CityGetCitizens(City city, UniqueOrderedList citizens_list){
    UniqueOrderedList city_citizens = uniqueOrderedListCopy(citizens_list);
    if (city_citizens == NULL){
        return NULL;
    }
    for (Citizen citizen = uniqueOrderedListGetLowest(city_citizens);
         citizen != NULL; citizen = uniqueOrderedListGetNext(city_citizens)){
        if (citizen->city_id != city->city_id){
            uniqueOrderedListRemove(city_citizens, citizen);
        }
    }
    return city_citizens;
}
*/
