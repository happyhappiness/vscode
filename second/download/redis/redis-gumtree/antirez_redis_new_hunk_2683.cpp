            goto cleanup;
        }

        if (aofRewriteBufferWrite(newfd) == -1) {
            redisLog(REDIS_WARNING,
                "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
            close(newfd);
            goto cleanup;
        }

        redisLog(REDIS_NOTICE,
            "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", aofRewriteBufferSize());

        /* The only remaining thing to do is to rename the temporary file to
         * the configured file and switch the file descriptor used to do AOF
