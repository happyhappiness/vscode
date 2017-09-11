/* Lookup the named master into sentinel.masters.
 * If the master is not found reply to the client with an error and returns
 * NULL. */
sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(redisClient *c,
                        robj *name)
{
    sentinelRedisInstance *ri;
