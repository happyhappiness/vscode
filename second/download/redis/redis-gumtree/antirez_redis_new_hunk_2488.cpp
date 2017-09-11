    decrRefCount(cmdobj);
}

/* Feed the slave 'c' with the replication backlog starting from the
 * specified 'offset' up to the end of the backlog. */
long long addReplyReplicationBacklog(redisClient *c, long long offset) {
    long long j, skip, len;

//    printf("SLAVE REQUEST %lld\n", offset);

    if (server.repl_backlog_histlen == 0) {
//        printf("NO HISTORY\n");
        return 0;
    }

//    printf("FIRST BYTE WE HAVE %lld\n", server.repl_backlog_off);
//    printf("HISTLEN %lld\n", server.repl_backlog_histlen);
//    printf("IDX %lld\n", server.repl_backlog_idx);

    /* Compute the amount of bytes we need to discard. */
    skip = offset - server.repl_backlog_off;
//    printf("SKIP %lld\n", skip);

    /* Point j to the oldest byte, that is actaully our
     * server.repl_backlog_off byte. */
    j = (server.repl_backlog_idx +
        (server.repl_backlog_size-server.repl_backlog_histlen)) %
        server.repl_backlog_size;
//    printf("J %lld\n", j);

    /* Discard the amount of data to seek to the specified 'offset'. */
    j = (j + skip) % server.repl_backlog_size;

    /* Feed slave with data. Since it is a circular buffer we have to
     * split the reply in two parts if we are cross-boundary. */
    len = server.repl_backlog_histlen - skip;
//    printf("LEN %lld\n", len);
    while(len) {
        long long thislen =
            ((server.repl_backlog_size - j) < len) ?
            (server.repl_backlog_size - j) : len;

//        printf("WRITE %lld\n", thislen);
        addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
        len -= thislen;
        j = 0;
    }
    return server.repl_backlog_histlen - skip;
}

/* This function handles the PSYNC command from the point of view of a
 * master receiving a request for partial resynchronization.
 *
 * On success return REDIS_OK, otherwise REDIS_ERR is returned and we proceed
 * with the usual full resync. */
int masterTryPartialResynchronization(redisClient *c) {
    long long psync_offset, psync_len;
    char *master_runid = c->argv[1]->ptr;

    /* Is the runid of this master the same advertised by the wannabe slave
     * via PSYNC? If runid changed this master is a different instance and
     * there is no way to continue. */
    if (strcasecmp(master_runid, server.runid)) {
        /* Run id "?" is used by slaves that want to force a full resync. */
        if (master_runid[0] != '?') {
            redisLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
                "Runid mismatch (Client asked for '%s', I'm '%s')",
                master_runid, server.runid);
        } else {
            redisLog(REDIS_NOTICE,"Full resync requested by slave.");
        }
        goto need_full_resync;
    }

    /* We still have the data our slave is asking for? */
    if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
       REDIS_OK) goto need_full_resync;
    if (!server.repl_backlog ||
        psync_offset < server.repl_backlog_off ||
        psync_offset >= (server.repl_backlog_off + server.repl_backlog_size))
    {
        redisLog(REDIS_NOTICE,
            "Unable to partial resync with the slave for lack of backlog (Slave request was: %lld).", psync_offset);
        goto need_full_resync;
    }

    /* If we reached this point, we are able to perform a partial resync:
     * 1) Set client state to make it a slave.
     * 2) Inform the client we can continue with +CONTINUE
     * 3) Send the backlog data (from the offset to the end) to the slave. */
    c->flags |= REDIS_SLAVE;
    c->replstate = REDIS_REPL_ONLINE;
    listAddNodeTail(server.slaves,c);
    addReplySds(c,sdsnew("+CONTINUE\r\n"));
    psync_len = addReplyReplicationBacklog(c,psync_offset);
    redisLog(REDIS_NOTICE,
        "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
    /* Note that we don't need to set the selected DB at server.slaveseldb
     * to -1 to force the master to emit SELECT, since the slave already
     * has this state from the previous connection with the master. */

    return REDIS_OK; /* The caller can return, no full resync needed. */

need_full_resync:
    /* We need a full resync for some reason... notify the client. */
    psync_offset = server.master_repl_offset;
    /* Add 1 to psync_offset if it the replication backlog does not exists
     * as when it will be created later we'll increment the offset by one. */
    if (server.repl_backlog == NULL) psync_offset++;
    addReplySds(c,
        sdscatprintf(sdsempty(),"+FULLRESYNC %s %lld\r\n",
        server.runid,
        psync_offset));
    return REDIS_ERR;
}

/* SYNC ad PSYNC command implemenation. */
void syncCommand(redisClient *c) {
    /* ignore SYNC if already slave or in monitor mode */
    if (c->flags & REDIS_SLAVE) return;
