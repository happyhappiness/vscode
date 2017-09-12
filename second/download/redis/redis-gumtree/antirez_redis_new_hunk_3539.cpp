    return 1;
}

int checkTimeout(redisClient *c, robj *object, time_t *timeout) {
    long long lltimeout;

    if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
        addReplyError(c, "timeout is not an integer");
        return REDIS_ERR;
    }

    if (lltimeout < 0) {
        addReplyError(c, "timeout is negative");
        return REDIS_ERR;
    }

    *timeout = lltimeout;

    return REDIS_OK;
}

/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
