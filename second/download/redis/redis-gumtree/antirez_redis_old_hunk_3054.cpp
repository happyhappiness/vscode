        redisLog(REDIS_NOTICE,
            "Background AOF rewrite terminated with success");

        /* Flush the differences accumulated by the parent to the rewritten AOF. */
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int)server.bgrewritechildpid);
        newfd = open(tmpfile,O_WRONLY|O_APPEND);
        if (newfd == -1) {
            redisLog(REDIS_WARNING,
