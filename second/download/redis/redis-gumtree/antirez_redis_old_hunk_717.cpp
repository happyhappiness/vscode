 * socket target depending on the configuration, and making sure that
 * the script cache is flushed before to start.
 *
 * Returns C_OK on success or C_ERR otherwise. */
int startBgsaveForReplication(void) {
    int retval;

    serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        server.repl_diskless_sync ? "slaves sockets" : "disk");

    if (server.repl_diskless_sync)
        retval = rdbSaveToSlavesSockets();
    else
        retval = rdbSaveBackground(server.rdb_filename);
