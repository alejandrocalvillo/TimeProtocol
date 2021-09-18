#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>


/**************
 * Prints manual when option "atdate man"
 * 
 * *************/
void printMan();

/**********************************************************************
 This funtion will convert from 32 bit received from the server to cest

    @param uint32_t *secs 

 ************************************************************************/
void from_secs_to_cest(uint32_t *secs);

/**********************************************************************
 * This function choose the mode among the arguments received
 * 
 *  @param int argc
 *  @param char *argv[]
 * 
 * ********************************************************************/
void startingArg(int argc, char *argv[]);