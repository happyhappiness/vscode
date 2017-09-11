             /* Don't care if this fails: oldfd will be -1 and we handle that.
              * One notable case of -1 return is if the old file does
              * not exist. */
             oldfd = open(server.appendfilename,O_RDONLY|O_NONBLOCK);
        } else {
            /* AOF enabled */
            oldfd = -1; /* We'll set this to the current AOF filedes later. */
        }

        /* Rename the temporary file. This will not unlink the target file if
         * it exists, because we reference it with "oldfd". */
        if (rename(tmpfile,server.appendfilename) == -1) {
            redisLog(REDIS_WARNING,
                "Error trying to rename the temporary AOF: %s", strerror(errno));
            close(newfd);
