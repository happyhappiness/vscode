__redisSetError(c,REDIS_ERR_OTHER,
                sdscatprintf(sdsempty(),"can't resolve: %s",addr));