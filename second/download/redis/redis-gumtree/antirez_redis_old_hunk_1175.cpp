#include <sys/uio.h>
#include <math.h>

static void setProtocolError(redisClient *c, int pos);

/* Return the size consumed from the allocator, for the specified SDS string,
 * including internal fragmentation. This function is used in order to compute
