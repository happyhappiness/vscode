        _exit((retval == REDIS_OK) ? 0 : 1);
    } else {
        /* Parent */
        if (childpid == -1) {
            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                strerror(errno));
