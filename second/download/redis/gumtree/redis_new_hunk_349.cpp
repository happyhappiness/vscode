/* Lookup a slave in a master Redis instance, by ip and port. */
sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
                sentinelRedisInstance *ri, char *ip, int port)
{
    sds key;
    sentinelRedisInstance *slave;

    redisAssert(ri->flags & SRI_MASTER);
    key = sdscatprintf(sdsempty(),
        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
        ip,port);
    slave = dictFetchValue(ri->slaves,key);
    sdsfree(key);
