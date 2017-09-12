    }
}

/* Try to encode a string object in order to save space */
static int tryObjectEncoding(robj *o) {
    long value;
    char *endptr, buf[32];
    sds s = o->ptr;

    if (o->encoding != REDIS_ENCODING_RAW)
        return REDIS_ERR; /* Already encoded */

    /* It's not save to encode shared objects: shared objects can be shared
     * everywhere in the "object space" of Redis. Encoded objects can only
     * appear as "values" (and not, for instance, as keys) */
     if (o->refcount > 1) return REDIS_ERR;

    /* Currently we try to encode only strings */
    assert(o->type == REDIS_STRING);

    /* Check if it's possible to encode this value as a long. We are assuming
     * that sizeof(long) = sizeof(void) in all the supported archs. */
    value = strtol(s, &endptr, 10);
    if (endptr[0] != '\0') return REDIS_ERR;
    snprintf(buf,32,"%ld",value);

    /* If the number converted back into a string is not identical
     * then it's not possible to encode the string as integer */
    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return REDIS_ERR;

    /* Ok, this object can be encoded */
    o->encoding = REDIS_ENCODING_INT;
    sdsfree(o->ptr);
    o->ptr = (void*) value;
    return REDIS_OK;
}

/* Get a decoded version of an encoded object (returned as a new object) */
static robj *getDecodedObject(const robj *o) {
    robj *dec;
    
    assert(o->encoding != REDIS_ENCODING_RAW);
    if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
        char buf[32];

        snprintf(buf,32,"%ld",(long)o->ptr);
        dec = createStringObject(buf,strlen(buf));
        return dec;
    } else {
        assert(1 != 1);
    }
}

/*============================ DB saving/loading ============================ */
