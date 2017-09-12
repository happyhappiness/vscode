int ldbStartSession(client *c) {
    ldb.forked = (c->flags & CLIENT_LUA_DEBUG_SYNC) == 0;
    if (ldb.forked) {
        pid_t cp = fork();
        if (cp == -1) {
            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
            return 0;
        } else if (cp == 0) {
            /* Child */
            serverLog(LL_WARNING,"Redis forked for debugging eval");
            closeListeningSockets(0);
        } else {
            /* Parent */
            freeClientAsync(c); /* Close the client in the parent side. */
            return 0;
        }
    }

    /* Setup our debugging session. */
    anetBlock(NULL,ldb.fd);
    ldb.active = 1;
    ldb.src = c->argv[1]; /* First argument of EVAL is the script itself. */
    incrRefCount(ldb.src);
    return 1;
}