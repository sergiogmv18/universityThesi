#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <time.h>

#include "parapin.h"

// define state constants
#define START_STATE 0
#define INACTIVE_STATE 1
#define ACTIVE_STATE 2
#define PREPARING_ALARM_STATE 3
#define ALARM_ON_STATE 4
/**
  *  check if it is a weekday 
  *  @author  SGV
  *  @version 20201025    1.1   initial release
  *  @return <bool> if it is a weekday (true==if it is a weekday, false==it's not a weekday)
  */
bool checkIfTodayIsWeekday(){
	time_t weekday = time(0);
    struct tm *tlocal = localtime(&weekday);
	return (tlocal->tm_wday>0 && tlocal->tm_wday<6);
    
}
/**
 *  check if the time is within 8h & 17h 
 *  @author  SGV
 *  @version 20201025    1.1   initial release
 *  @return <bool> i(true==if it is within working hours, false==if it is within working hours)
 */
bool checkTheSchedule(){
	time_t hour = time(0);
    struct tm *tlocal = localtime(&hour);
	return (tlocal->tm_hour>=8 && tlocal->tm_hour< 17);
}

/**
  *  Create file to know status
  *  @author  SGV
  *  @version 20220415    1.1   initial release
  *  @param <bool> - status
  *  @return <void>
  */
checkAndCreateFile(status){
  	FILE *pont_arq;
  	if(status == true){
  		remove("alarmOff.txt");
  		pont_arq = fopen("alarmOn.txt", "a");	
	}else{
		remove("alarmOn.txt");
	 	pont_arq = fopen("alarmOff.txt", "a");		
	}
   	fclose(pont_arq);
  	return(0);	
}

int main(int argc,char* argv[]) {
	// initializing state
	char state = START_STATE;

	// alarm timeout variables
	long sensorActivationTimestamp = 0;
	long currentTimestamp;
	int currentInterval;
	int prevInterval =0;
	if (pin_init_user(LPT1) < 0)
     	exit(0);
	//SGV 20201016 Intance pin 9 whith inpunt of sensor
    pin_input_mode (LP_PIN09 | LP_PIN11);
    //SGV 20201016 Intance pin 16 whith output of alarme 
	pin_output_mode (LP_PIN16  | LP_PIN14);
//	clear_pin(LP_PIN16);
	clear_pin(LP_PIN14);
	clear_pin(LP_PIN11);
	while (1) {
		switch (state)
		{
		case START_STATE:
			/*initialize other stuff*/
			if(!checkIfTodayIsWeekday() || !checkTheSchedule()){
				state = ACTIVE_STATE;
				checkAndCreateFile(true);
			}else{
				state = INACTIVE_STATE;
				checkAndCreateFile(false);
			} 
			break;

		case INACTIVE_STATE:
			if (!checkIfTodayIsWeekday() || !checkTheSchedule())
				state = ACTIVE_STATE;
				checkAndCreateFile(true);	
			
			break;

		case ACTIVE_STATE:
			if (checkIfTodayIsWeekday() && checkTheSchedule()){
				state = INACTIVE_STATE;
				checkAndCreateFile(false);
				// leave the switch statement
				break;
			}
			/* sensor is ON */
			if (pin_is_set(LP_PIN09)){
				state = PREPARING_ALARM_STATE;
			}
			break;

		case PREPARING_ALARM_STATE:
			if( sensorActivationTimestamp == 0)
				sensorActivationTimestamp = time(NULL);
			
			currentTimestamp = time(NULL);
			
			currentInterval = currentTimestamp - sensorActivationTimestamp;
			printf("%d/%d\n", currentInterval, prevInterval);
			if(prevInterval != currentInterval) {
				printf("Elapsed time: %d seconds\n", currentInterval);
			}
			prevInterval = currentInterval;
			
			/* button is pressed */
			if (!pin_is_set(LP_PIN11)) {
				printf("\n\nBUTTON\n\n");
				// reset activation timestamp
				sensorActivationTimestamp = 0;
				state = ACTIVE_STATE;
				checkAndCreateFile(true);
			} else if (currentTimestamp - sensorActivationTimestamp > 10) {
				// reset activation timestamp
				sensorActivationTimestamp = 0;
				state = ALARM_ON_STATE;
			}
			break;
			
		case ALARM_ON_STATE:
			/* turn on the lights and the alarm */
			set_pin(LP_PIN14);
//			set_pin(LP_PIN16);
			/* button is pressed */
			if (!pin_is_set(LP_PIN11)){
				clear_pin(LP_PIN14);
				state = START_STATE;
			}
				
			break;
		}
	}
}

