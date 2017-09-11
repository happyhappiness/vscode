    if (dbid != -1) selectDb(server.master,dbid);
}

void restartAOF() {
    int retry = 10;
    while (retry-- && startAppendOnly() == C_ERR) {
        serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
        sleep(1);
    }
    if (!retry) {
        serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
        exit(1);
    }
}

/* Asynchronously read the SYNC payload we receive from a master */
#define REPL_MAX_WRITTEN_BEFORE_FSYNC (1024*1024*8) /* 8 MB */
void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
