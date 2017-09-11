    c->flags |= REDIS_SLAVE;
    c->replstate = REDIS_REPL_ONLINE;
    listAddNodeTail(server.slaves,c);
    addReplySds(c,sdsnew("+CONTINUE\r\n"));
    psync_len = addReplyReplicationBacklog(c,psync_offset);
    redisLog(REDIS_NOTICE,
        "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
