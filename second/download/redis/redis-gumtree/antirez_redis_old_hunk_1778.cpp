            server.lastbgsave_status = REDIS_ERR;
    }
    server.rdb_child_pid = -1;
    server.rdb_save_time_last = time(NULL)-server.rdb_save_time_start;
    server.rdb_save_time_start = -1;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR);
}

void saveCommand(redisClient *c) {
