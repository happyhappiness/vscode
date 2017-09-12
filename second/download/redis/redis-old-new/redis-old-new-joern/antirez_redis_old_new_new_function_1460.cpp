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