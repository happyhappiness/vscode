            zfree(fds);
            close(pipefds[0]);
            close(pipefds[1]);
            return C_ERR;
        }
        serverLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
        server.rdb_save_time_start = time(NULL);
        server.rdb_child_pid = childpid;
        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
        updateDictResizePolicy();
        zfree(fds);
        return C_OK;
    }
    return C_OK; /* unreached */
}

void saveCommand(client *c) {
    if (server.rdb_child_pid != -1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
    if (rdbSave(server.rdb_filename) == C_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
