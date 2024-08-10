#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "myfree.h"
#include <string.h>

#define BUFFSIZE	4096

typedef struct meminfo{
	unsigned long MemTotal;
	unsigned long SwapTotal;
	unsigned long MemFree;
	unsigned long SwapFree;
	unsigned long Shmem;
	unsigned long Buffers;
	unsigned long Cached;
	unsigned long SReclaimable;
	unsigned long MemAvailable;
	 
}mem;	

//mem memory;
void findMemInfo(char *line, unsigned long *value) {
    sscanf(line, "%*s %lu", value); 
}

void returnMemInfo(mem* memory)
{
	int fd = open("/proc/meminfo", O_RDONLY);

	if(fd == -1)
	{
		perror("Error opening /proc/meminfo");
		exit(EXIT_FAILURE);
	}

	char file[BUFFSIZE]; 
	int bytes = read(fd, file, sizeof(file) - 1);
	
	if(bytes == -1){
		perror("Error reading /proc/meminfo");
	      	close(fd);
	       	exit(EXIT_FAILURE);
    	}

	file[bytes] = '\0';

	close(fd);

	char *line  = strtok(file, "\n");

	while(line != NULL)
	{
		if (strncmp(line, "MemTotal:", 9) == 0) {
	     		findMemInfo(line, &memory->MemTotal);       
	       	} else if (strncmp(line, "MemFree:", 8) == 0) {           
		       	findMemInfo(line, &memory->MemFree);       
	       	} else if (strncmp(line, "MemAvailable:", 13) == 0) {
		    	findMemInfo(line, &memory->MemAvailable);
	       	} else if (strncmp(line, "SwapTotal:", 10) == 0){
		      	findMemInfo(line, &memory->SwapTotal);
	   	} else if (strncmp(line, "SwapFree:", 9) == 0) {
           	       	findMemInfo(line, &memory->SwapFree);
		} else if (strncmp(line, "Shmem:", 6) == 0) {
			findMemInfo(line, &memory->Shmem);
		} else if (strncmp(line, "Buffers:", 8) == 0) {
	    		findMemInfo(line, &memory->Buffers);
		} else if (strncmp(line, "Cached:", 7) == 0) {
	    		findMemInfo(line, &memory->Cached);
		} else if (strncmp(line, "SReclaimable:", 13) == 0) {
	    		findMemInfo(line, &memory->SReclaimable);
		}
		line = strtok(NULL, "\n");
	}
}


void printMemoryInfo() {
	
	mem memory = {0};
	returnMemInfo(&memory);
	unsigned long memUsed = memory.MemTotal - memory.MemFree - memory.Buffers - memory.Cached;
    	unsigned long swapUsed = memory.SwapTotal - memory.SwapFree;
    	unsigned long buffCache = memory.Buffers + memory.Cached;
       	printf("               total        used        free      shared  buff/cache   available\n");
       	printf("Mem:         %8lu %11lu %10lu %12lu %11lu %11lu\n",
           memory.MemTotal,
           memUsed,
           memory.MemFree,
           memory.Shmem,
           buffCache,
           memory.MemAvailable);
       	printf("Swap:        %8lu %11lu %11lu\n",
           memory.SwapTotal,
           swapUsed,
           memory.SwapFree);
}
