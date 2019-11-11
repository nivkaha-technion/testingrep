//
// Created by nivka on 25-Nov-18.
//

#include "citizen.h"

Citizen CitizenCopy(Citizen source) {
    return NewCitizen (cizien->name, source->age, source-> id_number, source->years_of_education,
                       source-> preferences, source->city_id); //CR: No preferences param in New Citizen
}

void CitizenFree(Citizen this) {
    uniqueOrderedListDestroy(this->preferences);
    //TODO: free the string malloc for citizen->name
    free(this);
    return;
}

//TODO: It might be nicer and cleaner to just return the bool statement. Example:
//  bool funcname(Element e1, Element e2) { return (e1->id_number == e2->id_number); }
bool CitizenEquals (Citizen first, Citizen second ){
    return (first->id_number == second->id_number);
}

bool CitizenGreaterThan (Citizen first, Citizen second ){
    return (first->id_number > second->id_number);
}

bool CitizenGreaterThanByName (Citizen first,Citizen second ){
    if(strcmp(first->name,second->name)>0) {
        return true;
    }
    if(strcmp(first->name,second->name)<0) {
        return false;
    }
    if(strcmp(first->name,second->name) == 0){
        CitizenGreaterThan(first,second);
    }
}



Citizen CitizenCreate (char* name, int age, int id_number,
                       int years_of_education, int city_id) {
    Citizen new_citizen = (Citizen) malloc(sizeof(struct citizen_t));
    if(new_citizen == NULL) {
        return NULL;
    }
    new_citizen->name = malloc(sizeof(char)*(strlen(name)+1));
    if(new_citizen->name == NULL){
        //TODO: destroy new citizen on failure otherwise memory leak
        return NULL;
    }
    preferences = uniqueOrderedListCreate(VotingPreferenceCopy,
                                          VotingPreferenceFree,
                                          VotingPreferenceEqual,
                                          VotingPreferenceGreaterThan);
    //TODO: deal with failure
    //TODO: new_citizen->preferences?
    new_citizen->name = strcpy (new_citizen->name,name);
    new_citizen->age = age;
    new_citizen->id_number = id_number;
    new_citizen->years_of_education = years_of_education;
    new_citizen->city_id = city_id;
    return new_citizen;
}

void CitizenChangeAddress (Citizen this, int  new_city_id){
    this->city_id = new_city_id;
    uniqueOrderedListClear(this->preferences);
}

MtmElectionResult CitizenSupportCandidate(Citizen this, Candidate candidate,
                                          int priority) {
    VotingPreference new_preference;
    new_preference = VotingPreferenceCreate(candidate, priority);
    if(new_preference == NULL){
        return MTM_ELECTIONS_MEMORY_ERROR; //TODO: maybe replace with new enum to remove dependency on elections object
    }
    if (uniqueOrderedListInsert(this->preferences, new_preference)
                                                == UNIQUE_ORDERED_LIST_SUCCESS){
        return MTM_ELECTIONS_SUCCESS;
    }else{ //TODO: better error handling, also free new_preference on failure?
        return MTM_ELECTIONS_MEMORY_ERROR;
    }
}
void CitizenRemoveSupportForCandidate(Citizen this,
                                      int candidate_id) {
    VotingPreference to_remove;
    to_remove = GetVotingPreferenceByCandidate(this->preference, candidate_id);
    uniqueOrderedListRemove(this->preferences,to_remove);
}
