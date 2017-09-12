void ldbEndSession(client *c) {
    /* If it's a fork()ed session, we just exit. */
    if (ldb.forked) {
        writeToClient(c->fd, c, 0);
        serverLog(LL_WARNING,"Lua debugging session child exiting");
        exitFromChild(0);
    }

    /* Otherwise let's restore client's state. */
    anetNonBlock(NULL,ldb.fd);
    ldb.active = 0;
    decrRefCount(ldb.src);
}