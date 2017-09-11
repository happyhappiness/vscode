        redisSetProcTitle("redis-rdb-bgsave");
        retval = rdbSave(filename);
        if (retval == C_OK) {
            size_t private_dirty = zmalloc_get_private_dirty();

            if (private_dirty) {
                serverLog(LL_NOTICE,
