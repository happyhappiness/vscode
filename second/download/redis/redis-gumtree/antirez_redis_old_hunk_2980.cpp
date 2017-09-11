    return REDIS_OK;
}

void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
    long seconds = 0; /* initialized to avoid an harmness warning */

    if (expire) {
        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
            return;
        if (seconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
    }

    if (lookupKeyWrite(c->db,key) != NULL && nx) {
