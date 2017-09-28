    replicationSendNewlineToMaster();
}

/* Once we have a link with the master and the synchroniziation was
 * performed, this function materializes the master client we store
 * at server.master, starting from the specified file descriptor. */
void replicationCreateMasterClient(int fd) {
    server.master = createClient(fd);
    server.master->flags |= CLIENT_MASTER;
    server.master->authenticated = 1;
    server.repl_state = REPL_STATE_CONNECTED;
    server.master->reploff = server.repl_master_initial_offset;
    memcpy(server.master->replrunid, server.repl_master_runid,
        sizeof(server.repl_master_runid));
    /* If master offset is set to -1, this master is old and is not
     * PSYNC capable, so we flag it accordingly. */
    if (server.master->reploff == -1)
        server.master->flags |= CLIENT_PRE_PSYNC;
}

/* Asynchronously read the SYNC payload we receive from a master */
#define REPL_MAX_WRITTEN_BEFORE_FSYNC (1024*1024*8) /* 8 MB */
void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[4096];
