    /* Refuse SYNC requests if we are a slave but the link with our master
     * is not ok... */
    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED) {
        addReplySds(c,sdsnew("-ERR Can't SYNC while not connected with my master\r\n"));
        return;
    }

