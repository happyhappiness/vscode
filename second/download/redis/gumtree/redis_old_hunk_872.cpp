    listIter li;
    listNode *ln;

    serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        socket_target ? "slaves sockets" : "disk");

    rdbSaveInfo rsi = RDB_SAVE_INFO_INIT;
    /* If we are saving for a chained slave (that is, if we are,
     * in turn, a slave of another instance), make sure after
     * loadig the RDB, our slaves select the right DB: we'll just
     * send the replication stream we receive from our master, so
     * no way to send SELECT commands. */
    if (server.master) rsi.repl_stream_db = server.master->db->id;

    if (socket_target)
        retval = rdbSaveToSlavesSockets(&rsi);
    else
        retval = rdbSaveBackground(server.rdb_filename,&rsi);

    /* If we failed to BGSAVE, remove the slaves waiting for a full
     * resynchorinization from the list of salves, inform them with
     * an error about what happened, close the connection ASAP. */
    if (retval == C_ERR) {
        serverLog(LL_WARNING,"BGSAVE for replication failed");
