//
// Created by nivka on 29-Nov-18.
//

#include "mtm_elections_utils.h"


Element* GetElementFromUniqueOrderedList(UniqueOrderedList list,
                                         ElementMatcher element_match,
                                         void * matching_arguement){
    Element current_element = uniqueOrderedListGetLowest(list);
    while (current_element != NULL &&
           !element_match(current_element, matching_arguement)) {
        current_element = uniqueOrderedListGetNext(list);
    }
    return current_element; // will be NULL if no matching element found
}
//TODO: maybe move matchers to modules? (city matcher to city, etc)
// Get City
bool CityMatchesId (City element, int * id_number) {
    return (element->city_id == *id_number);
}
City GetCity (UniqueOrderedList cities, int city_id){
    return (City) GetElementFromUniqueOrderedList(cities,
                                                  CityMatchesId,
                                                  &city_id);
}

// Get Citizen

bool CitizenMatchesId (Citizen element, int * id_number) {
    return (element->id_number == *id_number);
}

City GetCitizen (UniqueOrderedList citizens, int id_number){
    return (Citizens) GetElementFromUniqueOrderedList(citizens,
                                                      CitizenMatchesId,
                                                      &id_number);
}

// Get Preference
bool PreferenceMatchesCandidate (VotingPreference element, int * id_number) {
    return CandidateMatchesId(element->candidate, id_number);
}

VotingPreference GetVotingPreferenceByCandidate (UniqueOrderedList preferences,
                                                 int candidate_id) {
    return (VotingPreference) GetElementFromUniqueOrderedList(preferences,
                                                     PreferenceMatchesCandidate,
                                                     &candidate_id);
}

bool PreferenceMatchesByPriority(VotingPreference element, int * priority) {
    return (element->priority == *priority);
}

VotingPreference GetVotingPreferenceByPriority (UniqueOrderedList preferences,
                                                int priority){
    return (VotingPreference) GetElementFromUniqueOrderedList(preferences,
                                                   PreferenceMatchesByPriority,
                                                   &priority);
}

// Get Candidate
bool CandidateMatchesId (Candidate element, int * id_number) {
    return (element->citizen->id_number == *id_number);
}
Candidate GetCandidate(UniqueOrderedList candidates, int id_number){
    return (Candidate) GetElementFromUniqueOrderedList(candidates,
                                                       CandidateMatchesId,
                                                       &id_number);
}
// Get Candidate among all Cities
Candidate GetCandidateAllCities(UniqueOrderedList cities, int candidate_id){
    City current_city = uniqueOrderedListGetLowest(cities);
    while (current_city != NULL){
        Candidate found = GetCandidate(current_city->candidates, candidate_id);
        if (found != NULL){
            return found;
        }
        current_city = uniqueOrderedListGetNext(cities);
    }
    return NULL;
}
int GetRank (MtmElections mtmElections, RankFunc Rank, void* parameter,int citizen_id) {
    if (Rank == NULL) {
        Citizen Current_citizen = GetCitizen(mtmElections->citizens,citizen_id);
        if (current_citizen->age <  (int) *parameter){
           return 0;
        } else {
            return  1;
        }
    }
    return Rank(mtmElections, parameter, citizen_id);
}

void election_counter(MtmElections mtmElections,Citizen current_citizen, City election_city,int *pAge,int* mayor,RankFunc Rank){
    while (current_citizen != NULL) {
        if (current_citizen->city_id == cityId) {
            VotingPreference current_preference = uniqueOrderedListGetLowest
                    (current_citizen->preferences);
            if (current_preference != NULL) {
                current_preference->candidate->number_of_votes += GetRank
                        (MtmElectionsmtmElections, Rank, current_citizen->id_number, pAge);
            }
        }
        Voting_compare(current_city, mayor);
    }
}

void Voting_compare(City current_city, int* mayor){
    Candidate current_candidate = uniqueOrderedListGetLowest(current_city -> candidates);
    Candidate current_mayor = current_candidate;
    while (current_candidate != NULL){
        if(current_candidate->number_of_votes > current_mayor->number_of_votes){
            current_mayor = current_candidate;
        }
        if(current_candidate->number_of_votes == current_mayor->number_of_votes &&
                strcmp(current_candidate->citizen->name, current_mayor->citizen->name)== 0) {
            if (CitizenGreaterThan(current_candidate->citizen, current_mayor->citizen)) {
                current_mayor = current_candidate;
            }
        }
        current_candidate = uniqueOrderedListGetNext(current_city->candidates);
    }
    *mayor = current_mayor->citizen->id_number;
    return;
}