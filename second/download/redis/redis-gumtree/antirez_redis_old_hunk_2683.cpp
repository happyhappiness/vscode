            goto cleanup;
        }

        nwritten = write(newfd,server.aof_rewrite_buf,sdslen(server.aof_rewrite_buf));
        if (nwritten != (signed)sdslen(server.aof_rewrite_buf)) {
            if (nwritten == -1) {
                redisLog(REDIS_WARNING,
                    "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
            } else {
                redisLog(REDIS_WARNING,
                    "Short write trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
            }
            close(newfd);
            goto cleanup;
        }

        redisLog(REDIS_NOTICE,
            "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", nwritten);

        /* The only remaining thing to do is to rename the temporary file to
         * the configured file and switch the file descriptor used to do AOF
