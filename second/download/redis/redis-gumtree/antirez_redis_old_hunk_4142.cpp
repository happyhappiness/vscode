        val = 0; /* anti-warning */
        redisPanic("Unknown RDB integer encoding type");
    }
    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
}

static robj *rdbLoadLzfStringObject(FILE*fp) {
