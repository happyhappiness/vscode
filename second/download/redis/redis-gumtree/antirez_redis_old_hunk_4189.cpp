    robj *o;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        value = 0;
    } else {
        if (o->type != REDIS_STRING) {
            value = 0;
        } else {
            char *eptr;

            if (o->encoding == REDIS_ENCODING_RAW)
                value = strtoll(o->ptr, &eptr, 10);
            else if (o->encoding == REDIS_ENCODING_INT)
                value = (long)o->ptr;
            else
                redisAssert(1 != 1);
        }
    }

    value += incr;
    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
