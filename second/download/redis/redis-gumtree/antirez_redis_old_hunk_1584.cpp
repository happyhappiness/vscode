    }

    uint32_t length = 0;
    if (e->type == REDIS_LIST ||
        e->type == REDIS_SET  ||
        e->type == REDIS_ZSET ||
        e->type == REDIS_HASH) {
        if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
            SHIFT_ERROR(offset, "Error reading %s length", types[e->type]);
            return 0;
        }
    }

    switch(e->type) {
    case REDIS_STRING:
    case REDIS_HASH_ZIPMAP:
    case REDIS_LIST_ZIPLIST:
    case REDIS_SET_INTSET:
    case REDIS_ZSET_ZIPLIST:
    case REDIS_HASH_ZIPLIST:
        if (!processStringObject(NULL)) {
            SHIFT_ERROR(offset, "Error reading entry value");
            return 0;
        }
    break;
    case REDIS_LIST:
    case REDIS_SET:
        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
