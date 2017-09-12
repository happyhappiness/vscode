__redisSetError(c,REDIS_ERR_IO,
                sdscatprintf(sdsempty(), "getsockopt(SO_ERROR): %s", strerror(errno)));