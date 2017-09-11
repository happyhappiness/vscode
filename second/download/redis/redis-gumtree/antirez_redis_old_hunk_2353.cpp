    sentinelRedisInstance *slave;
  
    redisAssert(ri->flags & SRI_MASTER);
    key = sdscatprintf(sdsempty(),"%s:%d",ip,port);
    slave = dictFetchValue(ri->slaves,key);
    sdsfree(key);
    return slave;
