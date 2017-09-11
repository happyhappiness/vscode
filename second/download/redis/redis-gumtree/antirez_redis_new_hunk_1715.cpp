    sentinelRedisInstance *slave;

    redisAssert(ri->flags & SRI_MASTER);
    key = sdsformatip(ip, port);
    slave = dictFetchValue(ri->slaves,key);
    sdsfree(key);
    return slave;
