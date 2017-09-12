    blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
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

void blpopCommand(redisClient *c) {
    blockingPopGenericCommand(c,REDIS_HEAD);
}
