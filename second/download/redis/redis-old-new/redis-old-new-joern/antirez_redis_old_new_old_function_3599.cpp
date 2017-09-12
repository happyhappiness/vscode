void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    time_t timeout;
    int j;

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
        if (o != NULL) {
            if (o->type != REDIS_LIST) {
                addReply(c,shared.wrongtypeerr);
                return;
            } else {
                if (listTypeLength(o) != 0) {
                    /* If the list contains elements fall back to the usual
                     * non-blocking POP operation */
                    robj *argv[2], **orig_argv;
                    int orig_argc;

                    /* We need to alter the command arguments before to call
                     * popGenericCommand() as the command takes a single key. */
                    orig_argv = c->argv;
                    orig_argc = c->argc;
                    argv[1] = c->argv[j];
                    c->argv = argv;
                    c->argc = 2;

                    /* Also the return value is different, we need to output
                     * the multi bulk reply header and the key name. The
                     * "real" command will add the last element (the value)
                     * for us. If this souds like an hack to you it's just
                     * because it is... */
                    addReplySds(c,sdsnew("*2\r\n"));
                    addReplyBulk(c,argv[1]);
                    popGenericCommand(c,where);

                    /* Fix the client structure with the original stuff */
                    c->argv = orig_argv;
                    c->argc = orig_argc;
                    return;
                }
            }
        }
    }
    /* If the list is empty or the key does not exists we must block */
    timeout = strtol(c->argv[c->argc-1]->ptr,NULL,10);
    if (timeout > 0) timeout += time(NULL);
    blockForKeys(c,c->argv+1,c->argc-2,timeout);
}