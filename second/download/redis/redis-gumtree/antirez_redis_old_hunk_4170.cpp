    }
}

static int getDoubleFromObject(redisClient *c, robj *o, double *value) {
    double parsedValue;
    char *eptr = NULL;

    if (o && o->type != REDIS_STRING) {
        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
        return REDIS_ERR;
    }

    if (o == NULL)
        parsedValue = 0;
    else if (o->encoding == REDIS_ENCODING_RAW)
        parsedValue = strtod(o->ptr, &eptr);
    else if (o->encoding == REDIS_ENCODING_INT)
        parsedValue = (long)o->ptr;
    else
        redisAssert(1 != 1);

    if (eptr != NULL && *eptr != '\0') {
        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
        return REDIS_ERR;
    }

    *value = parsedValue;

    return REDIS_OK;
}

static int getLongLongFromObject(redisClient *c, robj *o, long long *value) {
    long long parsedValue;
    char *eptr = NULL;

    if (o && o->type != REDIS_STRING) {
        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
        return REDIS_ERR;
    }

    if (o == NULL)
        parsedValue = 0;
    else if (o->encoding == REDIS_ENCODING_RAW)
        parsedValue = strtoll(o->ptr, &eptr, 10);
    else if (o->encoding == REDIS_ENCODING_INT)
        parsedValue = (long)o->ptr;
    else
        redisAssert(1 != 1);

    if (eptr != NULL && *eptr != '\0') {
        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
        return REDIS_ERR;
    }

    *value = parsedValue;

    return REDIS_OK;
}

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

