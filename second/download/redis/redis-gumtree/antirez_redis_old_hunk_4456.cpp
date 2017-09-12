    }
}

/* Try to encode a string object in order to save space */
static int tryObjectEncoding(robj *o) {
    long value;
    char *endptr, buf[32];
    sds s = o->ptr;

    if (o->encoding != REDIS_ENCODING_RAW)
