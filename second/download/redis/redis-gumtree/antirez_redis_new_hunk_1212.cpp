        long long now = ustime();
        mstime_t latency;

        serverLog(REDIS_NOTICE,
            "Background AOF rewrite terminated with success");

        /* Flush the differences accumulated by the parent to the
