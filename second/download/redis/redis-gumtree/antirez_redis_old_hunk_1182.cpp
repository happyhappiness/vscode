
    listRewind(monitors,&li);
    while((ln = listNext(&li))) {
        redisClient *monitor = ln->value;
        addReply(monitor,cmdobj);
    }
    decrRefCount(cmdobj);
}

/* Feed the slave 'c' with the replication backlog starting from the
 * specified 'offset' up to the end of the backlog. */
long long addReplyReplicationBacklog(redisClient *c, long long offset) {
    long long j, skip, len;

    serverLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
