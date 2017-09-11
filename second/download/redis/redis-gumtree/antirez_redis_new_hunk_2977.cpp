        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not a valid float");
        }
        return REDIS_ERR;
    }

    *target = value;
    return REDIS_OK;
}

int getLongDoubleFromObject(robj *o, long double *target) {
    long double value;
    char *eptr;

    if (o == NULL) {
        value = 0;
    } else {
        redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
        if (o->encoding == REDIS_ENCODING_RAW) {
            errno = 0;
            value = strtold(o->ptr, &eptr);
            if (eptr[0] != '\0' || errno == ERANGE || isnan(value))
                return REDIS_ERR;
        } else if (o->encoding == REDIS_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            redisPanic("Unknown string encoding");
        }
    }
    *target = value;
    return REDIS_OK;
}

int getLongDoubleFromObjectOrReply(redisClient *c, robj *o, long double *target, const char *msg) {
    long double value;
    if (getLongDoubleFromObject(o, &value) != REDIS_OK) {
        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not a valid float");
        }
        return REDIS_ERR;
    }
