    serverAssert(server.aof_state == REDIS_AOF_OFF);
    if (server.aof_fd == -1) {
        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
        return C_ERR;
    }
    if (rewriteAppendOnlyFileBackground() == C_ERR) {
        close(server.aof_fd);
        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
        return C_ERR;
    }
    /* We correctly switched on AOF, now wait for the rewrite to be complete
     * in order to append data on disk. */
    server.aof_state = REDIS_AOF_WAIT_REWRITE;
    return C_OK;
}

/* Write the append only file buffer on disk.
