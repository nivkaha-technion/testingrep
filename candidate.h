//
// Created by nivka on 25-Nov-18.
//


#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "uniqueOrderedList/uniqueOrderedList.h"
#include "citizen.h"

typedef  struct  candidate_t{
    Citizen citizen
    int number_of_votes
} *Candidate;

Candidate CandidateCreate(Citizen candidate_person);

Candidate CandidateCopy(Candidate source);

void CandidateSupportOnlySelf(Candidate candidate);

void CandidateFree(Candidate candidate);

bool CandidateEquals (Candidate first, Candidate second);

bool CandidateGreaterThan (Candidate first, Candidate second);

MtmElectionResult CandidateAdd(Citizen wanna_be_candidate,City wanna_be_city);

MtmElectionResult CandidateRemove(MtmElections mtmElections,City had_enough_city,
                                                 Candidate had_enough_candidate);
void election_over(MtmElections mtmElections);


//ToAdd: CandidateCreate function
//ToAdd: CandidateSupportOnlySelf function

#endif //CANDIDATE_H
