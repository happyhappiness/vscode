void ldbEndSession(client *c) {
    /* Emit the remaining logs and an <endsession> mark. */
    ldbLog(sdsnew("<endsession>"));
    ldbSendLogs();

    /* If it's a fork()ed session, we just exit. */
    if (ldb.forked) {
        writeToClient(c->fd, c, 0);
        serverLog(LL_WARNING,"Lua debugging session child exiting");
        exitFromChild(0);
    } else {
        serverLog(LL_WARNING,
            "Redis synchronous debugging eval session ended");
    }

    /* Otherwise let's restore client's state. */
    anetNonBlock(NULL,ldb.fd);
    anetSendTimeout(NULL,ldb.fd,0);

    /* Close the client connectin after sending the final EVAL reply
     * in order to signal the end of the debugging session. */
    c->flags |= CLIENT_CLOSE_AFTER_REPLY;

    /* Cleanup. */
    sdsfreesplitres(ldb.src,ldb.lines);
    ldb.lines = 0;
    ldb.active = 0;
}