long long addReplyReplicationBacklog(redisClient *c, long long offset) {
    long long j, skip, len;

//    printf("SLAVE REQUEST %lld\n", offset);

    if (server.repl_backlog_histlen == 0) {
//        printf("NO HISTORY\n");
        return 0;
    }

//    printf("FIRST BYTE WE HAVE %lld\n", server.repl_backlog_off);
//    printf("HISTLEN %lld\n", server.repl_backlog_histlen);
//    printf("IDX %lld\n", server.repl_backlog_idx);

    /* Compute the amount of bytes we need to discard. */
    skip = offset - server.repl_backlog_off;
//    printf("SKIP %lld\n", skip);

    /* Point j to the oldest byte, that is actaully our
     * server.repl_backlog_off byte. */
    j = (server.repl_backlog_idx +
        (server.repl_backlog_size-server.repl_backlog_histlen)) %
        server.repl_backlog_size;
//    printf("J %lld\n", j);

    /* Discard the amount of data to seek to the specified 'offset'. */
    j = (j + skip) % server.repl_backlog_size;

    /* Feed slave with data. Since it is a circular buffer we have to
     * split the reply in two parts if we are cross-boundary. */
    len = server.repl_backlog_histlen - skip;
//    printf("LEN %lld\n", len);
    while(len) {
        long long thislen =
            ((server.repl_backlog_size - j) < len) ?
            (server.repl_backlog_size - j) : len;

//        printf("WRITE %lld\n", thislen);
        addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
        len -= thislen;
        j = 0;
