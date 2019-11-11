CC=gcc
OBJS=candidate.o citizen.o city.o mtm_elections.o mtm_elections_utils.o mtm_print.o voting_preference.o exampleMain.o #
EXEC=take1
DEBUG=
CFLAGS=-std=c99 -Wall -Werror -pedantic-errors $(DEBUG)

$(EXEC)  : $(OBJS)
    $(CC) $(DEBUG_FLAG) $(OBJS) -o $@

candidate.o: candidate.c candidate.h uniqueOrderedList/uniqueOrderedList.h citizen.h voting_preference.h

citizen.o: citizen.c citizen.h uniqueOrderedList/uniqueOrderedList.h

city.o: city.c uniqueOrderedList/uniqueOrderedList.h city.h candidate.h  citizen.h

mtm_elections.o: mtm_elections.c mtm_elections.h  uniqueOrderedList/uniqueOrderedList.h candidate.h citizen.h city.h  voting_preference.h

mtm_elections_utils.o: mtm_elections_utils.c mtm_elections_utils.h  uniqueOrderedList/uniqueOrderedList.h citizen.h city.h candidate.h  voting_preference.h

mtm_print.o: mtm_print.c mtm_print.h

voting_preference.o: voting_preference.c voting_preference.h  uniqueOrderedList/uniqueOrderedList.h candidate.h citizen.h
#exmaple main remove befor flight\submit
exampleMain.o: exampleMain.c mtm_elections.h uniqueOrderedList/uniqueOrderedList.h


clean:
    rm -f $(OBJS)