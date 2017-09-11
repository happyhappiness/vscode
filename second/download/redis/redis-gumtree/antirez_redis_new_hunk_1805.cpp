    server.rdb_save_time_start = -1;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_DISK);
}

/* A background saving child (BGSAVE) terminated its work. Handle this.
 * This function covers the case of RDB -> Salves socket transfers for
 * diskless replication. */
void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
    if (!bysignal && exitcode == 0) {
        redisLog(REDIS_NOTICE,
            "Background RDB transfer terminated with success");
    } else if (!bysignal && exitcode != 0) {
        redisLog(REDIS_WARNING, "Background transfer error");
    } else {
        redisLog(REDIS_WARNING,
            "Background transfer terminated by signal %d", bysignal);
    }
    server.rdb_child_pid = -1;
    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
    server.rdb_save_time_start = -1;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
}

/* When a background RDB saving/transfer terminates, call the right handler. */
void backgroundSaveDoneHandler(int exitcode, int bysignal) {
    switch(server.rdb_child_type) {
    case REDIS_RDB_CHILD_TYPE_DISK:
        backgroundSaveDoneHandlerDisk(exitcode,bysignal);
        break;
    case REDIS_RDB_CHILD_TYPE_SOCKET:
        backgroundSaveDoneHandlerSocket(exitcode,bysignal);
        break;
    default:
        redisPanic("Unknown RDB child type.");
        break;
    }
}

/* Spawn an RDB child that writes the RDB to the sockets of the slaves
 * that are currently in REDIS_REPL_WAIT_BGSAVE_START state. */
int rdbSaveToSlavesSockets(void) {
    int *fds;
    int numfds;
    listNode *ln;
    listIter li;
    pid_t childpid;
    long long start;

    if (server.rdb_child_pid != -1) return REDIS_ERR;

    fds = zmalloc(sizeof(int)*listLength(server.slaves));
    numfds = 0;

    listRewind(server.slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;

        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
            fds[numfds++] = slave->fd;
            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
        }
    }

    /* Fork ... */
    start = ustime();
    if ((childpid = fork()) == 0) {
        /* Child */
        int retval;
        rio slave_sockets;

        rioInitWithFdset(&slave_sockets,fds,numfds);
        zfree(fds);

        closeListeningSockets(0);
        redisSetProcTitle("redis-rdb-to-slaves");

        retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL);
        if (retval == REDIS_OK) {
            size_t private_dirty = zmalloc_get_private_dirty();

            if (private_dirty) {
                redisLog(REDIS_NOTICE,
                    "RDB: %zu MB of memory used by copy-on-write",
                    private_dirty/(1024*1024));
            }
        }
        exitFromChild((retval == REDIS_OK) ? 0 : 1);
    } else {
        /* Parent */
        server.stat_fork_time = ustime()-start;
        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
        if (childpid == -1) {
            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                strerror(errno));
            return REDIS_ERR;
        }
        redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
        server.rdb_save_time_start = time(NULL);
        server.rdb_child_pid = childpid;
        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
        updateDictResizePolicy();
        zfree(fds);
        return REDIS_OK;
    }
    return REDIS_OK; /* unreached */
}

void saveCommand(redisClient *c) {
