#include "mtm_elections.h"
#include "uniqueOrderedList/uniqueOrderedList.h"
#include "candidate.h"
#include "city.h"
#include "citizen.h"
#include "voting_preference.h"
#define MIN_CANDIDATE_AGE (21)
#define VOTING_AGE (17)

struct mtm_elections_t{
    uniqueOrderedList cities;
    uniqueOrderedList citizens;
};

MtmElections mtmElectionsCreate() {
    MtmElections new_mtm_elections = NULL;
    new_mtm_elections = (MtmElections) malloc(sizeof(struct mtm_elections_t));
    if (new_mtm_elections == NULL) {
           return NULL;
    }
    new_mtm_elections->cities = uniqueOrderedListCreate(CityCopy,
                                                        CityFree,
                                                        CityEquals,
                                                        CitizenGreaterThan);
    if (new_mtm_elections->cities == NULL) {
        new_mtm_elections->citizens = NULL; // so that we can free with destroy
        mtmElectionsDestroy(new_mtm_elections);
        return NULL;
    }
    new_mtm_elections->citizens = uniqueOrderedListCreate(CitizenCopy,
                                                          CitizenFree,
                                                          CitizenEquals,
                                                          CitizenGreaterThan);
    if (new_mtm_elections->cities == NULL){
        mtmElectionsDestroy(new_mtm_elections);
        return NULL;
    }
    return new_mtm_elections;
}

void mtmElectionsDestroy(MtmElections mtmElections) {
    uniqueOrderedListDestroy(mtmElections->citizens);
    uniqueOrderedListDestroy(mtmElections->cities);
    free(mtmElections);
    return;
}

MtmElectionsResult mtmElectionsAddCity(MtmElections mtmElections,
                                       const char* cityName,
                                       int cityId){
    if(mtmElections == NULL || cityName == NULL) {
        return MTM_ELECTIONS_NULL_ARGUMENT;
    }
    if (cityId < 0){
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    City new_city = CityCreate(cityId, cityName, NULL);
    if (new_city == NULL){
        return  MTM_ELECTIONS_MEMORY_ERROR;
    }
    UniqueOrderedListResult insert_result;
    insert_result = uniqueOrderedListInsert(mtmElections->cities, new_city);
    //todo: think about if this is the right way to handle this
    if (insert_result == UNIQUE_ORDERED_LIST_OUT_OF_MEMORY){
        return MTM_ELECTIONS_MEMORY_ERROR;
    } else if (insert_result == UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS){
        return MTM_ELECTIONS_CITY_ALREADY_EXISTS;
    } else if (insert_result == UNIQUE_ORDERED_LIST_SUCCESS) {
        return MTM_ELECTIONS_SUCCESS;
    }
    return MTM_ELECTIONS_UNDEFINED_ERROR;
}

MtmElectionsResult mtmElectionsAddCitizen(MtmElections mtmElections,
                                          const char* citizenName,
                                          int citizenId,
                                          int citizenAge,
                                          int yearsOfEducation,
                                          int cityId) {
    if (citizenName == NULL || mtmElections == NULL) {
        return MTM_ELECTIONS_NULL_ARGUMENT
    }
    if (cityId <0 || citizenId <0) {
        return MTM_ELECTIONS_ILLEGAL_ID
    }
    if (citizenAge <= 0) {
        return MTM_ELECTIONS_ILLEGAL_AGE;
    }
    if(yearsOfEducation < 0) {
        return MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS;
    }

    Citizen new_citizen = CitizenCreate(char* citizenName, int citizenAge,
                                        int citizenId, int yearsOfEducation,
                                        int cityId);
    if (new_citizen == NULL){
        return MTM_ELECTIONS_MEMORY_ERROR;
    }
    UniqueOrderedListResult result;
    result = uniqueOrderedListInsert(mtmElections->citizens, new_citizen);

    if (result == UNIQUE_ORDERED_LIST_SUCCESS) {
        return MTM_ELECTIONS_SUCCESS;
    } else if (result == UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS) {
        CitizenFree(new_citizen);
        return MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS;
    } else if (result == UNIQUE_ORDERED_LIST_OUT_OF_MEMORY) {
        CitizenFree(new_citizen);
        return MTM_ELECTIONS_MEMORY_ERROR;
    }
    return MTM_ELECTIONS_UNDEFINED_ERROR;
}

MtmElectionsResult MtmElectionsCitizenGetName(MtmElections mtmElections,
                                              int citizenId,
                                              char** name) {
    if (name == NULL || mtmElections == NULL) { //TODO:CR: if name == NULL, why is that a problem?
        return MTM_ELECTIONS_NULL_ARGUMENT;
    }
    if(citizenId < 0){
        return  MTM_ELECTIONS_ILLEGAL_ID;
    }
    Citizen citizen = GetCitizen(mtmElections->citizens, citizenId);
    if (citizen == NULL){
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *name = malloc (sizeof(char)*citizen->name); //TODO: CR: name = ptr to ptr. *name = ptr, **name value of first byte
    if (*name == NULL) {
        return MTM_ELECTIONS_MEMORY_ERROR;
    }
    strcpy(*name, citizen->name);
    return MTM_ELECTIONS_SUCCESS
}

MtmElectionsResult MtmElectionsCitizenGetCity(MtmElections mtmElections,
                                              int citizenId,
                                              int* cityId) {
    if (mtmElections == NULL){
        return MTM_ELECTIONS_NULL_ARGUMENT
    }
    if(citizenId < 0 ){
        return  MTM_ELECTIONS_ILLEGAL_ID;
    }
    Citizen citizen = GetCitizen(mtmElections->citizen,citizenId);
    if (citizen == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *cityId = citizen->city_id;
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult MtmElectionsCitizenGetAge(MtmElections mtmElections,
                                             int citizenId,
                                             int* age){
    if (mtmElections == NULL){
        return MTM_ELECTIONS_NULL_ARGUMENT
    }
    if(citizenId < 0 ){
        return  MTM_ELECTIONS_ILLEGAL_ID;
    }
    Citizen citizen = GetCitizen(mtmElections->citizen,citizenId);
    if (citizen == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *age = citizen->age;
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult MtmElectionsCitizenGetEducation(MtmElections mtmElections,
                                                   int citizenId,
                                                   int* yearsOfEducation){
    if (mtmElections == NULL){
        return MTM_ELECTIONS_NULL_ARGUMENT
    }
    if(citizenId < 0 ){
        return  MTM_ELECTIONS_ILLEGAL_ID;
    }
    Citizen citizen = GetCitizen(mtmElections->citizen,citizenId);
    if (citizen == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *yearsOfEducation = citizen->yearsOfEducation;
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult mtmElectionsSupportCandidate(MtmElections mtmElections,
                                                int citizenId,
                                                int candidateId,
                                                int priority) {
    if (mtmElections == NULL){
        return  MTM_ELECTIONS_NULL_ARGUMENT;
    }
    if (citizenId < 0 || candidateId < 0) {
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    if (priority < 0) {
        return MTM_ELECTIONS_ILLEGAL_PRIORITY;
    }
    Citizen citizen = GetCitizen(mtmElections->citizens, citizenId);
    if (citizen == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }

    Candidate candidate = GetCandidateAllCites(mtmElections->cities,
                                               candidateId);
    if (candidate == NULL) {
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    }

    if (citizen->city_id != candidate->citizen->city_id) { //CR: still not convinced this is the right way
        return MTM_ELECTIONS_NOT_SAME_CITY;
    }
    if(GetVotingPreferenceByPriority(citizen->preferences, priority) != NULL) {
        return MTM_ELECTIONS_PRIORITY_EXISTS;
    }
    if(GetVotingPreferenceByCandidate(citizen->preferences, candidateId)
                                                                     != NULL) {
        return MTM_ELECTIONS_ALREADY_SUPPORTED;
    }
    if (GetCandidateAllCites(mtmElections->cities, citizenId) != NULL) {
        return MTM_ELECTIONS_CAN_NOT_SUPPORT; // Citizen is a candidate
    }
    return  Add_Support(citizen,candidate,priority); //TODO: rework split of responsibility between the functions

}

MtmElectionsResult mtmElectionsCancelSupport(MtmElections mtmElections,
                                             int citizenId,
                                             int candidateId) {
    if (mtmElections == NULL){
        return  MTM_ELECTIONS_NULL_ARGUMENT;
    }
    if (citizenId < 0 || candidateId < 0) {
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    Citizen citizen = GetCitizen(mtmElections->citizens, citizenId);
    if (citizen == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    Candidate candidate = GetCandidateAllCites(mtmElections->cities,
                                               candidateId);
    if (candidate == NULL) {
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    }
    if(GetVotingPreferenceByCandidate(citizen->preferences, candidateId)
                                                                      == NULL) {
        return MTM_ELECTIONS_NOT_SUPPORTED;
    }
    if (citizenId == candidateId) {
        return MTM_ELECTIONS_MUST_SUPPORT;
    }
    remove_Support (citizen, candidateId); // TODO: rename and examine work-split
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult mtmElectionsChangeAddress(MtmElections mtmElections,
                                             int citizenId, int cityId){
    if (mtmElections == NULL){
        return  MTM_ELECTIONS_NULL_ARGUMENT;
    }
    if(new_city_id < 0 || id_number <0) {
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    if (GetCity(mtmElections->cities, city_id) == NULL) {
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    Citizen  citizen = GetCitizen(mtmElections->citizens, citizenId);
    if(citizen == NULL){
        MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    ChangeAddress(citizen, cityid); //TODO Change name to something better, ie CitizenSetAddress, maybe also seperate into additional clear support
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult mtmElectionsAddCandidate(MtmElections mtmElections,
                                            int candidateId, int cityId){
    if (candidateId <0 || cityId <0){
        return MTM_ELECTIONS_ILLEGAL_ID
    }
    if (mtmElections == NULL){
        return MTM_ELECTIONS_NULL_ARGUMENT;
    }
    City city = GetCity(mtmElections->cities, cityId);
    if(city== NULL){
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    }
    Citizen wanna_be_candidate = GetCitizen(mtmElections->citizens,candidateId);
    if(wanna_be_candidate == NULL || wanna_be_candidate->city_id != cityId){
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    if(GetCandidate(city->candidates,candidateId) != NULL ){
        return MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS;
    }
    if(wanna_be_candidate->age < MIN_CANDIDATE_AGE) {
        return MTM_ELECTIONS_ILLEGAL_AGE;
    }
    return CandidateAdd( wanna_be_candidate, city); //todo examine workload split
}

MtmElectionsResult mtmElectionsWithdrawCandidate(MtmElections mtmElections,
                                                 int candidateId, int cityId){
    if(mtmElections == NULL) {
        return NULL;
    }
    if (candidateId < 0 || cityId < 0 ){
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    City city = GetCity(mtmElections->cities, cityId);
    if(city == NULL){
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    }
    Candidate quitter_candidate = GetCandidate(city->candidates, candidateId);
    if(quitter_candidate == NULL){
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    }
    return CandidateRemove(mtmElections, city, quitter_candidate); //todo examine workload split
}

}

int mtmElectionsRankByAge(MtmElections mtmElections, int citizen, void* pAge){

    Citizen current_citizen = GetCitizen(mtmElections->citizens,citizen_id);
    return ((current_citizen->age) / *pAge);
}

MtmElectionsResult mtmElectionsMayorOfCity(MtmElections mtmElections, int cityId, int* mayor, const char* filename) {
    if (mtmElections == NULL) {
        return NULL;
    }
    if (cityid < 0) {
        return MTM_ELECTIONS_ILLEGAL_ID;
    }
    City election_city = GetCity(mtmElections->cities,cityId);
    if(election_city == NULL){
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    }
    if( uniqueOrderedListSize(election_city->candidates) == 0){
        return MTM_ELECTIONS_NO_CANDIDATES_IN_CITY;
    }
    Citizen current_citizen = uniqueOrderedListGetLowest(mtmElections->citizens);
    if(current_citizen == NULL){
        return NULL;
    }
    int* pAge;
    *pAge = VOTING_AGE;
    election_counter(mtmElections, current_citizen, election_city, pAge, mayor);
    FILE* winner = fopen(filename,w);
    if (winner == NULL){
        return MTM_ELECTIONS_FILE_ERROR;
    }
    Citizen chosen_mayor = GetCitizen(mtmElections->citizens, *mayor);
    mtmPrintMayorDetails(chosen_mayor->id_number, chosen_mayor->age,
            chosen_mayor->years_of_education, chosen_mayor->name,
            election_city->city_name, election_city->city_id, winner);
    fclose(winner);
    election_over(mtmElections);
    return MTM_ELECTIONS_SUCCESS;
}

UniqueOrderedList mtmElectionsPerformElections(MtmElections mtmElections, RankFunc rank, void* auxilaryData, const char* filename){
    if(mtmElections == NULL){
        return NULL;
    }
    City current_city = uniqueOrderedListGetLowest( mtmElections->cities);
    if(current_city == NULL){
        return MTM_ELECTIONS_NULL_ARGUMENT;
    }
    UniqueOrderedList Mayors =uniqueOrderedListCreate(CitizenCopy,CitizenFree,CitizenEquals,CitizenGreaterThanByName);
    int* current_mayor;
    while(current_city != NULL){
        if(uniqueOrderedListSize(current_city->candidates) != 0) {
            Citizen current_citizen = uniqueOrderedListGetLowest(mtmElections->citizens);
            election_counter(mtmElections, current_citizen, election_city, auxilaryData, current_mayor);
            uniqueOrderedListInsert(Mayors, GetCitizen(mtmElections->citizens, *mayor));
        }
        current_city = uniqueOrderedListGetNext(mtmElections->cities);
    }
    FILE* winner = fopen(filename,a);
    if (winner == NULL){
        return Mayors;
    }
    Citizen current_chosen_mayor = uniqueOrderedListGetLowest(Mayors);
    while(current_chosen_mayor != NULL) {
        current_city = GetCity(mtmElections->cities,current_chosen_mayor->city_id)
        mtmPrintMayorDetails(current_chosen_mayor->id_number, current_chosen_mayor->age, current_chosen_mayor->years_of_education,
                             current_chosen_mayor->name,
                             current_city->city_name,current_city->city_id, winner);
        current_chosen_mayor = uniqueOrderedListGetNext(Mayors);
    }
    fclose(winner);
    election_over(mtmElections);
    return Mayors;
}
