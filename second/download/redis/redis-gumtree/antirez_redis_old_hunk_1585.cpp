    }

    offset[1] = CURR_OFFSET;
    if (e.type == REDIS_SELECTDB) {
        if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
            SHIFT_ERROR(offset[1], "Error reading database number");
            return e;
