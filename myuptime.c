#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "myuptime.h" 

#define BUFFSIZE 128

void printUptime() {
       	int fd = open("/proc/uptime", O_RDONLY);
    
	if (fd == -1) {
		perror("Cannot open /proc/uptime");
		exit(EXIT_FAILURE);
    	}
    
	char file[BUFFSIZE];
   	ssize_t bytes = read(fd, file, sizeof(file) - 1);

	if (bytes == -1) {
		perror("Error reading /proc/uptime");
	 	close(fd);
		exit(EXIT_FAILURE);
    	}
    	file[bytes] = '\0'; 
       	close(fd);
    
	double uptime = 0.0, idleTime = 0.0;
    	sscanf(file, "%lf %lf", &uptime, &idleTime);


	time_t now = time(NULL);  // Time in seconds
    	struct tm *local = localtime(&now); // tm struct which contains sec, min, hours, etc
      	char mytime[9];
    	strftime(mytime, sizeof(mytime), "%H:%M:%S", local); // formats the tm struct
    
	int days = uptime / 86400;
    	int hours = (uptime - (days * 86400)) / 3600;
    	int minutes = (uptime - (days * 86400) - (hours * 3600)) / 60;
    

	fd = open("/proc/loadavg", O_RDONLY);
    
	if (fd == -1) {
		perror("Cannot open /proc/loadavg");
		exit(EXIT_FAILURE);
    	}
    
	char loadfile[BUFFSIZE];
	bytes = read(fd, loadfile, sizeof(loadfile) - 1);
    	if (bytes == -1) {
		perror("Error reading /proc/loadavg");
		close(fd);
		exit(EXIT_FAILURE);
       	}
    
	loadfile[bytes] = '\0'; 
    	close(fd);
    
	double load1, load5, load15;
    	sscanf(loadfile, "%lf %lf %lf", &load1, &load5, &load15);
      
	printf("%s up %d:%02d, 1 user, load average: %.2f, %.2f, %.2f\n", mytime, hours, minutes, load1, load5, load15);
}


