        he = gethostbyname(addr);
        if (he == NULL) {
            __redisSetError(c,REDIS_ERR_OTHER,
                sdscatprintf(sdsempty(),"Can't resolve: %s",addr));
            close(s);
            return REDIS_ERR;
        }
