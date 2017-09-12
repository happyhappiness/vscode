int redisContextSetTimeout(redisContext *c, struct timeval tv) {
    if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(SO_RCVTIMEO): %s", strerror(errno)));
        return REDIS_ERR;
    }
    if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(SO_SNDTIMEO): %s", strerror(errno)));
        return REDIS_ERR;
    }
    return REDIS_OK;
}