#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

void printMan();
void from_secs_to_cest(uint32_t * secs);
void startingArg(int argc, char *argv[]);
void time_conversion(uint32_t * seconds);