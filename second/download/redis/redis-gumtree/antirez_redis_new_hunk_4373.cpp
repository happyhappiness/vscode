        val = (int32_t)v;
    } else {
        val = 0; /* anti-warning */
        redisAssert(0!=0);
    }
    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
}
