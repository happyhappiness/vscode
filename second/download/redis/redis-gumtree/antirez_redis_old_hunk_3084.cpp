        rdbRemoveTempFile(server.bgsavechildpid);
    }
    server.bgsavechildpid = -1;
    server.bgsavethread = (pthread_t) -1;
    server.bgsavethread_state = REDIS_BGSAVE_THREAD_UNACTIVE;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
}

void saveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
