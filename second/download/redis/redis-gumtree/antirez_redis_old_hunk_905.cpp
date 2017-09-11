        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
        if (childpid == -1) {
            server.lastbgsave_status = C_ERR;
            serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
                strerror(errno));
            return C_ERR;
        }
        serverLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
        server.rdb_save_time_start = time(NULL);
        server.rdb_child_pid = childpid;
        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
        updateDictResizePolicy();
        return C_OK;
    }
