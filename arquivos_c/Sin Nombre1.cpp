#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// for time() function
#include <time.h>

int main(){
	time_t hour = time(0);
    struct tm *tlocal = localtime(&hour);
	printf(tlocal->tm_hour);
	}
