addReplyError(c,
                "Active defragmentation cannot be enabled: it requires a "
                "Redis server compiled with a modified Jemalloc like the "
                "one shipped by default with the Redis source distribution");