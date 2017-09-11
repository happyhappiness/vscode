#include "net.h"
#include "sds.h"

/* Forward declaration */
void __redisSetError(redisContext *c, int type, sds err);

static int redisCreateSocket(redisContext *c, int type) {
    int s, on = 1;
    if ((s = socket(type, SOCK_STREAM, 0)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,NULL);
        return REDIS_ERR;
    }
    if (type == AF_INET) {
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(s);
            return REDIS_ERR;
        }
    }
