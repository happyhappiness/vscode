        val = 0; /* anti-warning */
        redisPanic("Unknown RDB integer encoding type");
    }
    return createStringObjectFromLongLong(val);
}

static robj *rdbLoadLzfStringObject(FILE*fp) {
