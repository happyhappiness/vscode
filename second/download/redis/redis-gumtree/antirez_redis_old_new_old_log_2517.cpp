__redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(SO_RCVTIMEO): %s", strerror(errno)));