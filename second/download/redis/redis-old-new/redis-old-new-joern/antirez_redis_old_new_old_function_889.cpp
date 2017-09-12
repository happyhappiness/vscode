static void setProtocolError(client *c, int pos) {
    if (server.verbosity <= REDIS_VERBOSE) {
        sds client = catClientInfoString(sdsempty(),c);
        serverLog(REDIS_VERBOSE,
            "Protocol error from client: %s", client);
        sdsfree(client);
    }
    c->flags |= REDIS_CLOSE_AFTER_REPLY;
    sdsrange(c->querybuf,pos,-1);
}