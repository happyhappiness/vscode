#include <stdio.h>
#include <poll.h>
#include <limits.h>
#include <stdlib.h>

#include "net.h"
#include "sds.h"

/* Defined in hiredis.c */
void __redisSetError(redisContext *c, int type, const char *str);

static void redisContextCloseFd(redisContext *c) {
    if (c && c->fd >= 0) {
        close(c->fd);
        c->fd = -1;
    }
}

static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
    char buf[128] = { 0 };
    size_t len = 0;

    if (prefix != NULL)
        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
    __redis_strerror_r(errno, (char *)(buf + len), sizeof(buf) - len);
    __redisSetError(c,type,buf);
}

static int redisSetReuseAddr(redisContext *c) {
    int on = 1;
    if (setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        redisContextCloseFd(c);
        return REDIS_ERR;
    }
    return REDIS_OK;
