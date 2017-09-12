    }
}

static int getDoubleFromObject(robj *o, double *target) {
    double value;
    char *eptr = NULL;

    if (o == NULL) {
        value = 0;
    } else {
        redisAssert(o->type == REDIS_STRING);
        if (o->encoding == REDIS_ENCODING_RAW) {
            value = strtod(o->ptr, &eptr);
        } else if (o->encoding == REDIS_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            redisAssert(1 != 1);
        }
    }

    if (eptr != NULL && eptr[0] != '\0') {
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

static int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const char *msg) {
    double value;
    if (getDoubleFromObject(o, &value) != REDIS_OK) {
        if (msg != NULL) {
            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
        } else {
            addReplySds(c, sdsnew("-ERR value is not a double\r\n"));
        }
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

static int getLongLongFromObject(robj *o, long long *target) {
    long long value;
    char *eptr = NULL;

    if (o == NULL) {
        value = 0;
    } else {
        redisAssert(o->type == REDIS_STRING);
        if (o->encoding == REDIS_ENCODING_RAW) {
            value = strtoll(o->ptr, &eptr, 10);
        } else if (o->encoding == REDIS_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            redisAssert(1 != 1);
        }
    }

    if (eptr != NULL && eptr[0] != '\0') {
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

static int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg) {
    long long value;
    if (getLongLongFromObject(o, &value) != REDIS_OK) {
        if (msg != NULL) {
            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
        } else {
            addReplySds(c, sdsnew("-ERR value is not an integer\r\n"));
        }
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

static int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *msg) {
    long long value;

    if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
    if (value < LONG_MIN || value > LONG_MAX) {
        if (msg != NULL) {
            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
        } else {
            addReplySds(c, sdsnew("-ERR value is out of range\r\n"));
        }
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

