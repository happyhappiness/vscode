 * This way multiple Sentinel objects that refer all to the same physical
 * Sentinel instance but in the context of different masters will use
 * a single connection, will send a single PING per second for failure
 * detection and so forth. */
void tryConnectionSharing(sentinelRedisInstance *ri) {
    redisAssert(ri->flags & SRI_SENTINEL);

    /* TODO:
     * 1) Check if there is a match.
     * 2) Free our current link.
     * 3) Reference the other link and increment its reference count. */
    REDIS_NOTUSED(ri);
}

/* This function is called when an hiredis connection reported an error.
