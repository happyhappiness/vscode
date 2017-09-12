#include "redis.h"

/*-----------------------------------------------------------------------------
 * String Commands
 *----------------------------------------------------------------------------*/

void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
    int retval;
    long seconds = 0; /* initialized to avoid an harmness warning */
