        val = 0; /* anti-warning */
        redisPanic("Unknown RDB integer encoding type");
    }
    if (encode)
        return createStringObjectFromLongLong(val);
    else
        return createObject(REDIS_STRING,sdsfromlonglong(val));
}

static robj *rdbLoadLzfStringObject(FILE*fp) {
