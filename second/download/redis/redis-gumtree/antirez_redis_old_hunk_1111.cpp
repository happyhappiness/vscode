            zfree(fds);
            close(pipefds[0]);
            close(pipefds[1]);
            return REDIS_ERR;
        }
        serverLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
        server.rdb_save_time_start = time(NULL);
        server.rdb_child_pid = childpid;
        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
        updateDictResizePolicy();
        zfree(fds);
        return REDIS_OK;
    }
    return REDIS_OK; /* unreached */
}

void saveCommand(client *c) {
    if (server.rdb_child_pid != -1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
    if (rdbSave(server.rdb_filename) == REDIS_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
