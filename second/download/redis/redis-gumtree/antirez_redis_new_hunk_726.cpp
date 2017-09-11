    return server.repl_backlog_histlen - skip;
}

/* Return the offset to provide as reply to the PSYNC command received
 * from the slave. The returned value is only valid immediately after
 * the BGSAVE process started and before executing any other command
 * from clients. */
long long getPsyncInitialOffset(void) {
    long long psync_offset = server.master_repl_offset;
    /* Add 1 to psync_offset if it the replication backlog does not exists
     * as when it will be created later we'll increment the offset by one. */
    if (server.repl_backlog == NULL) psync_offset++;
    return psync_offset;
}

/* Send a PSYNC reply in the specific case of a full resynchronization.
 * As a side effect, set into the slave client structure the offset
 * we sent here, so that if new slaves will later attach to the same
 * background RDB saving process (by duplicating this client output
 * buffer), we can get the right offset from this slave. */
int replicationSendFullresyncReply(client *slave, long long offset) {
    char buf[128];
    int buflen;

    slave->psync_initial_offset = offset;
    /* Don't send this reply to slaves that approached us with
     * the old SYNC command. */
    if (!(slave->flags & CLIENT_PRE_PSYNC)) {
        buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
                          server.runid,offset);
        if (write(slave->fd,buf,buflen) != buflen) {
            freeClientAsync(slave);
            return C_ERR;
        }
    }
    return C_OK;
}

/* This function handles the PSYNC command from the point of view of a
 * master receiving a request for partial resynchronization.
 *
