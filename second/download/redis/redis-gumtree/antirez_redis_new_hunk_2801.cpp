    case REDIS_LIST_ZIPLIST:
    case REDIS_SET_INTSET:
    case REDIS_ZSET_ZIPLIST:
    case REDIS_HASH_ZIPLIST:
        if (!processStringObject(NULL)) {
            SHIFT_ERROR(offset, "Error reading entry value");
            return 0;
