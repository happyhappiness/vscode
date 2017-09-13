static int getLongFromObject(redisClient *c, robj *o, long *value) {
    long long actualValue;

    if (getLongLongFromObject(c, o, &actualValue) != REDIS_OK) return REDIS_ERR;

    if (actualValue < LONG_MIN || actualValue > LONG_MAX) {
        addReplySds(c,sdsnew("-ERR value is out of range\r\n"));
        return REDIS_ERR;
    }

    *value = actualValue;

    return REDIS_OK;
}