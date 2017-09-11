#include <stdio.h>
#include <poll.h>
#include <limits.h>

#include "net.h"
#include "sds.h"

/* Defined in hiredis.c */
void __redisSetError(redisContext *c, int type, const char *str);

static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
    char buf[128];
    size_t len = 0;

    if (prefix != NULL)
        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
    strerror_r(errno,buf+len,sizeof(buf)-len);
    __redisSetError(c,type,buf);
}

static int redisSetReuseAddr(redisContext *c, int fd) {
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
