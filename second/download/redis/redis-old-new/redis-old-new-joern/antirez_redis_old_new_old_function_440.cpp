static int loadPair(entry *e) {
    uint32_t offset = CURR_OFFSET;
    uint32_t i;

    /* read key first */
    char *key;
    if (processStringObject(&key)) {
        e->key = key;
    } else {
        SHIFT_ERROR(offset, "Error reading entry key");
        return 0;
    }

    uint32_t length = 0;
    if (e->type == RDB_TYPE_LIST ||
        e->type == RDB_TYPE_SET  ||
        e->type == RDB_TYPE_ZSET ||
        e->type == RDB_TYPE_HASH) {
        if ((length = loadLength(NULL)) == RDB_LENERR) {
            SHIFT_ERROR(offset, "Error reading %s length", types[e->type]);
            return 0;
        }
    }

    switch(e->type) {
    case RDB_TYPE_STRING:
    case RDB_TYPE_HASH_ZIPMAP:
    case RDB_TYPE_LIST_ZIPLIST:
    case RDB_TYPE_SET_INTSET:
    case RDB_TYPE_ZSET_ZIPLIST:
    case RDB_TYPE_HASH_ZIPLIST:
        if (!processStringObject(NULL)) {
            SHIFT_ERROR(offset, "Error reading entry value");
            return 0;
        }
    break;
    case RDB_TYPE_LIST:
    case RDB_TYPE_SET:
        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element at index %d (length: %d)", i, length);
                return 0;
            }
        }
    break;
    case RDB_TYPE_ZSET:
        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element key at index %d (length: %d)", i, length);
                return 0;
            }
            offset = CURR_OFFSET;
            if (!processDoubleValue(NULL)) {
                SHIFT_ERROR(offset, "Error reading element value at index %d (length: %d)", i, length);
                return 0;
            }
        }
    break;
    case RDB_TYPE_HASH:
        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element key at index %d (length: %d)", i, length);
                return 0;
            }
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element value at index %d (length: %d)", i, length);
                return 0;
            }
        }
    break;
    default:
        SHIFT_ERROR(offset, "Type not implemented");
        return 0;
    }
    /* because we're done, we assume success */
    e->success = 1;
    return 1;
}