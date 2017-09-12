__redisSetError(c,REDIS_ERR_PROTOCOL,
            sdsnew(((redisReader*)c->reader)->error));