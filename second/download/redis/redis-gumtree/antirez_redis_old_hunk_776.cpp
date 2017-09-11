            size_t private_dirty = zmalloc_get_private_dirty();

            if (private_dirty) {
                serverLog(REDIS_NOTICE,
                    "AOF rewrite: %zu MB of memory used by copy-on-write",
                    private_dirty/(1024*1024));
            }
