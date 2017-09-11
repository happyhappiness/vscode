        /* Flush the differences accumulated by the parent to the
         * rewritten AOF. */
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof",
            (int)server.bgrewritechildpid);
        newfd = open(tmpfile,O_WRONLY|O_APPEND);
        if (newfd == -1) {
            redisLog(REDIS_WARNING,
                "Unable to open the temporary AOF produced by the child: %s", strerror(errno));
            goto cleanup;
        }

        nwritten = write(newfd,server.bgrewritebuf,sdslen(server.bgrewritebuf));
        if (nwritten != (signed)sdslen(server.bgrewritebuf)) {
            if (nwritten == -1) {
                redisLog(REDIS_WARNING,
                    "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
