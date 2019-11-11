//
// Created by nivka on 29-Nov-18.
//

#ifndef MTM_ELECTIONS_UTILS_H
#define MTM_ELECTIONS_UTILS_H

#include "uniqueOrderedList/uniqueOrderedList.h"
#include "citizen.h"
#include "city.h"
#include "candidate.h"
#include "voting_preference.h"

typedef bool (*ElementMatcher)(Element, void *);

Element* GetElementFromUniqueOrderedList(UniqueOrderedList list,
                                         ElementMatcher element_match,
                                         void * matching_arguement);

// Get City
bool CityMatchesId (City element, int * id_number);
City GetCity (UniqueOrderedList cities, int city_id);

// Get Citizen
bool CitizenMatchesId (Citizen element, int * id_number);
City GetCitizen (UniqueOrderedList citizens, int id_number);

// Get Preference
bool PreferenceMatchesCandidate (VotingPreference element, int * id_number);
VotingPreference GetVotingPreferenceByCandidate (UniqueOrderedList preferences,
                                                 int candidate_id);
bool PreferenceMatchesByPriority(VotingPreference element, int * priority);
VotingPreference GetVotingPreferenceByPriority (UniqueOrderedList preferences,
                                                int priority);

// Get Candidate
bool CandidateMatchesId (Candidate element, int * id_number);
Candidate GetCandidate(UniqueOrderedList candidates, int id_number);

int GetRank (MtmElections mtmElections, RankFunc Rank, void* parameter,int citizen_id);

void election_counter(MtmElections mtmElections,Citizen current_citizen, City election_city,int* pAge,int* mayor);

void Voting_compare(City current_city, int* mayor);
#endif //MTM_ELECTIONS_UTILS_H