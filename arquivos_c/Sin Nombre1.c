#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// for time() function
#include <time.h>

/**
 *  check if the time is within 8h & 17h 
 *  @author  SGV
 *  @version 20201025    1.1   initial release
 *  @param   <int> $nowDT (current date time)
 *  @return <bool> i(true==if it is within working hours, false==if it is within working hours)
 */
bool checkTheSchedule(){
	time_t hour = time(0);
   
		return ( struct tm *tlocal = localtime(&hour));
}


int main(){
printf(checkTheSchedule());

}
