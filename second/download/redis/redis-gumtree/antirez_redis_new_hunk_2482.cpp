    c->flags |= REDIS_SLAVE;
    c->replstate = REDIS_REPL_ONLINE;
    listAddNodeTail(server.slaves,c);
    /* We can't use the connection buffers since they are used to accumulate
     * new commands at this stage. But we are sure the socket send buffer is
     * emtpy so this write will never fail actually. */
    buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
    if (write(c->fd,buf,buflen) != buflen) {
        freeClientAsync(c);
        return REDIS_OK;
    }
    psync_len = addReplyReplicationBacklog(c,psync_offset);
    redisLog(REDIS_NOTICE,
        "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
