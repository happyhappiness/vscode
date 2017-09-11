    /* Add 1 to psync_offset if it the replication backlog does not exists
     * as when it will be created later we'll increment the offset by one. */
    if (server.repl_backlog == NULL) psync_offset++;
    addReplySds(c,
        sdscatprintf(sdsempty(),"+FULLRESYNC %s %lld\r\n",
        server.runid,
        psync_offset));
    return REDIS_ERR;
}

