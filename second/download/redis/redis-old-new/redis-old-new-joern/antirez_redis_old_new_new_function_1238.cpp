int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
    redisAssert(ri->flags & SRI_SENTINEL);
    dictIterator *di;
    dictEntry *de;

    if (ri->runid == NULL) return REDIS_ERR; /* No way to identify it. */
    if (ri->link->refcount > 1) return REDIS_ERR; /* Already shared. */

    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master = dictGetVal(de), *match;
        /* We want to share with the same physical Senitnel referenced
         * in other masters, so skip our master. */
        if (master == ri->master) continue;
        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
                                                       NULL,0,ri->runid);
        if (match == ri) continue; /* Should never happen but... safer. */

        /* We identified a matching Sentinel, great! Let's free our link
         * and use the one of the matching Sentinel. */
        releaseInstanceLink(ri->link,NULL);
        ri->link = match->link;
        match->link->refcount++;
        printf("SHARED!\n");
        return REDIS_OK;
    }
    dictReleaseIterator(di);
    return REDIS_ERR;
}