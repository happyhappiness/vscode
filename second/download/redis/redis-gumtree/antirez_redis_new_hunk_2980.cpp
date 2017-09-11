    return REDIS_OK;
}

void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire, int unit) {
    long long milliseconds = 0; /* initialized to avoid an harmness warning */

    if (expire) {
        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
            return;
        if (milliseconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
        if (unit == UNIT_SECONDS) milliseconds *= 1000;
    }

    if (lookupKeyWrite(c->db,key) != NULL && nx) {
